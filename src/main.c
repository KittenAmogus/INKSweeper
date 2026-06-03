#include "cell.h"
#include "config.h"
#include "images.h"

#include "inkview.h"

// InkPad entry
int main_handler(int event, int p1, int p2) {
  return 0;
}

// LD entry
int main(void) {
  InkViewMain(main_handler);
  return 0;
}

