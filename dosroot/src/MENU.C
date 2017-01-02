#include "menu.h"
#include "mouse.h"
#include "common.h"

void InitFormMenuItem(FormMenu *menu)
/* Initialize a form menu item, give default values */
{
    menu -> text = NULL;
    menu -> next = NULL;
    menu -> pressed = 0;
    menu -> moveover = 0;
}

void AddFormMenu(FormMenu *menu, char *title)
/* Add an form menu item to an existing chain */
{
    FormMenu *menutmp, *menunew;
    char *s;
    menutmp = menu;
    while(menutmp -> next != NULL)
        menutmp = menutmp -> next;
    if(menutmp -> text == NULL)
    {
        InitFormMenuItem(menutmp);
        s = (char *)ALLOC((strlen(title) + 1) * sizeof(char));
        strcpy(s, title);
        menutmp -> text = s;
    }
    else
    {
        menunew = ALLOC(sizeof(FormMenu));
        InitFormMenuItem(menunew);
        s=(char *)ALLOC((strlen(title) + 1) * sizeof(char));
        strcpy(s, title);
        menunew -> text = s;
        menutmp -> next = menunew;
    }
}
    
void DrawFormMenu(void *n)
{
    State *s;
    FormMenu *menu;
    int x = 6;
    s = (State *)n;
    menu = s -> menu;
    setwritemode(1);
    SetColor(0);
    setfillstyle(SOLID_FILL, 7);
    bar(x - 3, 21, getmaxx() - 3, 43);
    while(menu -> text != NULL)
    {
        OutTextxy(n, x, 24, menu -> text, 0);
        if(menu -> next == NULL)
            break;
        menu = menu -> next;
        x += 80;
    }
}

void IsMoveOverFormMenu(void *n)
{
    State *s;
    int x = 6;
    FormMenu *menu;
    s = (State *)n;
    menu = s -> menu;
    SetColor(0);
    setwritemode(1);
    while(menu -> text != NULL)
    {
        if(!s -> ischildwindow && PinRA(
                  s -> mouse . x, s -> mouse . y, x, 24, x + 70 , 44))
            menu -> moveover = 1;
        else
            menu -> moveover = 0;
        if(menu -> next == NULL)
            break;
        menu = menu -> next;
        x += 80;
    }
}
    
void DrawMoveOverFormMenu(void *n)
{
    State *s;
    int x = 6, y = 24, k = 0;
    FormMenu *menu;
    static char moveover[10]={0};
    s = (State *)n;
    menu = s -> menu;
    setwritemode(1);
    while(menu -> text != NULL)
    {
        if(menu -> moveover == 2 || menu -> moveover != moveover[k] && !menu -> pressed)
        {
            CleanUp(n);
            SetColor(8);
            line(x-3,y-2,x-3,y+17);
            line(x-2,y-2,x+71,y-2);
            SetColor(15);
            line(x-3,y+17,x+71,y+17);
            line(x+71,y-2,x+71,y+16);
            CleanUp(n);
            menu -> moveover = menu -> moveover ? 1 : 0;
        }
        moveover[k++] = menu -> moveover;
        if(menu -> next == NULL)
            break;
        menu = menu -> next;
        x += 80;
    }
}

void IsClickFormMenu(void *n)
{
    State *s;
    int x = 6;
    int flag = 0;
    FormMenu *menu;
    s = (State *)n;
    menu = s -> menu;
    SetColor(0);
    while(menu != NULL)
    {
        if(menu -> moveover && s -> mouse . key && !s -> ischildwindow)
            menu -> pressed = ! menu -> pressed;
        else if(!menu -> moveover && s -> mouse . key)
            menu -> pressed = 0;
        if(menu -> pressed)
        {
            s -> isedit = 0;
            flag = 1;
        }
        if(menu -> next == NULL)
            break;
        menu = menu -> next;
        x += 80;
    }
    if(!flag && !s -> isedit && !s -> iscontextmenu && s -> ischildwindow < 99)
        s -> isedit = 1;
}

void DoubleOver(void *n)
{
    State *s;
    FormMenu *menu;
    s = (State *)n;
    menu = s -> menu;
    while(menu -> text != NULL)
    {
        menu -> moveover *= 2;
        if(menu -> next == NULL)
            break;
        menu = menu -> next;
    }
}

void DrawClickFormMenu(void *n)
{
    State *s;
    int x = 6, y = 24, k = 0;
    static char pressed[10]={0};
    FormMenu *menu;
    s = (State *)n;
    menu = s -> menu;
    setwritemode(1);
    while(menu -> text != NULL)
    {
        if(menu -> pressed != pressed[k] && menu -> pressed == 0)
        {
            s -> isedit = 1;
            CleanUp(n);
            if(!s -> ischildwindow)
                DoEvent(s -> redraw, n);
            CleanUp(n);
            DoubleOver(n);
            DrawMoveOverFormMenu(n);
            CleanUp(n);
            OutTextxy(n, x + 1, 25, menu -> text, 7);
            OutTextxy(n, x, 24, menu -> text, 0);
            CleanUp(n);
            pressed[k++] = menu -> pressed;
        }
        else
            k++;
        if(menu -> next == NULL)
            break;
        menu = menu -> next;
        x += 80;
    }
    menu = s -> menu;
    x = 6;
    k = 0;
    while(menu -> text != NULL)
    {
        if(menu -> pressed != pressed[k] && menu -> pressed)
        {
            DoubleOver(n);
            DrawMoveOverFormMenu(n);
            CleanUp(n);
            SetColor(15);
            line(x-3,y-2,x-3,y+17);
            line(x-2,y-2,x+71,y-2);
            SetColor(8);
            line(x-3,y+17,x+71,y+17);
            line(x+71,y-2,x+71,y+16);
            OutTextxy(n, x + 1 - menu -> pressed, 24 + 1 - menu -> pressed, menu -> text, 7);
            OutTextxy(n, x + menu -> pressed, 24 + menu -> pressed, menu -> text, 0);
            if(menu -> pressed)
                DrawMenu(n, menu -> menu, x, y + 18);
            CleanUp(n);
        }
        pressed[k++] = menu -> pressed;
        if(menu -> next == NULL)
            break;
        menu = menu -> next;
        x += 80;
    }
}

void InitMenuItem(Menu *menu)
{
    menu -> text = NULL;
    menu -> next = NULL;
    menu -> moveover = 0;
    menu -> enabled = 1;
    menu -> func = NULL;
}

void AddMenu(Menu *menu, char enabled, char *title, Event *func)
{
    Menu *menutmp, *menunew;
    char *s;
    menutmp = menu;
    while(menutmp -> next != NULL)
        menutmp = menutmp -> next;
    if(menutmp -> text == NULL)
    {
        InitMenuItem(menutmp);
        s=(char *)ALLOC((strlen(title) + 1) * sizeof(char));
        strcpy(s, title);
        menutmp -> text = s;
        menutmp -> func = func;
        menutmp -> enabled = enabled;
    }
    else
    {
        menunew = ALLOC(sizeof(Menu));
        InitMenuItem(menunew);
        s=(char *)ALLOC((strlen(title) + 1) * sizeof(char));
        strcpy(s, title);
        menunew -> text = s;
        menunew -> func = func;
        menunew -> enabled = enabled;
        menutmp -> next = menunew;
    }
}

void DrawMenu(void *n, Menu *menu, int x, int y)
{
    Menu *menutmp;
    char ch[30];
    State *s;
    s = (State *)n;
    s -> isedit = 0;
    menutmp = menu;
    setwritemode(0);
    setfillstyle(SOLID_FILL, 7);
    if(x + 180 > getmaxx())
        x -= 180;
    bar(x, y, x + 180, y + 5);
    SetColor(7);
    line(x, y, x + 180, y);
    line(x, y, x, y + 5);
    SetColor(15);
    line(x + 1, y + 1, x + 179 , y + 1);
    line(x + 1, y + 1, x + 1 , y + 4);
    SetColor(8);
    line(x + 179, y + 1, x + 179, y + 4);
    SetColor(0);
    line(x + 180, y, x + 180, y + 5);
    while(menutmp -> text != NULL)
    {
        bar(x, y + 5, x + 180, y + 30);
        SetColor(7);
        line(x, y + 5, x, y + 30);
        SetColor(15);
        line(x + 1, y + 5, x + 1, y + 30);
        SetColor(8);
        line(x + 179, y + 5, x + 179, y + 30);
        SetColor(0);
        line(x + 180, y + 5, x + 180, y + 30);
        if(menutmp -> text[0] == '-')
        {
            SetColor(8);
            line(x + 6, y + 5, x + 172, y + 5);
            SetColor(15);
            line(x + 6, y + 6, x + 172, y + 6);
            y -= 20;
        }
        else if(menutmp -> enabled == 1)
            OutTextxy(n, x + 6, y + 6, menutmp -> text, 0);
        else if(menutmp -> enabled == 2)
        {
            strcpy(ch, "  ");
            strcpy(ch + 2, menutmp -> text);
            OutTextxy(n, x + 6, y + 6, ch, 0);
        }
        else if(menutmp -> enabled == 3)
        {
            strcpy(ch, "¡Ì");
            strcpy(ch + 2, menutmp -> text);
            OutTextxy(n, x + 6, y + 6, ch, 0);
        }
        else if(menutmp -> enabled == 4)
        {
            strcpy(ch, "  ");
            strcpy(ch + 2, menutmp -> text);
            OutTextxy(n, x + 7, y + 7, ch, 15);
            OutTextxy(n, x + 6, y + 6, ch, 8);
        }
        else if(menutmp -> enabled == 5)
        {
            strcpy(ch, "¡Ì");
            strcpy(ch + 2, menutmp -> text);
            OutTextxy(n, x + 7, y + 7, ch, 15);
            OutTextxy(n, x + 6, y + 6, ch, 8);
        }
        else
        {
            OutTextxy(n, x + 7, y + 7, menutmp -> text, 15);
            OutTextxy(n, x + 6, y + 6, menutmp -> text, 8);
        }
        if(menutmp -> next == NULL)
        {
            y += 25;
            break;
        }
        menutmp = menutmp -> next;
        y += 25;
    }
    SetColor(8);
    line(x + 1, y + 5, x + 179, y + 5);
    SetColor(0);
    line(x, y + 6, x + 180, y + 6);
}

void IsMoveOverMenu(void *n)
{
    State *s;
    int x = 6, y = 42;
    FormMenu *formmenu;
    Menu *menu;
    s = (State *)n;
    formmenu = s -> menu;
    while(formmenu -> next != NULL && !formmenu -> pressed)
    {
        formmenu = formmenu -> next;
        x += 80;
    }
    if(formmenu -> pressed || s -> iscontextmenu)
    {
        if((s -> keyboard . key & 0xff00) == ESC)
        {
            formmenu = s -> menu;
            while(formmenu -> text != NULL)
            {
                formmenu -> pressed = 0;
                if(formmenu -> next == NULL)
                    break;
                formmenu = formmenu -> next;
            }
            s -> isexit = 0;
            s -> isedit = 1;
            s -> iscontextmenu = 0;
            return;
        }
        
        if(formmenu -> pressed)
            menu = formmenu -> menu;
        else
        {
            menu = s -> contextmenu;
            x = s -> cmmousex;
            y = s -> cmmousey;
        }
        while(menu != NULL)
        {
            if(x + 180 > getmaxx())
                x -= 180;
            if(PinRA(s -> mouse . x, s -> mouse . y,
               x + 1, y + 5, x + 179, y + 25) && menu -> text[0] != '-'
               && menu -> enabled != 0 && menu -> enabled != 4 &&
               menu -> enabled != 5 && !(s -> iskeyboard))
                menu -> moveover = 1;
            else if(!(s -> iskeyboard))
                menu -> moveover = 0;
            if(strlen(menu -> text) > 5 && 'A' <= menu -> text[5] &&
               menu -> text[5] <= 'Z')
                if((s -> keyboard . key & 0xff00) == s -> map . chs[menu -> text[5] - 'A'])
                {
                    menu -> moveover = 1;
                    s -> keyboard . key = ENTER;
                }
            if(menu -> moveover)
            {
                if(s -> mouse . key || (s -> keyboard . key & 0xff00) == ENTER)
                {
                    s -> iscontextmenu = 0;
                    s -> isedit = 1;
                    s -> mouse . key = 0;
                    DoEvent(menu -> func, n);
                    formmenu = s -> menu;
                    while(formmenu -> text != NULL)
                    {
                        formmenu -> pressed = 0;
                        if(formmenu -> next == NULL)
                            break;
                        formmenu = formmenu -> next;
                    }
                    return;
                }
            }
            menu = menu -> next;
            if(menu -> text[0] == '-')
            y -= 20;
            y += 25;
        }
    }
}

void DrawMoveOverMenu(void *n)
{
    State *s;
    int x = 6, y = 42, k1 = 0, k2 = 0, i, j;
    char ch[30];
    FormMenu *formmenu;
    Menu *menu;
    static char moveover[10][20]={0};
    s = (State *)n;
    formmenu = s -> menu;
    setwritemode(0);
    if(s -> isclearmenu)
    {
        for(i = 0; i < 10; i ++)
            for(j = 0; j < 20; j ++)
                moveover[i][j] = 0;
        s -> isclearmenu = 0;
    }
    while(formmenu -> next != NULL && !formmenu -> pressed)
    {
        formmenu = formmenu -> next;
        x += 80;
        k1 ++;
    }
    if(formmenu -> pressed || s -> iscontextmenu)
    {
        if(formmenu -> pressed)
            menu = formmenu -> menu;
        else
        {
            menu = s -> contextmenu;
            x = s -> cmmousex;
            y = s -> cmmousey;
            k1 = 9;
        }
        while(menu -> text != NULL)
        {
            if((menu -> moveover ? 1 : 0) != moveover[k1][k2])
            {
                if(x + 180 > getmaxx())
                    x -= 180;
                CleanUp(n);
                setwritemode(0);
                SetColor(7 - 6 * (menu -> moveover ? 1 : 0));
                for(i = y + 5; i < y + 25; i ++)
                    line(x + 3, i, x + 177, i);
                if(menu -> enabled == 2)
                {
                    strcpy(ch, "  ");
                    strcpy(ch + 2, menu -> text);
                    OutTextxy(n, x + 6, y + 6, ch, (menu -> moveover ? 1 : 0) * 15);
                }
                else if(menu -> enabled == 3)
                {
                    strcpy(ch, "¡Ì");
                    strcpy(ch + 2, menu -> text);
                    OutTextxy(n, x + 6, y + 6, ch, (menu -> moveover ? 1 : 0) * 15);
                }
                else
                    OutTextxy(n, x + 6, y + 6, menu -> text, (menu -> moveover ? 1 : 0) * 15);
                CleanUp(n);
                //menu -> moveover = menu -> moveover ? 1 : 0;
            }
            moveover[k1][k2++] = menu -> moveover ? 1 : 0;
            if(menu -> next == NULL)
                break;
            menu = menu -> next;
            k2 ++;
            if(menu -> text[0] == '-')
                y -= 20;
            y += 25;
        }
    }
    else
    {
        for(i = 0; i < 10; i ++)
            for(j = 0; j < 20; j ++)
                moveover[i][j] = 0;
    }
}

void ClearMenuMoveOver(void *n)
{
    State *s;
    FormMenu *formmenu;
    Menu *menu;
    s = (State *)n;
    formmenu = s -> menu;
    while(formmenu -> next != NULL)
    {
        menu = formmenu -> menu;
        while(menu -> next != NULL)
        {
            menu -> moveover = 0;
            menu = menu -> next;
        }
        formmenu = formmenu -> next;
    }
    s -> isclearmenu = 1;
}

Menu *GetUpMenu(FormMenu *formmenu, Menu *menu)
{
    Menu *menutmp, *menusearch;
    menusearch = menu;
    while(1)
    {
        menutmp = formmenu -> menu;
        while(menutmp -> next != NULL && menutmp -> next != menusearch)
            menutmp = menutmp -> next;
        if(menutmp -> next == menusearch && menutmp -> enabled != 0 && 
            menutmp -> enabled != 4 && menutmp -> enabled != 5)
            return menutmp;
        else if(menutmp -> next == NULL && menutmp -> enabled != 0 &&
            menutmp -> enabled != 4 && menutmp -> enabled != 5)
            return menutmp;
        menusearch = menutmp;
    }
}

Menu *GetDownMenu(FormMenu *formmenu, Menu *menu)
{
    Menu *menutmp;
    menutmp = menu;
    
    while(menutmp != NULL)
    {
        menutmp = menutmp -> next;
        if(menutmp != NULL && menutmp -> enabled != 0 && menutmp -> enabled != 4
           && menutmp -> enabled != 5)
            break;
    }
    
    if(menutmp == NULL)
    {
        menutmp = formmenu -> menu;
        while((menutmp -> enabled == 0 || menutmp -> enabled == 4 || menutmp -> enabled == 5) && menutmp -> next != NULL)
            menutmp = menutmp -> next;
    }
    return menutmp;
}

FormMenu *GetLeftFormMenu(State *s, FormMenu *formmenu)
{
    FormMenu *menutmp;
    menutmp = s -> menu;
    while(menutmp -> next != NULL && menutmp -> next != formmenu)
        menutmp = menutmp -> next;
    return menutmp;
}

FormMenu *GetRightFormMenu(State *s, FormMenu *formmenu)
{
    FormMenu *menutmp;
    menutmp = formmenu;
    menutmp = menutmp -> next;
    if(menutmp == NULL)
        menutmp = s -> menu;
    return menutmp;
}

FormMenu *FindPressedFormMenu(void *n)
{
    State *s;
    Menu *menu;
    FormMenu *formmenu;
    s = (State *)n;
    formmenu = s -> menu;
    while(formmenu -> next != NULL && !formmenu -> pressed)
        formmenu = formmenu -> next;
    if(!formmenu -> pressed)
        return NULL;
    return formmenu;
}    

Menu *FindMoveOverMenu(void *n)
{
    Menu *menu;
    FormMenu *formmenu;
    formmenu = FindPressedFormMenu(n);
    if(formmenu == NULL)
        return NULL;
    if(formmenu -> pressed)
    {
        menu = formmenu -> menu;
        while(menu -> text != NULL)
        {
            if(menu -> moveover)
                return menu;
            if(menu -> next == NULL)
                break;
            menu = menu -> next;
        }
    }
    return NULL;
}

void MenuUp(void *n)
{
    Menu *menu, *menuup;
    FormMenu *formmenu;
    formmenu = FindPressedFormMenu(n);
    if(formmenu == NULL)
        return;
    menu = FindMoveOverMenu(n);
    if(menu != NULL)
        menu -> moveover = 0;
    menuup = GetUpMenu(formmenu, menu);
    if(menuup != NULL)
        menuup -> moveover = 1;
}

void MenuDown(void *n)
{
    Menu *menu, *menudown;
    FormMenu *formmenu;
    formmenu = FindPressedFormMenu(n);
    if(formmenu == NULL)
        return;
    menu = FindMoveOverMenu(n);
    if(menu != NULL)
        menu -> moveover = 0;
    menudown = GetDownMenu(formmenu, menu);
    if(menudown != NULL)
        menudown -> moveover = 1;
}

void FormMenuLeft(void *n)
{
    State *s;
    FormMenu *menu, *menuleft;
    s = (State *)n;
    menu = FindPressedFormMenu(n);
    if(menu == NULL)
        return;
    menu -> pressed = 0;
    menuleft = GetLeftFormMenu(s, menu);
    menuleft -> pressed = 1;
}

void FormMenuRight(void *n)
{
    State *s;
    FormMenu *menu, *menuright;
    s = (State *)n;
    menu = FindPressedFormMenu(n);
    if(menu == NULL)
        return;
    menu -> pressed = 0;
    menuright = GetRightFormMenu(s, menu);
    menuright -> pressed = 1;
}

void AddMenuToFormMenu(Menu *menu, FormMenu *formmenu)
{
    FormMenu *tmp;
    tmp = formmenu;
    while(tmp -> next != NULL)
        tmp = tmp -> next;
    tmp -> menu = menu;
}

void OpenMenu(FormMenu *menu, int n)
{
    int i;
    FormMenu *menutmp;
    menutmp = menu;
    for(i = 0; i < 5; i++)
    {
        if(i == n)
            menutmp -> pressed = !menutmp -> pressed;
        else
            menutmp -> pressed = 0;
        menutmp = menutmp -> next;
    }
}

void OpenMenu0(void *n)
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow)
        return;
    s -> isedit = 0;
    OpenMenu(s -> menu, 0);
}

void OpenMenu1(void *n)
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow)
        return;
    s -> isedit = 0;
    OpenMenu(s -> menu, 1);
}

void OpenMenu2(void *n)
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow)
        return;
    s -> isedit = 0;
    OpenMenu(s -> menu, 2);
}

void OpenMenu3(void *n)
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow)
        return;
    s -> isedit = 0;
    OpenMenu(s -> menu, 3);
}

void OpenMenu4(void *n)
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow)
        return;
    s -> isedit = 0;
    OpenMenu(s -> menu, 4);
}

void ChildTitleContextMenu(void *n)
{
    int t;
    State *s;
    s = (State *)n;
    if(!s -> ischildwindow)
        return;
    if(s -> iscontextmenu && (s -> mouse . key || (s -> keyboard . key & 0xFF00) == ESC || 
      (s -> keyboard . key & 0xff00) == SPACE &&
      (s -> keyboard . modifier & ALT)))
    {
        //CleanUp(n);
        //DrawMainWindow(n);
        //DrawStatusBox(n);
        //DoEvent(s -> redraw, n);
        //CleanUp(n);
        t = s -> ischildwindow;
        s -> ischildwindow = -1;
        switch(t)
        {
            case 1:
            {
                DrawOpenWindow(n);
                break;
            }
            case 2:
            {
                DrawSaveWindow(n);
                break;
            }
            case 3:
            {
                DrawSaveAsWindow(n);
                break;
            }
            case 4:
            {
                DrawFindWindow(n);
                break;
            }
            case 5:
            {
                DrawReplaceWindow(n);
                break;
            }
        }
        s -> mouse . key = 0;
        s -> keyboard . key = -1;
        s -> iscontextmenu = 0;
        if(t < 99)
            s -> isedit = 1;
    }
    else if(s -> mouse . key == 2 && PinRA(
                    s -> mouse . x, s -> mouse . y,
                    s -> childx1, s -> childy1,
                    s -> childx2 - 23, s -> childy1 + 20) || 
                    (s -> keyboard . key & 0xff00) == SPACE &&
                    (s -> keyboard . modifier & ALT))
    {
        CleanUp(n);
        if(!PinRA(
                    s -> mouse . x, s -> mouse . y,
                    s -> childx1, s -> childy1,
                    s -> childx2 - 23, s -> childy1 + 20))
        {
            CleanUp(n);
            s -> mouse . x = s -> childx1;
            s -> mouse . y = s -> childy1;
            SetMouseXY(s -> childx1, s -> childy1);
            CleanUp(n);
        }
        s -> iscontextmenu = 1;
        DrawMenu(n, s -> contextmenu, s -> mouse . x, s -> mouse . y);
        CleanUp(n);
        s -> cmmousex = s -> mouse . x;
        s -> cmmousey = s -> mouse . y;
        //s -> isedit = 0;
    }
}
