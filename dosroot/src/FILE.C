#include "common.h"
#include "event.h"
#include "file.h"
#include "dialog.h"

Row *ReadFile(void *n, char *filename, Event *readerr)
/* Read all content from a file, and format all the data to the struct */
{
    FILE *fp;
    Char *ch, *chtemp;
    Row *row, *rowtemp, *rowhead;
    if ((fp = fopen(filename, "rt")) == NULL)
    {
        DoEvent(readerr, n);
        return NULL;
    }
    ch = ALLOC(sizeof(Char));
    CheckAlloc((void *)ch);
    row = ALLOC(sizeof(Row));
    CheckAlloc((void *)row);
    rowhead = row;
    row -> ch = ch;
    while(!feof(fp))
    {
        fscanf(fp, "%c", &ch -> ch);
        if(ch -> ch == 0)
            continue;
        if(ch -> ch == 10 || ch -> ch == 13)
        {
            ch -> ch = 0;
            ch -> next = NULL;
            rowtemp = ALLOC(sizeof(Row));
            CheckAlloc((void *)rowtemp);
            row -> next = rowtemp;
            row = rowtemp;
            ch = ALLOC(sizeof(Char));
            CheckAlloc((void *)ch);
            row -> ch = ch;
        }
        else
        {
            chtemp = ALLOC(sizeof(Char));
            CheckAlloc((void *)chtemp);
            ch -> next = chtemp;
            ch = chtemp;
        }
    }
    ch -> ch = 0;
    ch -> next = NULL;
    row -> next = NULL;
    fclose(fp);
    return rowhead;
}

void NewFile(void *n)
/* open a new file */
{
	State *s;
	Char *ch;
	Row *head;
	Row *row;
    s = (State *)n;
    if(s -> highlight)
        ChangeHighlight(n);
    ch = ALLOC(sizeof(Char));
    CheckAlloc((void *)ch);
    row = ALLOC(sizeof(Row));
    CheckAlloc((void *)row);
    row -> ch = ch;
    ch -> ch = 0;
    ch -> next = NULL;
    row -> next = NULL;
    head = row;
    FREEMEMRow(s -> filehead);
	s -> filehead = head;
    s -> currentrow = 1;
    s -> currentcolumn = 1;
    memset(s -> filename, 0, 20);
    //s -> filename[0] = 0;
    CleanUp(n);
    DrawMainWindow(n);
    DrawStatusBox(n);
    DoEvent(s -> redraw, n);
    CleanUp(n);
}

void ShowFile(void *row)
{
    Char *ch;
    Row *rowtmp;
    rowtmp = (Row *)row;
    do
    {
        ch = rowtmp -> ch;
        do
        {
            printf("%c", ch -> ch);
            ch = ch -> next;
        }while(ch != NULL);
        printf("\n");
        rowtmp = rowtmp -> next;
    }while(rowtmp != NULL);
}

/*Row *NewFile(char *NewFile, Event *readerr)
{
	Char *ch;
	Row *head;
	Row *row;
	FILE *fp;
	if ((fp = fopen(NewFile, "wr+")) == NULL)
    {
        DoEvent(readerr, (void *)NewFile);
        return NULL;
    }
    ch = ALLOC(sizeof(Char));
    row = ALLOC(sizeof(Row));
    head = row;
    row -> ch = ch;
    ch = '\0';
    ch -> next = NULL;
    row -> next = NULL;
    fclose(fp);
    return head;
}*/

void ReadErr(void *n)
{
    State *s;
    char tmp[40];
    s = (State *)n;
    sprintf(tmp, "无法打开文件 %s", s -> filename);
    MsgBox(n, "错误", tmp);
    //NewFile(n);
    //printf("Error reading file %s!\n", (char *)filename);
}

