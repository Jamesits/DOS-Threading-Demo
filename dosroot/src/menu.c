#include <dos.h>
#include <math.h>


#define COLOR_RED "\033[0;31m"
#define COLOR_BLUE "\033[0;32m"
#define COLOR_NULL "\033[0m"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RETURN 13
#define CHAR_BEL 7

int dispmenu(menu m, char autoexec) {
    int i;
    int c;

    printf(COLOR_RED "\t[MENU]\n\n" COLOR_NULL);

    for (i = 0; m[i].func; ++i) {
        printf("%d\t%s\n", i + 1, m[i].description);
    }
    printf("\n");
    printf(COLOR_RED "%s" COLOR_NULL, m[i].description);

    while (c = getch() - '0', c <= 0 || c >= i) ;

    if (autoexec) m[i].func();
    return c - 1;
}

int numselection(char *prompt, int initial, int low, int high, int step) {
    int         current = initial;
    char        c;
    int         cont = 1;
    int         i;

        printf( "%s", prompt);
        printf( "\033[s");

    while (cont) {
        printf( "\033[u");
        printf( COLOR_BLUE "%6d" COLOR_NULL, current);
        c = getch();

        switch (c) {
        case KEY_UP:

            if (current < high) {
                current += step;
            } else {
                putchar(CHAR_BEL);
            }
            break;

        case KEY_DOWN:

            if (current > low) {
                current -= step;
            } else {
                putchar(CHAR_BEL);
            }
            break;

        case KEY_RETURN:
            cont = 0;

        default:
            continue;
        }
    }
    printf( "\033[u");
    printf( COLOR_BLUE "%6d\n" COLOR_NULL, current);
    return current;
}
