#include <dos.h>

void f1(void)
{
    long i, j, k;

    for (i = 0; i < 1000; i++) {
        putchar('a');
    }
}

void f2(void)
{
    long i, j, k;

    for (i = 0; i < 100; i++) {
        putchar('b');
    }
}

void f3(void)
{
    long i, j, k;

    for (i = 0; i < 1000; i++) {
        putchar('c');
    }
}

void f4()
{
    int i;

    for (i = 0; i < 10; i++) {
        wait(&mutex);
        n++;
        printf(" %d", n);
        signal(&mutex);
    }
}

void f5()
{
    int i;

    for (i = 0; i < 5; i++) {
        wait(&mutex);
        n--;
        printf(" %d ", n);
        signal(&mutex);
    }
}

void producer()
{
    int tmp, i;

    for (i = 1; i <= 10; i++)
    {
        tmp = i * i;
        printf("[P] producing: %d\n", tmp);
        wait(   &empty);
        wait(   &mutex);
        intbuf[in]      = tmp;
        in              = (in + 1) % NBUF;

        signal( &mutex);
        signal( &full);
    }
}

void consumer()
{
    int tmp, i;

    for (i = 1; i <= 10; i++)
    {
        wait(   &full);
        wait(   &mutex);
        tmp     = intbuf[out];
        out     = (out + 1) % NBUF;

        signal( &mutex);
        signal( &empty);
        printf("[C] getting: %d: %d\n", i, tmp);
    }
}

void sender(void)
{
    int         i, j, size;
    char        a[10];

    for (i = 0; i < 10; i++) {
        strcpy(a, "message");
        a[7]    = '0' + n;
        a[8]    = 0;
        send("recv", a, strlen(a));
        printf("[S] Sending: %s\n", a);
        n++;
    }
    printf("[S] send finished\n");
    while (receive("recv", a) == -1) printf("[S] wait\n");
    printf("[S] got: %s\n", a);
}

void receiver(void)

{
    int         i, j, size;
    char        b[10];

    for (i = 0; i < 10; i++) {
        b[0] = 0;

        while ((size = receive("send", b)) == -1) ;
        printf( "[R] receiving: ");

        for (j = 0; j < size; j++) putchar(b[j]);
        printf( "\n");
    }
    printf( "[R] report success\n");
    strcpy(b, "ok");
    send("send", b, 3);
}
