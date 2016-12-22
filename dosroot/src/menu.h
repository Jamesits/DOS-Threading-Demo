#include <dos.h>

typedef struct {
    void (*func)(void);
    char *description;
} menuitem;

typedef menuitem *menu;

int dispmenu(menu m);
