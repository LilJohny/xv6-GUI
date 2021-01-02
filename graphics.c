#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "memlayout.h"
#include "proc.h"
#include "spinlock.h"
#include "graphics_defs.h"
#include "font.h"
#include "x86.h"
#include "cursor.h"
#include "graphics.h"

struct spinlock gui_lock;
struct cursor cursor_loc;

// Draws a single pixel with a given RGB colour
void drawPixel(PIXEL *DISPLAY_pix_pointer, PIXEL color_obj) {
	DISPLAY_pix_pointer->R = color_obj.R;
	DISPLAY_pix_pointer->G = color_obj.G;
	DISPLAY_pix_pointer->B = color_obj.B;
}

void demo() {

	PIXEL *pix2 = display;

	int offset = 0;

	const char *words[10];
	words[0] = "Red";
	words[1] = "Blue";
	words[2] = "Green";
	words[3] = "Yellow";
	words[4] = "Cyan";
	words[5] = "Magenta";
	words[6] = "White";
	words[7] = "Black";
	words[8] = "Orange";
	words[9] = "Brown";

	PIXELA colours[10];
	colours[0] = getRed();
	colours[1] = getBlue();
	colours[2] = getGreen();
	colours[3] = getYellow();
	colours[4] = getCyan();
	colours[5] = getMagenta();
	colours[6] = getWhite();
	colours[7] = getBlack();
	colours[8] = getOrange();
	colours[9] = getBrown();

	offset = 0;
	int offsetY = 0;
	for (int idx = 0; idx < 10; idx++) {

		int wordLen = strlen(words[idx]);

		for (int q = 0; q < wordLen; q++) {
			offset += drawChar(pix2, words[idx][q], 50 + offset, 80 + offsetY, colours[idx]);
		}
		offset = 0;
		offsetY += 15;
	}
	PIXEL pixel;

	pixel.R = 0x33;
	pixel.G = 0;
	pixel.B = 0;
	display += DISPLAY_WIDTH * cursor_loc.y_coord;
	display += cursor_loc.x_coord;
	for (int i = 0; i < CURSOR_HEIGHT; i++) {
		for (int j = 0; j < CURSOR_WIDTH; j++) {
			drawPixel(display + j, pixel);
		}
		display += DISPLAY_WIDTH;
	}
}
void init_cursor(){
	cursor_loc = cursor_default;
}
// Initializes the main GUI window
void initGraphics() {
	uint graphic_mem_start = KERNBASE + 0x1028;
	uint graphic_addr = *((uint *)graphic_mem_start);
	uchar *base = (uchar *)graphic_addr;

	display = (PIXEL *)base;
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

// Draws a RGB pixel based on a RGBA pixel colour value
void drawPixelA(PIXEL *DISPLAY_pix_pointer, PIXELA color_obj) {
	float alpha;

	if (color_obj.A == COLOUR_MAX) {
		DISPLAY_pix_pointer->R = color_obj.R;
		DISPLAY_pix_pointer->G = color_obj.G;
		DISPLAY_pix_pointer->B = color_obj.B;
		return;
	} else if (color_obj.A == COLOUR_MIN) {
		return;
	}

	alpha = (float)color_obj.A / 255;

	DISPLAY_pix_pointer->R = DISPLAY_pix_pointer->R * (1 - alpha) + color_obj.R * alpha;
	DISPLAY_pix_pointer->G = DISPLAY_pix_pointer->G * (1 - alpha) + color_obj.G * alpha;
	DISPLAY_pix_pointer->B = DISPLAY_pix_pointer->B * (1 - alpha) + color_obj.B * alpha;
}

// Draws a given character and returns its width (value to add to a pointer so the next char won't overlap this one)
int drawChar(PIXEL *buf, char character, int x, int y, PIXELA color) {
	int i, j;
	PIXEL *t;
	int ord = character - 0x20;
	if (ord < 0 || ord >= (CHAR_NUM - 1)) {
		return -1;
	}
	for (i = 0; i < CHAR_HEIGHT; i++) {
		for (j = 0; j < CHAR_WIDTH; j++) {
			if (Font_Default[ord][i][j] == 1) {
				t = buf + (y + i) * DISPLAY_WIDTH + x + j;
				drawPixelA(t, color);
			}
		}
	}
	return CHAR_WIDTH;
}

// Draws a sequence of characters
void drawStr(PIXEL *buf, char *str, int x, int y, PIXELA color) {
	int offset_x = 0;

	while (*str != '\0') {
		offset_x += drawChar(buf, x + offset_x, y, *str, color);
		str++;
	}
}
void change_cursor_loc(int x_diff, int y_diff) {
	if (cursor_loc.y_coord - x_diff >= 0 && cursor_loc.y_coord - x_diff < DISPLAY_HEIGHT) {
		cursor_loc.y_coord -= x_diff;
	}
	if (cursor_loc.x_coord + y_diff >= 0 && cursor_loc.x_coord + y_diff < DISPLAY_WIDTH) {
		cursor_loc.x_coord += y_diff;
	}
}