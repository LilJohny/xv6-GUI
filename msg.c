//
// Created by Denis Ivanenko on 01.11.2020.
//

#include "msg.h"
#include "types.h"
#include "defs.h"
#include "graphics.h"

int handle_message(message *msg) {
	if (msg->msg_type == M_KEY_UP) {
		cprintf("KEY UP: %x, %x\n", msg->params[0], msg->params[1]);
	} else if (msg->msg_type == M_KEY_DOWN) {
		cprintf("KEY DOWN: %x, %x\n", msg->params[0], msg->params[1]);
	} else if (msg->msg_type == M_MOUSE_MOVE) {
		change_cursor_loc(msg->params[1],msg->params[0]);
		cprintf("MOUSE MOVE: dx=%d, dy=%d, btn=%x\n", msg->params[0], msg->params[1], msg->params[2]);
		initGraphics();
		demo();
	} else if (msg->msg_type == M_MOUSE_DOWN) {
		cprintf("MOUSE DOWN: btn=%x\n", msg->params[0]);
		cursor_clicked();
	} else if (msg->msg_type == M_MOUSE_UP) {
		cprintf("MOUSE UP: btn=%x\n", msg->params[0]);
		cursor_released();
	}
	return 0;
}