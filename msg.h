//
// Created by Denis Ivanenko on 01.11.2020.
//

#ifndef XV6_GUI__MOUSE_MSG_H_
#define XV6_GUI__MOUSE_MSG_H_
#include "types.h"
#include "cursor.h"

#define M_KEY_UP 1
#define M_KEY_DOWN 2

#define M_KEY_CTRL 2
#define M_KEY_ALT 4
#define M_KEY_SHIFT 1

#define M_MOUSE_MOVE 3
#define M_MOUSE_DOWN 4
#define M_MOUSE_UP 5

typedef struct message {
	int msg_type;
	int params[10];
} message;
extern int handle_message(message*);
#endif //XV6_GUI__MOUSE_MSG_H_
