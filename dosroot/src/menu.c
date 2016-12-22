#include <dos.h>

int dispmenu(menu m, char autoexec) {
    int i;
    int c;

    printf("[MENU]\n");

    for (i = 0; m[i].func; ++i) {
        printf("%d\t%s\n", i + 1, m[i].description);
    }
    printf("%s\n", m[i].description);

    while (c = getch() - '0', c <= 0 || c >= i) ;

    if (autoexec) m[i].func();
    return c;
}
