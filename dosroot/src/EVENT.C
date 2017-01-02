/* event.c - Event Register Functions - Felix Yan */
#include "event.h"
#include "common.h"

void RegEvent(Event *e, void (*func)(void *))
/* Register a new func as event */
{
    Event *n, *newe;
    n = e;
    while(n -> next != NULL)
        n = n -> next;
    if(n -> func == NULL)
    {
        n -> func = func;
        n -> next = NULL;
    }
    else
    {
        newe = ALLOC(sizeof(Event));
        CheckAlloc((void *)newe);
        newe -> func = func;
        newe -> next = NULL;
        n -> next = newe;
    }
}

void DoEvent(Event *e, void *data)
/* Do a event */
{
    Event *temp;
    temp = e;
    while(temp != NULL && temp -> func != NULL)
    {
        temp -> func(data);
        temp = temp -> next;
    }
}

void InitEvent(Event *e)
/* Initialize a event */
{
    e -> func = NULL;
    e -> next = NULL;
}

void FreeEvent(Event *e)
{
    Event *bak;
    while(e != NULL)
    {
        bak = e -> next;
        FREEMEM(e);
        e = bak;
    }
}
