#include <dos.h>

typedef struct {
    void (*func)(void);
    char *description;
} menuitem;

typedef menuitem
    menu[];

int     dispmenu(menu   m,
                 char   autoexec);
int     numselection(char       *prompt,
                     int        initial,
                     int        low,
                     int        high,
                     int        step);
