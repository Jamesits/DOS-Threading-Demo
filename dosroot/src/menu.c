#include <dos.h>

int dispmenu(menu m) {
    int i = 0;
    int c;
    printf("[MENU]\n");
    for (; m[i].func ; ++i) {
        printf("%d\t%s\n", i + 1, m[i].description);
    }
    printf("%s\n", m[i].description);
    while (c = getch() - '0', c > 0 && c < i) {
        c = getch();
    }
    return c;
}
