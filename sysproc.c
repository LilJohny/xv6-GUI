#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "graphics_defs.h"
#include "pixel.h"
#include "cursor.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_drawpixel(void) {

  int offset, r, g, b;
  argint(0, &offset);
  argint(1, &r);
  argint(2, &g);
  argint(3, &b);
  drawpixel(offset, r, g, b);
  //cprintf("syscall pixel done\n");

  return 0;
}

int sys_getpixel(void) {
  PIXEL* ptr;
  int offset;
  argint(0, &offset);
  argptr(1, (void*)&ptr, sizeof(*ptr));
  getpixel(offset, ptr);
  return 0;
}

//extern struct cursor cursor_loc;

int sys_get_cursor_position_x_coord(void){
	return cursor_loc.x_coord;
}

int sys_get_cursor_position_y_coord(void){
	return cursor_loc.y_coord;
}

int sys_init_graphics(void){
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
			drawpixel(x+(y*DISPLAY_WIDTH), bg_color.R, bg_color.G,bg_color.B);
			pix++;
		}
	return 0;
}
