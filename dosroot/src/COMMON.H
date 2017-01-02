#ifndef _COMMON_H
#define _COMMON_H

#define TRUE 1
#define FALSE 0

#define ALLOC malloc
#define FREEMEM free

#define DEBUG 0

#include <stdio.h>
#include <alloc.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <dos.h>
#include <bios.h>
#include "menu.h"
#include "ui.h"
#include "music.h"

void CheckAlloc(void *n);
void DoNothing(void *n);

void InitGraph(void *);
/* Function to init graphics driver */

void ClearGraph(void *);
/* Function to clear screen */

struct _Char
/* Struct of a char */
{
    struct _Char *next;
    /* pointer to left or right one */
    char ch;
};
typedef struct _Char Char;

struct _Row
/* Struct of a row */
{
    struct _Row *next;
    /* pointer to up or down row */
    Char *ch;
};
typedef struct _Row Row;

struct _MouseState
{
    int x,y;
    int key;
    int release;
};
typedef struct _MouseState MouseState;

struct _KeyMap
{
    int chs[26];
};
typedef struct _KeyMap KeyMap;

struct _NumMap
{
    int num[10];
};
typedef struct _NumMap NumMap;

struct _State
/* State of Mouse and Keyboard :) */
{
    MouseState mouse;
    KeyboardState keyboard;
    char isexit;
    FormMenu *menu;
    Menu *contextmenu;
    int iscontextmenu, cmmousex, cmmousey;
    KeyBinding *keybinding;
    Event *redraw;
    char isclearmenu;
    char iskeyboard;
    int ischildwindow, childx1, childy1, childx2, childy2;
    char dotted, highlight;
    char isdrag;
    char isedit, chinese, fullwidth, chipunc;
    int editx1, edity1, editx2, edity2;
    long delaytime;
    Row *filehead, *childhead, *childhead2;
    char *filename;
    /* the name of the opening file */
    int cursorx, cursory, iscursor;
    long cursortime;
    /*current position of the cursor*/
	int pagemovecount, currentrow, currentcolumn, rowcount;
	/* a num that remember the distance of current row */
    KeyMap map;
    NumMap nummap;
    FILE *hzkfile;
    char page;
    char mousetype;
    char nothing;
    void *mousebuf;
    char ispinyin, pinyinpage, sheng, yun;
    Music curmusic;
    int isput,lastmsx,lastmsy;
};
typedef struct _State State;

void FREEMEMRow(Row *row);
/* Release all the memory that used by a row */

void FREEMEMChar(Char *ch);

void Exit(void *n);

void CalcDelay(void *n);
void Delay(void *n, long t);

#define RIGHTSHIFT  0x01
#define LEFTSHIFT   0x02
#define CTRL        0x04
#define ALT         0x08

#define ESC       0x100
#define TAB       0xf00
#define NOMOD     0xffff

#define ENTER     0x1c00
#define SPACE     0x3900
#define BACKSPACE 0x0e00
#define DELETE    0x5300

#define PAGEUP    0x4900
#define PAGEDOWN  0x5100
#define HOME      0x4700
#define END       0x4f00

#define F1    0x3b00
#define F2    0x3c00
#define F3    0x3d00
#define F4    0x3e00
#define F5    0x3f00
#define F6    0x4000
#define F7    0x4100
#define F8    0x4200

#define UP    0x4800
#define DOWN  0x5000
#define LEFT  0x4b00
#define RIGHT 0x4d00

#define EQUAL 0xd00
#define MINUS 0xc00

#endif
