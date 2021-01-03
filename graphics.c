#include "types.h"
#include "param.h"
#include "mmu.h"
#include "memlayout.h"
#include "proc.h"
#include "spinlock.h"
#include "graphics_defs.h"
#include "font.h"
#include "x86.h"
#include "user.h"
#include "cursor.h"

struct spinlock gui_lock;


// Draws a single pixel with a given RGB colour
void drawPixel(PIXEL* DISPLAY_pix_pointer, PIXEL color_obj) {
    drawpixel(DISPLAY_pix_pointer - display, color_obj.R, color_obj.G, color_obj.B);
}

void init_cursor(){
	cursor_loc = cursor_default;
}
// Initializes the main GUI window
void initGraphics() {
	uint graphic_mem_start = KERNBASE + 0x1028;
	uint graphic_addr = *((uint *)graphic_mem_start);
	uchar *base = (uchar *)graphic_addr;

    display = (PIXEL*)base;
    PIXEL *pix = display;
    
    PIXEL bg_color;
    bg_color.R = 0x33;
    bg_color.G = 0x66;
    bg_color.B = 0xCC;

	for (uint x = 0; x < DISPLAY_WIDTH; x++)
		for (uint y = 0; y < DISPLAY_HEIGHT; y++) {
			drawPixel(pix, bg_color);
			pix++;
		}
}