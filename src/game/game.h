#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#include "cell.h"

// Config
#define OFFSET_TOP      256 // Smile, timers
#define OFFSET_BORDERS  64

// Macros
//
#define MIN(a, b) (a > b ? b : a)
#define MAX(a, b) (a < b ? b : a)

#define FSIZE (sizeX * sizeY)
#define GET_IDX(gameptr, x, y) (x + (gameptr->cellW * y))
#define GET_CELL(gameptr, x, y)\
  (&(gameptr->field[x + (y * gameptr->fieldW)]))

// Redraw mask macros
#define BIT_SET(gameptr, idx)\
  ( (gameptr->redrawMask)[(idx) / 8] |=  (1 << ((idx) % 8)) )
#define BIT_CLEAR(gameptr, idx)\
  ( (gameptr->redrawMask)[(idx) / 8] &= ~(1 << ((idx) % 8)) )
#define BIT_TEST(gameptr, idx)\
  ( (gameptr->redrawMask)[(idx) / 8] &   (1 << ((idx) % 8)) )

typedef struct {
  // Field
  Cell *field;
  uint8_t fieldW;
  uint8_t fieldH;

  uint16_t cellW;
  uint16_t cellH;

  // Game
  uint16_t time_s;
  uint8_t allMines;
  uint8_t remMines;

  // Flags
  uint8_t isGameOver  : 1;
  uint8_t isWinState  : 1;
  uint8_t longPress   : 1;

  uint8_t _unused     : 6;

  uint8_t *redrawMask;
} Game;


uint8_t createField(Game *game, uint8_t sizeX, uint8_t sizeY);
uint8_t createMines(Game *game, uint8_t count);

void drawFull(Game *game);
void drawPart(Game *game);

#endif // GAME_H

