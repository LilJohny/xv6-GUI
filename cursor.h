//
// Created by Denis Ivanenko on 30.11.2020.
//

#ifndef XV6_GUI__CURSOR_H_
#define XV6_GUI__CURSOR_H_

struct cursor{
	int x_coord;
	int y_coord;
};
struct cursor cursor_default = {DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2};
#endif //XV6_GUI__CURSOR_H_
