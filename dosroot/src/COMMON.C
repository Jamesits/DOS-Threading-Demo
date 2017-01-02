#include "common.h"
#include "event.h"

void CheckAlloc(void *n)
{
    if(n == NULL)
        exit(1);
}

void DoNothing(void *n)
{
    State *s;
    s = (State *)n;
    s -> nothing = 0;
}

int returnmode()
{
    return 3;
}

void InitGraph(void *n)
/* Function to init graphics driver */
{
    int gd = VGA, gm = VGAMED;
    //installuserdriver("svga256", returnmode);
    initgraph(&gd, &gm, "");
    cleardevice();
    DoNothing(n);
}

void ClearGraph(void *n)
/* Function to clear screen */
{
    DoNothing(n);
    cleardevice();
}

void FREEMEMRow(Row *row)
{
    Row *next;
    next = row;
    while(next != NULL)
    {
        next = row -> next;
        FREEMEMChar(row -> ch);
        FREEMEM(row);
        row = next;
    }
}

void FREEMEMChar(Char *ch)
{
    Char *next;
    next = ch;
    while(next != NULL)
    {
        next = ch -> next;
        FREEMEM(ch);
        ch = next;
    }
}

void Exit(void *n)
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow)
        CloseChildWindow(n);
    else
        s -> isexit = 1;
}

void CalcDelay(void *n)
{
    long bios_time, bios_time_start;
    long i;
    State *s;
    s = (State *)n;
    bios_time_start = biostime(0, 0);
    delay(200);
    bios_time = biostime(0, 0);
    s -> delaytime = bios_time - bios_time_start;
}

void Delay(void *n, long t)
{
    State *s;
    int i;
    s = (State *)n;
    
    delay((int)(200 * t / s -> delaytime / CLK_TCK));
}
