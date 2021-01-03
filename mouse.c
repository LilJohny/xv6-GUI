#include "types.h"
#include "x86.h"
#include "defs.h"
#include "msg.h"
#include "spinlock.h"
#include "traps.h"
#include "msg.h"
#include "kbd.h"



static struct spinlock mouse_lock;
static struct {
	int x_sgn, y_sgn, x_mov, y_mov;
	int l_btn, r_btn, m_btn;
} packet;
static int count;

void mouse_wait(uchar type) {
	uint time_out = 100000;
	if (type == 0) {
		while (--time_out) {
			if ((inb(KBSTATP) & 1) == 1) {
				return;
			}
		}
	} else {
		while (--time_out) {
			if ((inb(KBSTATP) & 2) == 0)
				return;
		}
	}
}

uint mouse_read() {
	mouse_wait(0);
	return inb(KBDATAP);
}

void mouse_write(uchar word) {
	mouse_wait(1);
	outb(KBSTATP, 0xd4);
	mouse_wait(1);
	outb(KBDATAP, word);
}

void mouse_init(void) {
	uchar status_temp;

	mouse_wait(1);
	outb(KBSTATP, 0xa8);

	mouse_wait(0);

	status_temp = (inb(KBDATAP) | 2);

	mouse_wait(0);
	outb(KBSTATP, 0x60);

	mouse_wait(1);
	outb(KBDATAP, status_temp);

	mouse_write(0xf6);
	mouse_read();

	mouse_write(0xf3);
	mouse_read();

	mouse_write(10);
	mouse_read();

	mouse_write(0xf4);
	mouse_read();

	initlock(&mouse_lock, "mouse_lock");

	picenable(IRQ_MOUSE);
	ioapicenable(IRQ_MOUSE, 0);
	count = 0;
}

void gen_mouse_message() {
	if (packet.x_sgn) {
		packet.x_mov -= 256;
	}

	if (packet.y_sgn) {
		packet.y_mov -= 256;
	}
	int btns = packet.l_btn | (packet.r_btn << 1) | (packet.m_btn << 2);

	message msg;
	if (packet.x_mov || packet.y_mov) {
		msg.msg_type = M_MOUSE_MOVE;
		msg.params[0] = packet.x_mov;
		msg.params[1] = packet.y_mov;
		msg.params[2] = btns;
	} else if (btns) {
		msg.msg_type = M_MOUSE_DOWN;
		msg.params[0] = btns;
	} else {
		msg.msg_type = M_MOUSE_UP;
		msg.params[0] = btns;
	}
	handle_message(&msg);
}

void mouseintr(void) {
	acquire(&mouse_lock);
	int data = inb(KBDATAP);
	count++;
	if (count == 1) {
		if (data & 0x80) {
			packet.y_sgn = data >> 5 & 0x1;
			packet.x_sgn = data >> 4 & 0x1;
			packet.y_sgn = data >> 2 & 0x1;
			packet.y_sgn = data >> 1 & 0x1;
			packet.y_sgn = data >> 0 & 0x1;
		} else {
			count = 0;
		}
	} else if(count == 2){
		packet.x_mov = data;
	} else if(count==3){
		packet.y_mov = data;
		count = 0;
		gen_mouse_message();
	} else {
		count = 0;
	}
	release(&mouse_lock);
}



