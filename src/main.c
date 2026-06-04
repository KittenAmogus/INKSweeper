// === Libraries ===
#include <stdlib.h>
#include <string.h>

#include "inkview.h"

#include "game.h"


typedef struct {
  int x, y;
} PressContext;

Game *game;
PressContext pressContext;


// === App event handlers ===

uint8_t initApp(void) {
  game = malloc(sizeof(Game));
  if (game == NULL) return 1;
  memset(game, 0, sizeof(Game));

  if (!createField(game, 16, 16)) return 0;
  if (!createMines(game, 40))   return 0;

  return 1;
}

// Allocate memory, create timers
void onInit(void) {
  if (!initApp()) {
    Message(
      ICON_INFORMATION,
      "INKSweeper", "Error creating game", 1500);
    CloseApp();
  }

  drawFull(game);
  drawPart(game);
  FullUpdate();
}

// Free memory, timers
void onExit(void) {
  if (game == NULL) return;
  free(game->field);
  free(game);
  game = NULL;
}

// === Event handlers ===
// Screen events
void onShow(void) {
  drawFull(game);
}

void onHide(void) {
}

// Key events
void onKeyPress(int key) {
  if (key == IV_KEY_MENU) {
    Message(
      ICON_INFORMATION, "INKSweeper", "Closing", 1000); CloseApp(); return;
  } else {
    char *buff = malloc(sizeof(char) * 3);
    buff[2] = 0;
    sprintf(buff, "%02x", key);
    Message(
      ICON_ERROR, "INKSweeper", buff, 1000);
  }
}

void onKeyDown(int key) {}
void onKeyUp(int key) {}

// Pointer events
void longPress_cb(void *context) {
  PressContext *pctx = (PressContext*)context;
  game->longPress = 1;
}

void onPtrMove(int x, int y) {}

void onPtrDown(int x, int y) {
  game->longPress = 0;
  pressContext.x = x;
  pressContext.y = y;
  SetHardTimerEx("longpress-timer-sweeper", longPress_cb, &pressContext, 500);
}

void onPtrUp(int x, int y) {
  ClearTimerByName("longpress-timer-sweeper");
  int8_t cx, cy;

  cx = ((x - OFFSET_BORDERS) / game->cellW);
  cy = ((y - OFFSET_TOP) / game->cellH);

  if ((cx < 0) || (cx >= game->fieldW)) return;
  if ((cy < 0) || (cy >= game->fieldH)) return;

  Cell *cell = GET_CELL(game, cx, cy);
  BIT_SET(game, GET_IDX(game, cx, cy)); // Redraw cell

  if (game->longPress) {
    cell->flagged ^= 1; // ++cell->flagged
  } else if (!cell->flagged) {
    cell->isOpen = 1;

    if (cell->isMine) {
      // Mine
    }
  } else {
    cell->flagged = 0;
  }

  drawPart(game);
}

// === Entries ===
// InkPad entry
int main_handler(int event, int p1, int p2) {
  // App start and exit
  if (event == EVT_INIT)      onInit();
  else if (event == EVT_EXIT) onExit();

  // Screen handlers
  else if (event == EVT_SHOW) onShow();
  else if (event == EVT_HIDE) onHide();

  // Key handlers
  else if (event == EVT_KEYPRESS) onKeyPress(p1);
  else if (event == EVT_KEYDOWN)  onKeyDown(p1);
  else if (event == EVT_KEYUP)    onKeyUp(p1);

  // Pointer(touch) handlers
  else if (event == EVT_POINTERMOVE)  onPtrMove(p1, p2);
  else if (event == EVT_POINTERDOWN)  onPtrDown(p1, p2);
  else if (event == EVT_POINTERUP)    onPtrUp(p1, p2);

  return 0;
}

// LD entry
int main(void) {
  InkViewMain(main_handler);
  return 0;
}

