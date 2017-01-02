#ifndef _MENU_H
#define _MENU_H

#include "event.h"

struct _Menu
{
    char *text;
    char enabled, moveover;
    struct _Menu *next;
    Event *func;
};
typedef struct _Menu Menu;

struct _FormMenu
{
    Menu *menu;
    char *text;
    char moveover, pressed;
    struct _FormMenu *next;
};
typedef struct _FormMenu FormMenu;

void InitFormMenuItem(FormMenu *menu);
void AddFormMenu(FormMenu *menu, char *title);
void DrawFormMenu(void *null);
void IsMoveOverFormMenu(void *n);
void DrawMoveOverFormMenu(void *n);
void IsClickFormMenu(void *n);
void DrawClickFormMenu(void *n);

void InitMenuItem(Menu *menu);
void AddMenu(Menu *menu, char enabled, char *title, Event *func);
void DrawMenu(void *n, Menu *menu, int x, int y);
void IsMoveOverMenu(void *n);
void DrawMoveOverMenu(void *n);
void ClearMenuMoveOver(void *n);

void MenuUp(void *n);
void MenuDown(void *n);

void FormMenuLeft(void *n);
void FormMenuRight(void *n);

void AddMenuToFormMenu(Menu *menu, FormMenu *formmenu);
void OpenMenu0(void *n);
void OpenMenu1(void *n);
void OpenMenu2(void *n);
void OpenMenu3(void *n);
void OpenMenu4(void *n);

void ChildTitleContextMenu(void *n);
void CleanUp(void *n);
#endif
