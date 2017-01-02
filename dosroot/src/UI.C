#include "common.h"
#include "ui.h"
#include "mouse.h"
#include "han.h"
#include "file.h"
#include "edit.h"

void DrawTextBox(int x1, int y1, int x2, int y2)
/* Draw an text box similar to Win9x */
{
    setwritemode(0);
    setfillstyle(SOLID_FILL, 15);
    bar(x1,y1,x2,y2);
    SetColor(0);
    line(x1-1,y1-1,x1-1,y2+1);
    line(x1-1,y1-1,x2+1,y1-1);
    SetColor(8);
    line(x1-2,y1-2,x1-2,y2+2);
    line(x1-2,y1-2,x2+2,y1-2);
    SetColor(7);
    line(x1-1,y2+1,x2+1,y2+1);
    line(x2+1,y1-1,x2+1,y2+1);
    SetColor(15);
    line(x1-2,y2+2,x2+2,y2+2);
    line(x2+2,y1-2,x2+2,y2+2);
}

void DrawButton(void *n, int x1, int y1, int x2, int y2, char *title)
/* Draw a button on a specific place */
{
    setfillstyle(SOLID_FILL, 7);
    setwritemode(0);
    bar(x1, y1, x2, y2);
    /* Main background */
    
    SetColor(7);
    rectangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2);
    line(x1, y1, x2, y1);
    line(x1, y1, x1, y2);
    SetColor(8);
    line(x2 - 1, y1 + 1, x2 - 1, y2 - 1);
    line(x1 + 1, y2 - 1, x2 - 1, y2 - 1);
    SetColor(0);
    line(x2, y1, x2, y2);
    line(x1, y2, x2, y2);
    SetColor(15);
    line(x1 + 1, y1 + 1, x2 - 1, y1 + 1);
    line(x1 + 1, y1 + 1, x1 + 1, y2 - 1);
    /* Draw four borders */
    
    OutTextxy(n, x1 + 4, y1 + 4, title, 0);
    /* Output the title text */
}

void DrawWindow(void *n, int x1, int y1, int x2, int y2, char *title)
/* Draw an interface similar to Win9x */
{
    State *s;
    int i, j, k, dx, period, active = 1;
    setfillstyle(SOLID_FILL, 7);
    setwritemode(0);
    
    s = (State *)n;
    bar(x1 + 3, y1 + 21, x2 - 3, y2 - 3);
    /*for(i = y1 + 21; i <= y2 - 3; i ++)
        if(s -> edity1 <= i && i <= s -> edity2)
        {
            line(x1 + 3, i, s -> editx1 - 3, i);
            line(s -> editx2 + 4, i, x2 - 3, i);
        }
        else
            line(x1 + 3, i, x2 - 3, i);*/
    /* Main background, same as button */
    
    SetColor(7);
    rectangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2);
    line(x1, y1, x2, y1);
    line(x1, y1, x1, y2);
    SetColor(8);
    line(x2 - 1, y1 + 1, x2 - 1, y2 - 1);
    line(x1 + 1, y2 - 1, x2 - 1, y2 - 1);
    SetColor(0);
    line(x2, y1, x2, y2);
    line(x1, y2, x2, y2);
    SetColor(15);
    line(x1 + 1, y1 + 1, x2 - 1, y1 + 1);
    line(x1 + 1, y1 + 1, x1 + 1, y2 - 1);
    
    if(s -> ischildwindow && (x1 != s -> childx1 || x2 != s -> childx2))
    /* Inactive window, draw the title bar in gray */
    {
        active = 0;
        setfillstyle(SOLID_FILL, 8);
        bar(x1 + 3, y1 + 3, x2 - 3, y1 + 20);
    }
    
    /* Use six colors to make the title bar background shading */
    dx = (x2 - x1 - 6) / 6;
    /* Divide the width to 6 parts */
    
    for(i = 0; active && i < 6; i ++)
    /* Use 6 different colors to draw in their parts */
    {
        setfillstyle(SOLID_FILL, 9 + i);
        /* Using color 9 - 14 */
        
        bar(x1 + 3 + dx * i, y1 + 3, x1 + 3 + dx * (i + 1), y1 + 20);
    }
    bar(x1 + 3 + dx * 6, y1 + 3, x2 - 3, y1 + 20);
    
    for(i = 0; active && i < 6; i ++)
    /* Use random pixels to blurring the boundaries, so they look better */
    {
        if(i > 0)
        /* Use right color to exhaust dyeing the left parts */
            for(j = x1 + dx * i + 2; j > x1 + dx * i - dx * 2 / 3; j -= 1)
            {
                period = rand() % (x1 + dx * i + 3 - j) + 1;
                /* Set the probability depending on how far between the pixel
                 * and the boundary */
                 
                for(k = 3 + y1 + period; k < y1 + 20; k += period)
                {
                    period = rand() % ((x1 + dx * i - j + 3) / 2 + 1) + 1;
                    putpixel(j, k, 9 + i);
                }
            }
        
        if(i < 5)
        /* Use left color to exhaust dyeing the right parts */
            for(j = x1 + dx * (i + 1); j < x1 + dx * (i + 1) + dx * 2 / 3; j ++)
            {
                period = rand() % (j - (x1 + dx * (i + 1)) + 1) + 1;
                for(k = 3 + y1 + period; k < y1 + 20; k += period)
                {
                    period = rand() % ((j - (x1 + dx * (i + 1))) / 2 + 1) + 1;
                    putpixel(j, k, 9 + i);
                }
            }
    }
    /* Draw four borders, same as button, too */
    
    setfillstyle(SOLID_FILL, 7);
    bar(x2 - 22, y1 + 5, x2 - 7, y1 + 17);
    SetColor(15);
    line(x2 - 22, y1 + 5, x2 - 22, y1 + 16);
    line(x2 - 22, y1 + 5, x2 - 8, y1 + 5);
    SetColor(8);
    line(x2 - 8, y1 + 6, x2 - 8, y1 + 16);
    line(x2 - 21, y1 + 16, x2 - 8, y1 + 16);
    SetColor(0);
    line(x2 - 7, y1 + 5, x2 - 7, y1 + 17);
    line(x2 - 22, y1 + 17, x2 - 7, y1 + 17);
    line(x2 - 18, y1 + 8, x2 - 12, y1 + 13);
    line(x2 - 17, y1 + 8, x2 - 11, y1 + 13);
    line(x2 - 18, y1 + 13, x2 - 12, y1 + 8);
    line(x2 - 17, y1 + 13, x2 - 11, y1 + 8);
    /* The exit button 'x' on top right */
    
    OutTextxy(n, x1 + 4, y1 + 4, title, 15 - (!active) * 8);
    /* Output the title text, still same as button */
}

void DrawStatusBox(void *n)
/* Draw an status box similar to Win9x */
{
    int x1=getmaxx()-200,y1=getmaxy()-20,x2=getmaxx()-6,y2=getmaxy()-4;
    DoNothing(n);
    setwritemode(0);
    setfillstyle(SOLID_FILL, 7);
    bar(x1,y1,x2,y2);
    SetColor(8);
    line(x1-1,y1-1,x1-1,y2+1);
    line(x1-1,y1-1,x2+1,y1-1);
    SetColor(15);
    line(x1-1,y2+1,x2+1,y2+1);
    line(x2+1,y1-1,x2+1,y2+1);
}

void DrawMainTextBox(void *n)
/* The main text box */
{
    State *s;
    s = (State *)n;
    if(!s -> ischildwindow)
    {
        s -> editx1 = 10, s -> edity1 = 50;
        s -> editx2 = getmaxx() - 10, s -> edity2 = getmaxy() - 28;
        /*if(s -> filehead == NULL)
        {   
            s -> cursorx = s -> editx1;
            s -> cursory = s -> edity1;
        }*/
    }
    
    DrawTextBox(7, 46, getmaxx() - 7, getmaxy() - 25);
    OutPutMain(n);
    ClrCur(n);
    FlashCur(n);
}

void DrawMainWindow(void *n)
/* Draw main window */
{
    char title[30];
    State *s;
    s = (State *)n;
    if(s -> filename[0] == 0)
        strcpy(title, "无标题 - 记事本");
    else
        sprintf(title, "%s - 记事本", s -> filename);
    setbkcolor(0);
    DrawWindow(n, 0, 0, getmaxx(), getmaxy(), title);
}

void IsExit(void *n)
/* Check whether an window should be closed */
{
    State *s;
    s = (State *)n;
    
    if(!s -> ischildwindow && s -> mouse . key && PinRA(
                    s -> mouse . x, s -> mouse . y, 618, 0, 640, 17))
    /* Clicked the 'x' on main window */
        Exit(n);
    
    if(s -> ischildwindow && (s -> mouse . key && PinRA(
                    s -> mouse . x, s -> mouse . y,
                    s -> childx2 - 22, s -> childy1,
                    s -> childx2, s -> childy1 + 17) || s -> isexit))
    /* Clicked the 'x' on client window */
    {
        CloseChildWindow(n);
        s -> isexit = 0;
        s -> mouse . key = 0;
    }
}

int RAvsRA(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
/* If a RectAngle covers the other one */
{
    return(PinRA(x1, y1, x3, y3, x4, y4) || PinRA(x2, y2, x3, y3, x4, y4) ||
           PinRA(x1, y2, x3, y3, x4, y4) || PinRA(x2, y1, x3, y3, x4, y4) || 
           PinRA(x3, y3, x1, y1, x2, y2) || PinRA(x4, y4, x1, y1, x2, y2) || 
           PinRA(x3, y4, x1, y1, x2, y2) || PinRA(x4, y3, x1, y1, x2, y2));
    /* Just determine if the four corners of a rectangle is in the other one */
}

void SetColor(unsigned int n)
/* Workaround for quick access to change the function */
{
    setcolor(n);
}

void FadingColor(void *n)
/* Color fading while loading and unloading */
{
    int cp[16][3]={
    {0x00,0x00,0x00},
    {0x00,0x00,0x1f},
	{0x00,0x1f,0x00},
	{0x1f,0x00,0x00},
	{0x00,0x1f,0x1f},
	{0x1f,0x1f,0x00},
	{0x1f,0x00,0x1f},
    {0x27,0x27,0x27},
	{0x17,0x17,0x17},
	{0x06,0x0c,0x1e},
	{0x0c,0x14,0x25},
	{0x14,0x1b,0x29},
	{0x1a,0x22,0x2f},
	{0x21,0x29,0x35},
	{0x28,0x30,0x3b},
	{0x3f,0x3f,0x3f}
	};
    /* Manually set all 16 colors.
     * Some colors here are fetched from Windows XP Classic Theme */
    
	int i, j, sum = 20;
    /* Sum is the fading progression */
    
    int delta;
    /* Workaround for different direction between loading and unloading progress */
    
    State *s;
    s = (State *)n;
    delta = s -> isexit;
    
    j = delta * sum;
	while(1)
	{
        PlayMusic(n);
	    for(i=0;i<16;i++)
        {
            setrgbpalette(i, cp[i][0] * j / sum, cp[i][1] * j / sum, cp[i][2] * j / sum);
            setpalette(i, i);
            /* Color fading via calculating percentage of colors */
        }
        Delay(n, 7);
        /* A small delay */
        
        if(j == sum - delta * sum)
            break;
            
        j += (delta ? -1 : 1);
        /* Go on! */
	}
}

void InitColor(void *n)
/* Initialize all colors to black, so the fading could work later */
{
    int i;
    DoNothing(n);
    for(i = 0; i < 16; i ++)
    /* Set all palette to black */
    {
        setrgbpalette(i, 0, 0, 0);
        setpalette(i, i);
    }
}

void ChangeDotted(void *n)
/* Change dotted mode */
{
    State *s;
    s = (State *)n;
    s -> dotted = !s -> dotted;
    
    /* FIXME: Dirty solution */
    s -> menu -> next -> next -> menu -> enabled = 5 - s -> menu -> next -> next -> menu -> enabled;
}

void ChangeHighlight(void *n)
/* Change highlight mode */
{
    State *s;
    s = (State *)n;
    s -> highlight = !s -> highlight;
    
    /* FIXME: Dirty solution */
    s -> menu -> next -> next -> menu -> next -> enabled = 5 - s -> menu -> next -> next -> menu -> next -> enabled;
}

void CheckStatus(void *n)
/* Check and display the status in the main status box */
{
    State *s;
    static int isedit = 0, ischildwindow = 0, chinese = -1, chipunc = -1,
        fullwidth = -1, cursorcolumn = -1, cursorrow = -1;
    /* Memorize last statuses so it won't draw again and again */
    
    char location[20];
    
    int i, x, y;
    s = (State *)n;
    
    if(s -> isdrag)
    /* Disable editing while dragging */
        s -> isedit = 0;
    
    x = getmaxx() - 7, y = getmaxy() - 20;
    /* Define the place to draw */
    
    if(s -> isedit != isedit || ischildwindow != s -> ischildwindow ||
       chinese != s -> chinese || chipunc != s -> chipunc || fullwidth != s -> fullwidth
       || (s -> isedit && !s -> ischildwindow && (s -> currentrow + s -> pagemovecount != cursorrow ||
       s -> currentcolumn != cursorcolumn)))
    /* Status redraw for status bar */
    {
        CleanUp(n);
        
        /* Draw the status on both pages */
        i = !s -> page;
        do
        {
            setactivepage(i);
            
            DrawStatusBox(n);
            if(s -> isedit)
            {                
                setfillstyle(SOLID_FILL, 1);
                bar(x - 16, y, x + 1, y + 16);
                setwritemode(0);
                setcolor(15);
                line(x - 34, y, x - 34, y + 16);
                line(x - 34, y, x - 17, y);
                setcolor(8);
                line(x - 34, y + 16, x - 17, y + 16);
                line(x - 17, y, x - 17, y + 16);
                setcolor(15);
                line(x - 51, y, x - 51, y + 16);
                line(x - 51, y, x - 34, y);
                setcolor(8);
                line(x - 51, y + 16, x - 34, y + 16);
                line(x - 34, y, x - 34, y + 16);
                /* Draw the background */
                
                if(s -> chinese)
                /* Chinese mode enabled */
                {
                    OutTextxy(n, x - 15, y, "中", 15);
                }
                else
                /* Chinese mode disabled 
                 * It really looks like the Win9x En icon :) */
                {
                    OutTextxy(n, x - 15, y, "En", 15);
                }
                
                if(s -> chipunc)
                {
                    OutTextxy(n, x - 32, y - 4, "，", 0);
                    OutTextxy(n, x - 27, y, "。", 0);
                }
                else
                {
                    OutTextxy(n, x - 30, y - 2, ",", 0);
                    OutTextxy(n, x - 25, y + 1, ".", 0);
                }
                
                if(s -> fullwidth)
                {
                    OutTextxy(n, x - 51, y, "Ο", 0);
                    setcolor(0);
                    setfillstyle(SOLID_FILL, 0);
                    floodfill(x - 41, y + 8, 0);
                }
                else
                {
                    setcolor(0);
                    arc(x - 32, y + 3, 175, 255, 14);
                    arc(x - 40, y + 8, 135, 305, 8);
                    setfillstyle(SOLID_FILL, 0);
                    floodfill(x - 46, y + 8, 0);
                }
                
                if(!s -> ischildwindow)
                {
                    sprintf(location, "第%d行,第%d列", s -> currentrow + s -> pagemovecount, s -> currentcolumn);
                    OutTextxy(n, x - 180, y, location, 0);
                }
            }
            i = !i;
            /* Move to another page! */
        }while(i == s -> page);
        
        MouseAway(n);
        
        isedit = s -> isedit;
        ischildwindow = s -> ischildwindow;
        chinese = s -> chinese;
        chipunc = s -> chipunc;
        fullwidth = s -> fullwidth;
        cursorrow = s -> currentrow + s -> pagemovecount;
        cursorcolumn = s -> currentcolumn;
        /* Save the new statuses */
    }
}

void ShowHelp(void *n)
{
    char *help;
    State *s;
    s = (State *)n;
    help = (char *)ALLOC(20 * sizeof(char));
    CheckAlloc((void *)help);
    strcpy(help, "ui.h");
    OpenFile(n, help);
}

void OpenFile(void *n, char *f)
{
    State *s;
    Event *Readerr;
    int l;
    s = (State *)n;
    Readerr = ALLOC(sizeof(Event));
    InitEvent(Readerr);
    RegEvent(Readerr, &ReadErr);
    strcpy(s -> filename, f);
    CleanUp(n);
    DrawMainWindow(n);
    DrawStatusBox(n);
    DoEvent(s -> redraw, n);
    CleanUp(n);
    s -> isedit = 1;
    FREEMEMRow(s -> filehead);
    s -> filehead = NULL;
    s -> filehead = ReadFile(n, f, Readerr);
    
    FREEMEM(f);
    
    FreeEvent(Readerr);
    s -> currentcolumn = 1;
    s -> currentrow = 1;
    if(s -> filehead == NULL)
    {
        memset(s -> filename, 0, 20);
        //s -> filename[0] = 0;
    }
    l = strlen(s -> filename);
    
    if(l > 2 && Lowercase(s -> filename[l - 1]) == 'c' && s -> filename[l - 2] == '.'
    || l > 2 && Lowercase(s -> filename[l - 1]) == 'h' && s -> filename[l - 2] == '.'
    || l > 4 && Lowercase(s -> filename[l - 1]) == 'p' && Lowercase(s -> filename[l - 2]) == 'p'
    && Lowercase(s -> filename[l - 3]) == 'c' && s -> filename[l - 4] == '.')
    {
        if(!s -> highlight)
            ChangeHighlight(n);
    }
    else
    {
        if(s -> highlight)
            ChangeHighlight(n);
    }
    
    CleanUp(n);
    OutPutXY(n);
    CleanUp(n);
}
    
void CleanUp(void *n)
{
    MouseAway(n);
    ClrCur(n);
}
