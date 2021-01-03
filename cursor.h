//
// Created by Denis Ivanenko on 30.11.2020.
//

#ifndef XV6_GUI__CURSOR_H_
#define XV6_GUI__CURSOR_H_
#include "graphics_defs.h"

struct cursor{
	int x_coord;
	int y_coord;
};


void init_cursor();
void change_cursor_loc(int x_diff, int y_diff);
extern struct cursor cursor_loc;
#endif //XV6_GUI__CURSOR_H_
