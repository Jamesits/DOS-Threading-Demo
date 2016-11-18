#ifndef __MAIN_H__
#define __MAIN_H__

/* 0x1C is usable */
#define TIME_INT 0x08

extern void interrupt (*oldtimeslicehandler)(void);

int main();
void far cleanup();
#endif
