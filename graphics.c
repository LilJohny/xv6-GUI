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
void draw_hello_world_icon() {
	PIXELA pixel_red_a = getRed();
	PIXEL pixel_red;

	PIXELA pixel_white_a = getWhite();
	PIXEL pixel_white;

	pixel_red.R = pixel_red_a.R;
	pixel_red.G = pixel_red_a.G;
	pixel_red.B = pixel_red_a.B;

	pixel_white.R = pixel_white_a.R;
	pixel_white.G = pixel_white_a.G;
	pixel_white.B = pixel_white_a.B;

	int offset = DISPLAY_WIDTH * 10 + 10;
	display += DISPLAY_WIDTH * 10;
	display += 10;
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			drawPixel(display + j, pixel_red);
			if ((j == 7 || j == 22 || j == 8 || j == 23 || j == 6 || j == 21) && (i == 10 || i == 11)) {
				drawPixel(display + j, pixel_white);
			}
			if ((j >= 5 && j <= 24) && (i == 20)) {
				drawPixel(display + j, pixel_white);
			}
		}
		display += DISPLAY_WIDTH;
		offset += DISPLAY_WIDTH;
	}
	display -= offset;
}
int hello_world_window_x_coord = 40;
int hello_world_window_y_coord = 90;
void draw_hello_world_window() {
	PIXELA pixel_black_a = getBlack();
	PIXEL pixel_black;

	PIXELA pixel_white_a = getWhite();
	PIXEL pixel_white;

	PIXELA pixel_red_a = getRed();
	PIXEL pixel_red;

	pixel_black.R = pixel_black_a.R;
	pixel_black.G = pixel_black_a.G;
	pixel_black.B = pixel_black_a.B;

	pixel_white.R = pixel_white_a.R;
	pixel_white.G = pixel_white_a.G;
	pixel_white.B = pixel_white_a.B;

	pixel_red.R = pixel_red_a.R;
	pixel_red.G = pixel_red_a.G;
	pixel_red.B = pixel_red_a.B;

	int offset = DISPLAY_WIDTH * hello_world_window_y_coord + 10 + hello_world_window_x_coord;
	display += DISPLAY_WIDTH * (hello_world_window_y_coord + 10);
	display += hello_world_window_x_coord;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 160; j++) {
			drawPixel(display + j, pixel_black);
		}
		display += DISPLAY_WIDTH;
		offset += DISPLAY_WIDTH;
	}
	display -= offset;

	offset = DISPLAY_WIDTH * hello_world_window_y_coord + hello_world_window_x_coord + 10;
	display += DISPLAY_WIDTH * hello_world_window_y_coord;
	display += hello_world_window_x_coord + 10;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 150; j++) {
			drawPixel(display + j, pixel_white);
		}
		display += DISPLAY_WIDTH;
		offset += DISPLAY_WIDTH;
	}
	display -= offset;

	offset = DISPLAY_WIDTH * hello_world_window_y_coord + hello_world_window_x_coord + 160;
	display += DISPLAY_WIDTH * hello_world_window_y_coord;
	display += hello_world_window_x_coord + 160;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == j || 10 - i == j) {
				drawPixel(display + j, pixel_white);
				continue;
			}
			drawPixel(display + j, pixel_red);

		}
		display += DISPLAY_WIDTH;
		offset += DISPLAY_WIDTH;
	}
	display -= offset;
	const char *word = "Hello, world !";
	for (int q = 0; q < 14; q++) {
		offset += drawChar(display, word[q], (hello_world_window_x_coord+10) + q * 10, hello_world_window_y_coord+20, pixel_white_a);
	}
}

int in_hello_wolrd_icon(struct cursor cursor_loc) {
	int x_cond = cursor_loc.x_coord >= 10 && cursor_loc.x_coord <= 40;
	int y_cond = cursor_loc.y_coord >= 10 && cursor_loc.y_coord <= 40;
	return x_cond && y_cond;
}
int in_hello_world_close(struct cursor cursor_loc) {
	int x_cond =
			cursor_loc.x_coord >= hello_world_window_x_coord + 160 && cursor_loc.x_coord <= hello_world_window_x_coord + 170;
	int y_cond =
			cursor_loc.y_coord >= hello_world_window_y_coord && cursor_loc.y_coord <= hello_world_window_y_coord + 10;
	return x_cond && y_cond;
}
int in_hello_world_upbar(struct cursor cursor_loc) {
	int x_cond =
			cursor_loc.x_coord >= hello_world_window_x_coord + 10 && cursor_loc.x_coord <= hello_world_window_x_coord + 160;
	int y_cond =
			cursor_loc.y_coord >= hello_world_window_y_coord && cursor_loc.y_coord <= hello_world_window_y_coord + 10;
	return x_cond && y_cond;
}

int show_hello_world_icon = 1;
int show_hello_world_window = 0;
int hello_window_attached = 0;
void demo() {

	if (show_hello_world_icon == 1) {
		draw_hello_world_icon();
	}

	if (show_hello_world_window == 1) {
		draw_hello_world_window();
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

void init_cursor() {
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
		if (hello_window_attached == 1) {
			hello_world_window_y_coord -= x_diff;
		}
	}
	if (cursor_loc.x_coord + y_diff >= 0 && cursor_loc.x_coord + y_diff < DISPLAY_WIDTH) {
		cursor_loc.x_coord += y_diff;
		if (hello_window_attached == 1) {
			hello_world_window_x_coord += y_diff;
		}
	}

}
void cursor_clicked() {
	if (in_hello_wolrd_icon(cursor_loc)) {
		show_hello_world_window = 1;
	}
	if (in_hello_world_close(cursor_loc)) {
		show_hello_world_window = 0;
	}
	if (in_hello_world_upbar(cursor_loc)) {
		hello_window_attached = 1;
	}
}
void cursor_released(){
	hello_window_attached = 0;
}