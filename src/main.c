// Standart libs
#include <stdint.h>
#include <stdlib.h>

// InkPad lib
#include "inkview.h"

// Sweeper libs
#include "cell.h"
#include "game.h"
#include "config.h"
#include "images.h"

// Colors
#define COL_LIGHTGREY 0xCCCCCC
#define COL_DARKGREY  0x333333
#define COL_BLACK     0x000000
#define COL_WHITE     0xFFFFFF

uint32_t getRandom(void) {
  static uint32_t seed = 0x19236AF;

  seed ^= (seed << 13);
  seed ^= (seed >> 17);
  seed ^= (seed << 5);

  return seed;
}


// Macros
#define GET_CELL(x, y) (&(cells[x + (y * CellsX)]))

#define MIN(a, b) (a > b ? b : a)
#define MAX(a, b) (a < b ? b : a)
#define CLAMP(amin, amax, a) (MIN(MAX(a, amin), amax))

// Variables
Cell *cells;
Game game;

uint8_t CellsX;
uint8_t CellsY;

int8_t cellSizeX;
int8_t cellSizeY;


// Game functions
void genMines(void) {
  game.allMines = 10;

  uint8_t tries = 0;

  while (game.remainingMines < game.allMines) {
    ++tries;
    if (tries == 0) break;

    uint8_t posX = getRandom() % CellsX;
    uint8_t posY = getRandom() % CellsY;

    Cell *cell = GET_CELL(posX, posY);
 
    if (cell->isMine) continue;

    cell->isMine = 1;
    game.remainingMines++;

    for (int8_t ay=posY-1; ay<posY+2; ++ay) {
      if (ay < 0 || ay >= CellsY) continue;
      for (int8_t ax=posX-1; ax<posX+2; ++ax) {
        if (ax < 0 || ax >= CellsX) continue;
        if (ax == posX && ay == posY) continue;
        cell = GET_CELL(ax, ay);
        cell->nearMines++;
        cell->isOpen = 1;
      }
    }
  }
}


void redraw(void) {
}

#define DRAW_AREA(x, y, col) FillArea(\
  x * cellSizeX,\
  y * cellSizeY,\
cellSizeX, cellSizeY, col)

void redrawFull(void) {
  for (uint8_t y=0; y<CellsY; y++) {
    for (uint8_t x=0; x<CellsX; x++) {
      Cell *cell = GET_CELL(x, y);

      if (!cell->isOpen) {
        if (cell->isFlag) {
          DRAW_AREA(x, y, COL_WHITE);
          DrawRect(x * cellSizeX, y * cellSizeY, cellSizeX, cellSizeY, COL_BLACK);
        } else {
          DRAW_AREA(x, y, COL_DARKGREY);
        }
      } else {
        if (cell->isMine) {
          DRAW_AREA(x, y, COL_BLACK);
        } else {
          DRAW_AREA(x, y, COL_LIGHTGREY);
        }
      }

    }
  }

  PartialUpdate(0, 0,
                CellsX * cellSizeX,
                CellsY * cellSizeY);
}


// Functions
uint8_t start(void) {
  CellsX = 9;
  CellsY = 9;

  // Create cells array
  if (cells == NULL)
    cells = malloc(sizeof(Cell) * (CellsY * CellsX));
  if (cells == NULL) return 0;

  // Reset everything
  memset(&game, 0, sizeof(Game));
  memset(cells, 0, sizeof(Cell) * (CellsY * CellsX));

  // Create mines and draw everything
  genMines();
  redrawFull();

  return 1;
}


uint8_t onInit(void) {
  /*cellSizeX = ScreenWidth() / CellsX;
  cellSizeY = ScreenHeight() / CellsY;
  cellSizeX = MIN(cellSizeX, cellSizeY) - 4;
  cellSizeY = cellSizeX;*/
  cellSizeX = 64;
  cellSizeY = 64;
  return start();
}

void onExit(void) {
  if (cells != NULL) free(cells);
  cells = NULL;

  CloseApp();
}

// InkPad entry
int main_handler(int event, int p1, int p2) {
  // App start and exit
  if (event == EVT_INIT) {
    if (!onInit()) onExit();
  }
  else if (event == EVT_EXIT) onExit();

  else if (event == EVT_KEYPRESS) start();

  else if (event == EVT_POINTERDOWN) {
    // X=p1, Y=p2
    uint8_t intX, intY;
    intX = (p1 / cellSizeX);
    intY = (p2 / cellSizeY);
    if ((
        intX >= 0 && intX < (CellsX * cellSizeX)) &&
        (intY >= 0 && intY < (CellsY * cellSizeY))) {

      Cell *cell = GET_CELL(intX, intY);

      if (!cell) return 1;

      if (!cell->isFlag)
        cell->isOpen = 1;
      redrawFull();
    } else {
      Message(ICON_INFORMATION, "Help", "ok", 100);
    }
  }

  return 0;
}

// LD entry
int main(void) {
  InkViewMain(main_handler);
  return 0;
}

