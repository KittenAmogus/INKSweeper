#ifndef IMAGES_H
#define IMAGES_H

#define _IMG_ROOT "applications/INKSweeper_res/"

#define IMG_CELL  _IMG_ROOT "cell.bmp"  // Closed cell
#define IMG_OPEN  _IMG_ROOT "open.bmp"  // Empty cell (0)
#define IMG_FLAG  _IMG_ROOT "flag.bmp"  // Flagged cell

#define IMG_MINE  _IMG_ROOT "mine.bmp"  // Just mine
#define IMG_MINEA _IMG_ROOT "minea.bmp" // Mine that was pressed

// Usage: IMG_DIGIT(0) -> _IMG_ROOT "digits/0.png"
#define IMG_DIGIT(x)   _IMG_ROOT "digits/" #x ".bmp"

#endif // IMAGES_H

