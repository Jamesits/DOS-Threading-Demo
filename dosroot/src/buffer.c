#include <dos.h>

void initBuf()
{
    int i;

    for (i = 0; i < NBUF - 1; ++i) {
        buf[i].next = buf + i + 1;
    }
    buf[i].next = NULL;
    freebuf     = buf;
}

struct buffer* getbuf()
{
    struct buffer *buff;

    buff        = freebuf;
    freebuf     = freebuf->next;
    return buff;
}

void insert(struct buffer **mq, struct buffer *buff)
{
    struct buffer *temp;

    if (buff == NULL) return;

    if (*mq == NULL) *mq = buff;
    else
    {
        temp = *mq;

        while (temp->next) temp = temp->next;
        temp->next = buff;
    }
    buff->next = NULL;
}

void send(char *receiver, char *a, int size)
{
    struct buffer *buff;
    int i, id = -1;
    // in_kernel = 1;

    for (i = 0; i < NTCB; i++) {
        if (strcmp(receiver, tcb[i].name) == 0) {
            id = i;
            break;
        }
    }

    if (id == -1) {
        printf("FATAL: receiver not found.\n");
        return;
    }
    wait(   &sfb);
    wait(   &mutexfb);
    buff = getbuf();
    signal(&mutexfb);

    buff->id    = current;
    buff->size  = size;
    buff->next  = NULL;
    strcpy(buff->text, a);

    wait(&tcb[id].mutex);
    insert(&tcb[id].mq, buff);
    signal( &tcb[id].mutex);

    signal( &tcb[id].sm);
    // in_kernel = 0;
}

struct buffer* remov(struct buffer **mq, int sender)
{
    struct buffer *buff, *p, *q;

    q   = NULL;
    p   = *mq;

    while ((p->next != NULL) && (p->id != sender))
    {
        q       = p;
        p       = p->next;
    }

    if (p->id == sender) {
        buff = p;

        if (q == NULL) *mq = buff->next;
        else q->next = buff->next;
        buff->next = NULL;
        return buff;
    }
    else return NULL;
}

int receive(char *sender, char *b)

{
    int i, id = -1;
    struct buffer *buff;
    // in_kernel = 1;

    for (i = 0; i < NBUF; i++)
    {
        if (strcmp(sender, tcb[i].name) == 0) {
            id = i;
            break;
        }
    }

    if (id == -1)
    {
        // printf("FATAL: sender not found.\n");
        return -1;
    }
    wait(   &tcb[current].sm);
    wait(   &tcb[current].mutex);
    buff = remov(&(tcb[current].mq), id);
    signal(&tcb[current].mutex);

    if (buff == NULL) {
        signal(&tcb[current].sm);
        enable();
        return -1;
    }
    strcpy(b, buff->text);
    wait(&mutexfb);
    insert(&freebuf, buff);
    signal( &mutexfb);
    signal( &sfb);

    // in_kernel = 0;
    return buff->size;
}
