#include "game.h"

#include <string.h>
#include <stdlib.h>

#include "inkview.h"


void drawFull(Game *game) {
for (uint8_t y=0; y<game->fieldH; ++y) {
  for (uint8_t x=0; x<game->fieldW; ++x) {
    uint32_t col;

    Cell *cell = GET_CELL(game, x, y);

    if (cell->isOpen) {
      if (cell->isMine)
        col = BLACK;
      else if (cell->nearMines == 0)
        col = LGRAY;
      else
        col = LGRAY;
    } else {
      if (cell->flagged)
        col = WHITE;
      else
        col = DGRAY;
    }

    FillArea(
      OFFSET_BORDERS + (x * game->cellW),
      OFFSET_TOP + (y * game->cellH),
      game->cellW, game->cellH,
      col);

    DrawRect(
      OFFSET_BORDERS + (x * game->cellW),
      OFFSET_TOP + (y * game->cellH),
      game->cellW, game->cellH,
      BLACK);

    PartialUpdate(
      OFFSET_BORDERS + (x * game->cellW),
      OFFSET_TOP + (y * game->cellH),
      game->cellW, game->cellH);

    }
  }
}


void drawPart(Game *game) {
  for (uint8_t y=0; y<game->fieldH; ++y) {
    for (uint8_t x=0; x<game->fieldW; ++x) {
      if (BIT_TEST(game, GET_IDX(game, x, y))) {
        BIT_CLEAR(game, GET_IDX(game, x, y));

        uint32_t col;

        Cell *cell = GET_CELL(game, x, y);

        if (cell->isOpen) {
          if (cell->isMine)
            col = BLACK;
          else if (cell->nearMines == 0)
            col = LGRAY;
          else
            col = LGRAY;
        } else {
          if (cell->flagged)
            col = WHITE;
          else
            col = DGRAY;
        }

        FillArea(
          OFFSET_BORDERS + (x * game->cellW),
          OFFSET_TOP + (y * game->cellH),
          game->cellW, game->cellH,
          col);

        DrawRect(
          OFFSET_BORDERS + (x * game->cellW),
          OFFSET_TOP + (y * game->cellH),
          game->cellW, game->cellH,
          BLACK);

        PartialUpdate(
          OFFSET_BORDERS + (x * game->cellW),
          OFFSET_TOP + (y * game->cellH),
          game->cellW, game->cellH);

      }
    }
  }
}

uint8_t createField(Game *game, uint8_t sizeX, uint8_t sizeY) {
  game->fieldW = sizeX;
  game->fieldH = sizeY;

  // Free field
  if (game->field)  free(game->field);

  // Create field
  game->field = malloc(sizeof(Cell) * FSIZE);
  if (!game->field) return 0;
  memset(game->field, 0, sizeof(Cell) * FSIZE);

  // Create redraw mask
  game->redrawMask = malloc((7 + FSIZE) / 8);
  if (!game->redrawMask) return 0;
  memset(game->redrawMask, 0xFF, (7 + FSIZE) / 8);  // Redraw all

  // Calculate cell size (to fit screen)
  game->cellW =\
    (ScreenWidth() - (OFFSET_BORDERS << 1)) / game->fieldW;
  game->cellH =\
    (ScreenHeight() - (OFFSET_TOP)) / game->fieldH;

  // Make cell square
  game->cellW = MIN(game->cellW, game->cellH);
  game->cellH = game->cellW;

  return 1;
}

uint8_t createMines(Game *game, uint8_t count) {
  if (game->field == NULL) return 0;

  return 1;
}

