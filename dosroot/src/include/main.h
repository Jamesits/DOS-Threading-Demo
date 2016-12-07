#ifndef __MAIN_H__
#define __MAIN_H__

extern void interrupt (*oldtimeslicehandler)(void);

int main();
void far cleanup();
#endif
