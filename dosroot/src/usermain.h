#include <dos.h>

void    f1(void);
void    f2(void);
void    f3(void);
void    mutex1(void);
void    mutex2(void);
void    sender(void);
void    receiver(void);

semaphore mutex = { 1, NULL };
