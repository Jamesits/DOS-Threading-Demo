#include <dos.h>

void f1(void)
{
    long i, j, k;

    for (i = 0; i < 100; i++) {
        putchar('a');
        delay(5);
    }
}

void f2(void)
{
    long i, j, k;

    for (i = 0; i < 100; i++) {
        putchar('b');
        delay(5);
    }
}

void f3(void)
{
    long i, j, k;

    for (i = 0; i < 100; i++) {
        putchar('c');
        delay(5);
    }
}

void mutex1()
{
    int i;

    for (i = 0; i < 10; i++) {
        wait(&mutex);
        n++;
        printf(" %d", n);
        signal(&mutex);
    }
}

void mutex2()
{
    int i;

    for (i = 0; i < 5; i++) {
        wait(&mutex);
        n--;
        printf(" %d ", n);
        signal(&mutex);
    }
}

void sender(void)
{
    int         i;
    char        a[10] = "message ";
    for (i = 0; i < 10; i++) {
        a[7]    = '0' + i;
        send("recv", a, strlen(a) + 1);
        printf("[S] Sending: %s\n", a);
        n++;
    }
    printf("[S] send finished\n");
    receive("recv", a);
    printf("[S] got reply: %s\n", a);
}

void receiver(void)

{
    int         i;
    char        b[10];

    for (i = 0; i < 10; i++) {
        b[0] = 0;

        receive("send", b);
        printf( "[R] receiving: %s\n", b);

    }
    send("send", "OK", 3);
}
