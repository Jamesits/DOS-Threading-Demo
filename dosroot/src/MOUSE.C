#include "common.h"
#include "mouse.h"

int InitMouse()
{
    union REGS r;
    r.x.ax = 0;
    int86(0x33,&r,&r);
    return(r.x.bx);
}

void ShowMouse(void *n, int x, int y)
{
    /*union REGS r;
    r.x.ax = 0x0001;
    int86(0x33,&r,&r);*/
    State *s;
    s = (State *)n;
    if(getmaxx() - x < 11)
        getimage(x,y,getmaxx(),y+20,s -> mousebuf);
    else
        getimage(x,y,x+11,y+20,s -> mousebuf);
    s -> isput = 1;
    setwritemode(0);
    setcolor(0);
    line(x,y,x+11,y+11);
    line(x+10,y+11,x+8,y+11);
    line(x+7,y+11,x+10,y+19);
    line(x+9,y+20,x+8,y+20);
    line(x+7,y+19,x+4,y+12);
    line(x+3,y+13,x+1,y+15);
    line(x,y+16,x,y+1);
    setcolor(15);
    line(x+1,y+2,x+1,y+14);
    line(x+2,y+3,x+2,y+13);
    line(x+3,y+4,x+3,y+12);
    line(x+4,y+5,x+4,y+11);
    line(x+5,y+6,x+5,y+13);
    line(x+6,y+7,x+6,y+15);
    line(x+7,y+8,x+7,y+10);
    line(x+7,y+14,x+7,y+17);
    line(x+8,y+9,x+8,y+10);
    line(x+8,y+16,x+8,y+19);
    line(x+9,y+10,x+9,y+10);
    line(x+9,y+18,x+9,y+19);
    s -> lastmsx = x;
    s -> lastmsy = y;
}

void HideMouse(void *n, int x, int y)
{
    /*union REGS r;
    r.x.ax = 0x0002;
    int86(0x33,&r,&r);*/
    State *s;
    s = (State *)n;
    if(s -> isput)
        putimage(s -> lastmsx,s -> lastmsy,s->mousebuf,COPY_PUT);
    s -> isput = 0;
}

void GetMouseXY(int *x,int *y)
{
    union REGS r;
    r.x.ax = 0x0003;
    int86(0x33,&r,&r);
    *x = r.x.cx;
    *y = r.x.dx;
}

void SetMouseXY(int x,int y)
{
    union REGS r;
    r.x.ax = 0x0004;
    r.x.cx = x;
    r.x.dx = y;
    int86(0x33,&r,&r);
}

int GetPressInfo(int button)
{
    union REGS r;
    r.x.ax = 0x0005;
    r.x.bx = button;
    int86(0x33,&r,&r);
    return(r.x.bx);
}

int GetReleaseInfo(int button)
{
    union REGS r;
    r.x.ax = 0x0006;
    r.x.bx = button;
    int86(0x33,&r,&r);
    return(r.x.bx);
}

void SetXRange(int min,int max)
{
    union REGS r;
    r.x.ax = 0x0007;
    r.x.cx = min;
    r.x.dx = max;
    int86(0x33,&r,&r);
}

void SetYRange(int min,int max)
{
    union REGS r;
    r.x.ax = 0x0008;
    r.x.cx = min;
    r.x.dx = max;
    int86(0x33,&r,&r);
}

void DrawMouse(int x,int y)
{
    if(x<0||y<0)return;
    //line(x,y,x,y+16);
    //line(x,y+16,x+3,y+13);
    //line(x+4,y+12,x+8,y+20);
    //line(x+12,y+12,x+8,y+12);
    //line(x+8,y+12,x+11,y+18);
    /*line(x,y,x+11,y+11);
    line(x+10,y+11,x+8,y+11);
    line(x+7,y+11,x+10,y+19);
    line(x+9,y+20,x+8,y+20);
    line(x+7,y+19,x+4,y+12);
    line(x+3,y+13,x+1,y+15);
    line(x,y+16,x,y+1);*/
    line(x-8,y,x+8,y);
    line(x,y-8,x,y+8);
}

void DrawMouseEdit(int x,int y)
{
    line(x-3,y+8,x+3,y+8);
    line(x-3,y-8,x+3,y-8);
    line(x,y-8,x,y+8);
}

int PinRA(int x, int y, int x1, int y1, int x2, int y2)
{
    return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}

void LoadMouse(void *n)
{
    int x0,y0;
    State *s;
    s = (State *)n;
    s -> mousebuf = ALLOC(imagesize(0,0,11,20));
    x0=320;
    y0=240;
    InitMouse();
    setwritemode(1);
    SetMouseXY(x0,y0);
    SetColor(0);
}

void RedrawMouse(void *n)
{
    static int last_x = -1, last_y = -1, last_type = 0, last_isdrag = 0;
    int x0, y0;
    State *s;
    s = (State *)n;
    GetMouseXY(&x0, &y0);
    SetColor(15);
    setwritemode(1);
    if(x0 != last_x || y0 != last_y || (last_isdrag != s -> isdrag))
    {
        if(s -> isdrag > 0 || s -> isedit && PinRA(x0, y0, s -> editx1, s -> edity1, 
           s -> editx2, s -> edity2))
        {
            s -> mousetype = 1;
            if(last_type != s -> mousetype)
            {
                HideMouse(n, last_x, last_y);
                if(s -> isdrag > 0)
                    DrawMouse(last_x, last_y);
                else if(!s -> isdrag && !last_isdrag)
                    DrawMouseEdit(last_x, last_y);
            }
        }
        else
        {
            s -> mousetype = 0;
            if(last_type != s -> mousetype)
            {
                if(s -> isdrag > 0)
                    DrawMouse(last_x, last_y);
                else if(!s -> isdrag && !last_isdrag)
                    DrawMouseEdit(last_x, last_y);
                ShowMouse(n, last_x, last_y);
            }
        }
        setwritemode(1);
        if(s -> mousetype)
        {
            if(s -> isdrag > 0)
                DrawMouse(last_x, last_y);
            else if(!s -> isdrag && !last_isdrag)
                DrawMouseEdit(last_x, last_y);
        }
        else
            HideMouse(n, last_x, last_y);
        last_x = x0; last_y = y0;
        setwritemode(1);
        if(s -> mousetype)
            if(s -> isdrag)
                DrawMouse(last_x, last_y);
            else
                DrawMouseEdit(last_x, last_y);
        else
        {
            ShowMouse(n, last_x, last_y);
            //delay(50);
        }
        if(s -> iskeyboard == 1)
            s -> iskeyboard = 0;
        last_type = s -> mousetype;
    }
    last_isdrag = s -> isdrag;
    s -> mouse . key = GetPressInfo(0) ? 1 : GetPressInfo(1) * 2;
    s -> mouse . release = GetReleaseInfo(0) ? 1 : GetReleaseInfo(1) * 2;
    s -> mouse . x = x0;
    s -> mouse . y = y0;
}

void MouseAway(void *n)
{
    static int x0 = 0, y0 = 0, last_drag = 0, last = -1;
    State *s;
    s = (State *)n;
    if(s -> iskeyboard)
        s -> iskeyboard = -1;
    
    SetColor(15);
    setwritemode(1);
    
    if(!s -> mousetype)
    {
        /*if(x0 == 0 && y0 == 0)
        {
            GetMouseXY(&x0, &y0);
            if(x0 == getmaxx() && y0 == getmaxy())
                x0 = y0 = 0;
            else
                SetMouseXY(getmaxx(), getmaxy());
        }
        else
        {
            SetMouseXY(x0, y0);
            x0 = y0 = 0;
        }*/
        GetMouseXY(&x0, &y0);
        if(last)
            HideMouse(n, x0, y0);
        else
            ShowMouse(n, x0, y0);
    }
    else
    {
        if(s -> isdrag)
            DrawMouse(s -> mouse . x, s -> mouse . y);
        else
            DrawMouseEdit(s -> mouse . x, s -> mouse . y);
        //RedrawMouse(n);
    }
    
    if(last_drag != s -> isdrag)
    {
        if(!s -> isdrag)
        {
            DrawMouse(s -> mouse . x, s -> mouse . y);
        }
        last_drag = s -> isdrag;
    }
    
    last = -1 - last;
    
    /*
    if(x0 == -1 && y0 == -1)
    {
        GetMouseXY(&x0, &y0);
        SetMouseXY(-1, -1);
    }
    else
    {
        SetMouseXY(x0, y0);
        x0 = y0 = -1;
    }
    RedrawMouse(n);*/
    /* Changed. Oct 20. A small improvement */
    
    if(s -> iskeyboard)
        s -> iskeyboard = 1;
}
