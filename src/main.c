// === Libraries ===
#include "inkview.h"

// === App event handlers ===
// Allocate memory, create timers
void onInit(void) {}

// Free memory, timers
void onExit(void) {}

// === Event handlers ===
// Screen events
void onShow(void) {}
void onHide(void) {}

// Key events
void onKeyPress(int key) {}
void onKeyDown(int key) {}
void onKeyUp(int key) {}

// Pointer events
void onPtrMove(int x, int y) {}
void onPtrDown(int x, int y) {}
void onPtrUp(int x, int y) {}

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

