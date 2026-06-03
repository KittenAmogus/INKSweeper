#ifndef CELL_H
#define CELL_H

#include <stdint.h>

#undef PACKED
#define PACKED __attribute__((packed))

typedef struct {
  // Flags
  uint8_t isMine  : 1;
  uint8_t isOpen  : 1;
  uint8_t isFlag  : 1;

  // Neighbors
  uint8_t nearMines : 4;

  uint8_t _unused : 1;
} PACKED Cell;

#endif // CELL_H

