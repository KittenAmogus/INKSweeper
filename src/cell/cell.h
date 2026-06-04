#ifndef CELL_H
#define CELL_H

#include <stdint.h>

typedef struct {
  // Flags
  uint8_t isMine  : 1;
  uint8_t isOpen  : 1;
  uint8_t flagged : 1;

  uint8_t nearMines : 4;

  uint8_t _unused   : 1;
} __attribute__((packed)) Cell;

#endif // CELL_H

