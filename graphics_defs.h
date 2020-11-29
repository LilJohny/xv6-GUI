#define GUI_BUFFER 0x9000

// Main display window x and y sizes
#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600
#define CURSOR_WIDTH 20
#define CURSOR_HEIGHT 20
#include "pixel.h"

#ifndef __ASSEMBLER__

// Pixel array that represents the display
PIXEL *display;

#endif