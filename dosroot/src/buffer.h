#include <dos.h>

struct buffer {
    int                 id;
    int                 size;
    char                text[NTEXT];
    struct buffer       *next;
} buf[NBUF], *freebuf;

void            initBuf();
struct buffer   * getbuf();
void            insert(struct buffer    **mq,
                       struct buffer    *buff);
void            send(char       *receiver,
                     char       *a,
                     int        size);
struct buffer   * remov(struct buffer   **mq,
                        int             sender);
int             receive(char    *sender,
                        char    *b);

semaphore mutexfb = { 1, NULL };
semaphore sfb = { NBUF, NULL };
semaphore empty = { NBUF, NULL };
semaphore full = { 0, NULL };
