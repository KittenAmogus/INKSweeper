#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#undef PACKED
#define PACKED __attribute__((packed))

typedef struct {
  // Game not started
  uint8_t gameOver  : 1;
  uint8_t _unused : 7;

  // Counter
  uint8_t allMines;
  uint8_t remainingMines;

  // Timer
  uint16_t  gameTime_s;
} PACKED Game;

#endif // GAME_H

