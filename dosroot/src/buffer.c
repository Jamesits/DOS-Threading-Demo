#include <dos.h>

void initBuf()
{
    int i;

    for (i = 0; i < NBUF - 1; i++) {
        buf[i].next = &buf[i + 1];
    }
    buf[i].next = NULL;
    freebuf     = &buf[0];
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

    buff->next = NULL;

    if (*mq == NULL) *mq = buff;
    else
    {
        temp = *mq;

        while (temp->next != NULL) temp = temp->next;
        temp->next = buff;
    }
}

void send(char *receiver, char *a, int size)
{
    struct buffer *buff;
    int i, id = -1;

    disable();

    for (i = 0; i < NTCB; i++) {
        if (strcmp(receiver, tcb[i].name) == 0) {
            id = i;
            break;
        }
    }

    if (id == -1) {
        printf("Error: Receiver not exist.\n");
        enable();
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
    enable();
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

    disable();

    for (i = 0; i < NBUF; i++)
    {
        if (strcmp(sender, tcb[i].name) == 0) {
            id = i;
            break;
        }
    }

    if (id == -1)
    {
        enable();
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

    enable();

    return buff->size;
}
