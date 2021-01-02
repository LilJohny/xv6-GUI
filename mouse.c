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
	int x_overflow, y_overflow;
} packet;
static int count;
static int last_btn;
static int recovery;

void mouse_wait_read() {
	uint time_out = 100000;
	while (--time_out) {
		if ((inb(KBSTATP) & 1) == 1) {
			return;
		}
	}
}

void mouse_wait_write() {
	uint time_out = 100000;
	while (--time_out) {
		if ((inb(KBSTATP) & 2) == 0)
			return;
	}
}

uint mouse_read() {
	mouse_wait_read();
	return inb(KBDATAP);
}

void mouse_write(uchar word) {
	mouse_wait_write();
	outb(KBSTATP, 0xd4);
	mouse_wait_write();
	outb(KBDATAP, word);
}

void mouse_init(void) {
	uchar status_temp;

	mouse_wait_write();
	outb(KBSTATP, 0xa8);

	mouse_wait_write();
	outb(KBSTATP, 0x20);

	mouse_wait_read();
	status_temp = (inb(KBDATAP) | 2);

	mouse_wait_read();
	outb(KBSTATP, 0x60);

	mouse_wait_write();
	outb(0x60, status_temp);

	mouse_write(0xf6);
	mouse_read();

	mouse_write(0xf3);
	mouse_read();

	mouse_write(10);
	mouse_read();

	mouse_write(0xf4);
	mouse_read();

	initlock(&mouse_lock, "mouse");
	picenable(IRQ_MOUSE);
	ioapicenable(IRQ_MOUSE, 0);

	count = 0;
}

void gen_mouse_up_message(int btns) {
	message msg;
	msg.msg_type = M_MOUSE_UP;
	msg.params[0] = btns;
	handle_message(&msg);
}

void gen_mouse_message() {
	if (packet.x_overflow || packet.y_overflow) {
		return;
	}
	int x = packet.x_sgn ? (0xffffff00 | (packet.x_mov & 0xff)) : (packet.x_mov & 0xff);
	int y = packet.y_sgn ? (0xffffff00 | (packet.y_mov & 0xff)) : (packet.y_mov & 0xff);
	packet.x_mov = x;
	packet.y_mov = y;
	int btns = packet.l_btn | (packet.r_btn << 1) | (packet.m_btn << 2);

	message msg;

	if (packet.x_mov || packet.y_mov) {
		msg.msg_type = M_MOUSE_MOVE;
		msg.params[0] = packet.x_mov;
		msg.params[1] = packet.y_mov;
		msg.params[2] = btns;
		if (btns != last_btn) {
			gen_mouse_up_message(btns);
		}
	} else if (btns) {
		msg.msg_type = M_MOUSE_DOWN;
		msg.params[0] = btns;
	} else {
		gen_mouse_up_message(btns);
	}
	last_btn = btns;
	handle_message(&msg);
}

void mouseintr(void) {
	acquire(&mouse_lock);
	int state;
	while (((state = inb(0x64)) & 1) == 1) {
		int data = inb(0x60);
		count++;

		if (recovery == 0 && (data & 255) == 0)
			recovery = 1;
		else if (recovery == 1 && (data & 255) == 0)
			recovery = 2;
		else if ((data & 255) == 12)
			recovery = 0;
		else
			recovery = -1;

		switch(count)
		{
			case 1: if(data & 0x08)
				{
					packet.y_overflow = (data >> 7) & 0x1;
					packet.x_overflow = (data >> 6) & 0x1;
					packet.y_sgn = (data >> 5) & 0x1;
					packet.x_sgn = (data >> 4) & 0x1;
					packet.m_btn = (data >> 2) & 0x1;
					packet.r_btn = (data >> 1) & 0x1;
					packet.l_btn = (data >> 0) & 0x1;
					break;
				}
				else
				{
					count = 0;
					break;
				}
			case 2:  packet.x_mov = data;
				break;
			case 3:  packet.y_mov = data;
				break;
			default: count=0;    break;
		}

		if (recovery == 2)
		{
			count = 0;
			recovery = -1;
		}
		else if (count == 3)
		{
			count = 0;
			gen_mouse_message();
		}
	}
	release(&mouse_lock);
}



