//
// Created by Denis Ivanenko on 03.01.2021.
//
#include "cursor.h"

struct cursor cursor_loc;
struct cursor cursor_default = {DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2};
void change_cursor_loc(int x_diff, int y_diff) {
	if (cursor_loc.y_coord - x_diff >= 0 && cursor_loc.y_coord - x_diff < DISPLAY_HEIGHT) {
		cursor_loc.y_coord -= x_diff;
	}
	if (cursor_loc.x_coord + y_diff >= 0 && cursor_loc.x_coord + y_diff < DISPLAY_WIDTH) {
		cursor_loc.x_coord += y_diff;
	}
}
void init_cursor(){
	cursor_loc = cursor_default;
}
struct cursor get_cursor_location(){
	return cursor_loc;
}