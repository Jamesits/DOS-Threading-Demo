#ifndef _EVENT_H
#define _EVENT_H

struct _event
{
    void (*func)(void *);
    struct _event *next;
};
typedef struct _event Event;

void RegEvent(Event *e, void (*func)(void *));
/* Register a new func as event */

void DoEvent(Event *e, void *data);
/* Do a event */

void InitEvent(Event *e);
/* Initialize a event */

#endif
