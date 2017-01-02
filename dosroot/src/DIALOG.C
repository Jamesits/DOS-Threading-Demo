#include "common.h"
#include "ui.h"
#include "edit.h"
#include "dialog.h"

void MsgBox(void *n, char *title, char *message)
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow > 0)
        return;
    CleanUp(n);
    /* Hide mouse to solve some bugs */
    s -> ischildwindow = 99;
    DrawMainWindow(n);
    DrawStatusBox(n);
    s -> isedit = 0;
    CheckStatus(n);
    DoEvent(s -> redraw, n);
    /* Do a redraw before draw it */
    s -> childx1 = 120, s -> childy1 = 120;
    s -> childx2 = 360, s -> childy2 = 200;
    DrawWindow(n, s -> childx1, s -> childy1, s -> childx2, s -> childy2, title);
    OutTextxy(n, s -> childx1 + 7, s -> childy1 + 27, message, 0);
    DrawButton(n, s -> childx1 + 25, s -> childy2 - 30,
                  s -> childx1 + 120, s -> childy2 - 5, "确定(Enter)");
    CleanUp(n);
    s -> isedit = 0;
    /* Restore the mouse */
}

void DrawOpenWindow(void *n)
/* Draw "Open" window */
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow > 0)
        return;
    
    InitChildhead(n);
    CleanUp(n);
    /* Hide mouse to solve some bugs */
    
    s -> isedit = 1;
    if(!s -> ischildwindow)
    {
        s -> childx1 = 120, s -> childy1 = 120;
        s -> childx2 = 360, s -> childy2 = 200;
        /* Set the position of the window */
        
        s -> editx1 = s -> childx1 + 77, s -> edity1 = s -> childy1 + 27;
        s -> editx2 = s -> childx2 - 10, s -> edity2 = s -> childy1 + 43;
        if(s -> filehead == NULL)
        {
            s -> cursorx = s -> editx1;
            s -> cursory = s -> edity1;
        }
    }
    s -> ischildwindow = 1;
    DrawMainWindow(n);
    DrawStatusBox(n);
    s -> isedit = 0;
    CheckStatus(n);
    s -> isedit = 1;
    DoEvent(s -> redraw, n);
    /* Do a redraw before draw it */
    
    DrawWindow(n, s -> childx1, s -> childy1, s -> childx2, s -> childy2, "打开文件...");
    OutTextxy(n, s -> childx1 + 7, s -> childy1 + 27, "文件名:", 0);
    DrawTextBox(s -> childx1 + 75, s -> childy1 + 25,
                s -> childx2 - 7, s -> childy1 + 45);
    DrawButton(n, s -> childx1 + 5, s -> childy2 - 30,
                  s -> childx1 + 65, s -> childy2 - 5, "打开(O)");
    DrawButton(n, s -> childx1 + 70, s -> childy2 - 30,
                  s -> childx1 + 130, s -> childy2 - 5, "取消(C)");
    /* Draw all form elements */
    
    CleanUp(n);
    /* Restore the mouse */
}

void DrawSaveWindow(void *n)
/* Draw "Save" window */
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow > 0)
        return;
        
    if(s -> filename[0] != 0)
    {
        //SaveFile(n);
        return;
    }
    
    InitChildhead(n);
    CleanUp(n);
    
    s -> isedit = 1;
    if(!s -> ischildwindow)
    {
        s -> childx1 = 120, s -> childy1 = 120;
        s -> childx2 = 360, s -> childy2 = 200;
        
        s -> editx1 = s -> childx1 + 77, s -> edity1 = s -> childy1 + 27;
        s -> editx2 = s -> childx2 - 10, s -> edity2 = s -> childy1 + 43;
        if(s -> filehead == NULL)
        {   
            s -> cursorx = s -> editx1;
            s -> cursory = s -> edity1;
        }
    }    
    s -> ischildwindow = 2;
    DrawMainWindow(n);
    DrawStatusBox(n);
    s -> isedit = 0;
    CheckStatus(n);
    s -> isedit = 1;
    DoEvent(s -> redraw, n);
    
    DrawWindow(n, s -> childx1, s -> childy1, s -> childx2, s -> childy2, "保存文件...");
    OutTextxy(n, s -> childx1 + 7, s -> childy1 + 27, "文件名:", 0);
    DrawTextBox(s -> childx1 + 75, s -> childy1 + 25,
                s -> childx2 - 7, s -> childy1 + 45);
    DrawButton(n, s -> childx1 + 5, s -> childy2 - 30,
                  s -> childx1 + 65, s -> childy2 - 5, "保存(S)");
    DrawButton(n, s -> childx1 + 70, s -> childy2 - 30,
                  s -> childx1 + 130, s -> childy2 - 5, "取消(C)");
    
    CleanUp(n);
}

void DrawSaveAsWindow(void *n)
/* Draw "Save as" window */
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow > 0)
        return;
    
    InitChildhead(n);
    CleanUp(n);
    
    s -> isedit = 1;
    if(!s -> ischildwindow)
    {
        s -> childx1 = 120, s -> childy1 = 120;
        s -> childx2 = 360, s -> childy2 = 200;
        
        s -> editx1 = s -> childx1 + 77, s -> edity1 = s -> childy1 + 27;
        s -> editx2 = s -> childx2 - 10, s -> edity2 = s -> childy1 + 43;
        if(s -> filehead == NULL)
        {   
            s -> cursorx = s -> editx1;
            s -> cursory = s -> edity1;
        }
    }
    s -> ischildwindow = 3;
    DrawMainWindow(n);
    DrawStatusBox(n);
    s -> isedit = 0;
    CheckStatus(n);
    s -> isedit = 1;
    DoEvent(s -> redraw, n);
    
    DrawWindow(n, s -> childx1, s -> childy1, s -> childx2, s -> childy2, "文件另存为...");
    OutTextxy(n, s -> childx1 + 7, s -> childy1 + 27, "文件名:", 0);
    DrawTextBox(s -> childx1 + 75, s -> childy1 + 25,
                s -> childx2 - 7, s -> childy1 + 45);
    DrawButton(n, s -> childx1 + 5, s -> childy2 - 30,
                  s -> childx1 + 65, s -> childy2 - 5, "保存(S)");
    DrawButton(n, s -> childx1 + 70, s -> childy2 - 30,
                  s -> childx1 + 130, s -> childy2 - 5, "取消(C)");
    
    CleanUp(n);
}

void DrawFindWindow(void *n)
/* Draw "Find" window */
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow > 0)
        return;
    
    InitChildhead(n);
    CleanUp(n);
    
    s -> isedit = 1;
    if(!s -> ischildwindow)
    {
        s -> childx1 = 120, s -> childy1 = 120;
        s -> childx2 = 360, s -> childy2 = 200;
        
        s -> editx1 = s -> childx1 + 92, s -> edity1 = s -> childy1 + 27;
        s -> editx2 = s -> childx2 - 10, s -> edity2 = s -> childy1 + 43;
        if(s -> filehead == NULL)
        {   
            s -> cursorx = s -> editx1;
            s -> cursory = s -> edity1;
        }
    }
    s -> ischildwindow = 4;
    
    DrawMainWindow(n);
    DrawStatusBox(n);
    s -> isedit = 0;
    CheckStatus(n);
    s -> isedit = 1;
    DoEvent(s -> redraw, n);
    
    DrawWindow(n, s -> childx1, s -> childy1, s -> childx2, s -> childy2, "查找...");
    OutTextxy(n, s -> childx1 + 7, s -> childy1 + 27, "查找内容:", 0);
    DrawTextBox(s -> childx1 + 90, s -> childy1 + 25,
                s -> childx2 - 7, s -> childy1 + 45);
    DrawButton(n, s -> childx1 + 5, s -> childy2 - 30,
                  s -> childx1 + 65, s -> childy2 - 5, "查找(F)");
    DrawButton(n, s -> childx1 + 70, s -> childy2 - 30,
                  s -> childx1 + 130, s -> childy2 - 5, "取消(C)");
    
    CleanUp(n);
}

void DrawReplaceWindow(void *n)
/* Draw "Replace" window */
{
    State *s;
    s = (State *)n;
    if(s -> ischildwindow > 0)
        return;
    
    InitChildhead(n);
    InitChildhead2(n);
    CleanUp(n);
    
    s -> isedit = 1;
    if(!s -> ischildwindow)
    {
        s -> childx1 = 120, s -> childy1 = 120;
        s -> childx2 = 360, s -> childy2 = 225;
        
        s -> editx1 = s -> childx1 + 92, s -> edity1 = s -> childy1 + 27;
        s -> editx2 = s -> childx2 - 10, s -> edity2 = s -> childy1 + 43;
        if(s -> filehead == NULL)
        {   
            s -> cursorx = s -> editx1;
            s -> cursory = s -> edity1;
        }
    }
    s -> ischildwindow = 5;
    
    DrawMainWindow(n);
    DrawStatusBox(n);
    s -> isedit = 0;
    CheckStatus(n);
    s -> isedit = 1;
    DoEvent(s -> redraw, n);
    
    DrawWindow(n, s -> childx1, s -> childy1, s -> childx2, s -> childy2, "替换...");
    OutTextxy(n, s -> childx1 + 7, s -> childy1 + 27, "查找内容:", 0);
    OutTextxy(n, s -> childx1 + 7, s -> childy1 + 52, "替换为:", 0);
    DrawTextBox(s -> childx1 + 90, s -> childy1 + 25,
                s -> childx2 - 7, s -> childy1 + 45);
    DrawTextBox(s -> childx1 + 90, s -> childy1 + 50,
                s -> childx2 - 7, s -> childy1 + 70);
    DrawButton(n, s -> childx1 + 5, s -> childy2 - 30,
                  s -> childx1 + 65, s -> childy2 - 5, "查找(F)");
    DrawButton(n, s -> childx1 + 70, s -> childy2 - 30,
                  s -> childx1 + 130, s -> childy2 - 5, "取消(C)");
    
    CleanUp(n);
}

void SwitchTextBox(void *n)
{
    Row *tmp;
    State *s;
    s = (State *)n;
    if(s -> ischildwindow != 5)
        return;
    ClrCur(n);
    if(s -> edity1 == s -> childy1 + 27)
    {
        s -> edity1 += 25;
        s -> edity2 += 25;
    }
    else
    {
        s -> edity1 -= 25;
        s -> edity2 -= 25;
    }
    tmp = s -> childhead;
    s -> childhead = s -> childhead2;
    s -> childhead2 = tmp;
    s -> currentcolumn = 1;
    s -> currentrow = 1;
    End(n);
}

void CloseChildWindow(void *n)
/* Close the child window */
{
    State *s;
    s = (State *)n;
    CleanUp(n);
    ClrCur(n);
    
    FreeChildhead(n);
    if(s -> ischildwindow == 5)
        FreeChildhead2(n);
        
    if(RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
            0, getmaxy() - 25, getmaxx(), getmaxy()))
    /* Status box redrawing needed */
    {
        DrawStatusBox(n);
    }
    
    s -> ischildwindow = 0;
    s -> isedit = 1;
    
    DrawMainWindow(n);
    DrawStatusBox(n);
    DoEvent(s -> redraw, n);
    /* Unset the flag and redraw specific area */
    
    CleanUp(n);
}

void CheckChildButton(void *n)
/* Check if clicked an button on child window */
{
    State *s;
    s = (State *)n;
    
    if(!s -> ischildwindow)
    /* No child window opened, exiting */
        return;
        
    if(s -> mouse . key && PinRA(s -> mouse . x, s -> mouse . y,
                                            s -> childx1 + 70, s -> childy2 - 30,
                                            s -> childx1 + 130, s -> childy2 - 5))
    /* Clicked "Cancel", just close the child window */
    {
        s -> mouse . key = 0;
        CancelButton(n);
    }
    
    if(s -> mouse . key && PinRA(s -> mouse . x, s -> mouse . y,
                                            s -> childx1 + 5, s -> childy2 - 30,
                                            s -> childx1 + 65, s -> childy2 - 5))
    /* Clicked the operational button */
    {
        s -> mouse . key = 0;
        SubmitButton(n);
    }
    
    if(s -> ischildwindow == 99 && s -> mouse . key && PinRA(s -> mouse . x, s -> mouse . y,
                                            s -> childx1 + 25, s -> childy2 - 30,
                                            s -> childx1 + 120, s -> childy2 - 5))
    {
        s -> mouse . key = 0;
        MsgBoxButton(n);
    }
    
    if(s -> ischildwindow == 5 && s -> mouse . key )
    {
        if(s -> edity1 == s -> childy1 + 27 && PinRA(s -> mouse . x, s -> mouse . y,
                                            s -> childx1 + 92, s -> childy1 + 52,
                                            s -> childx2 - 10, s -> childy1 + 68))
        {
            s -> isdrag = 1;
            RedrawMouse(n);
            SwitchTextBox(n);
            //s -> mouse . key = 0;
            s -> isdrag = -1;
            RedrawMouse(n);
            s -> isdrag = 0;
            RedrawMouse(n);
        }
        else if(s -> edity1 == s -> childy1 + 52 && PinRA(s -> mouse . x, s -> mouse . y,
                                            s -> childx1 + 92, s -> childy1 + 27,
                                            s -> childx2 - 10, s -> childy1 + 43))
        {
            s -> isdrag = 1;
            RedrawMouse(n);
            SwitchTextBox(n);
            //s -> mouse . key = 0;
            s -> isdrag = -1;
            RedrawMouse(n);
            s -> isdrag = 0;
            RedrawMouse(n);
        }
    }
}

void MoveChildWindow(void *n)
/* Check and move the child window */
{
    State *s;
    static void *buf, *buf2;
    /* Saving the child window and the contents he covered */
    
    static int last_x, last_y;
    /* Saving the last place of mouse pointer */
    
    static int deltax, deltay;
    /* Saving the margin between the mouse pointer and the window */
     
    static origx1, origy1;
    /* Saving original coordinate for the window */
    
    static redraw = 0;
    
    int i, j;
    void *buftmp;
    
    int tx, ty;
    /* Width and Height of the child window */
    
    s = (State *)n;
    if(!s -> ischildwindow)
        return;
    
    if((!s -> isdrag) && s -> mouse . key == 1 && PinRA(
                    s -> mouse . x, s -> mouse . y,
                    s -> childx1, s -> childy1,
                    s -> childx2 - 23, s -> childy1 + 20))
    /* Dragging start! */
    {
        s -> isdrag = 1;
        /* Set the flag for dragging */
        
        buf = ALLOC(imagesize(s -> childx1, s -> childy1,
                              s -> childx2, s -> childy2));
        /* Memory allocation for saving the child window pixels */
        CheckAlloc((void *)buf);
        
        CleanUp(n);
        
        if(s -> ischildwindow == 5 && s -> edity1 == s -> childy1 + 52)
            SwitchTextBox(n);
        
        getimage(s -> childx1, s -> childy1, s -> childx2, s -> childy2, buf);
        /* Get the child window pixels */
        
        if(RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                  0, 0, getmaxx(), 20) ||
           RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                  0, 0, 7, getmaxy()) ||
           RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                  getmaxx() - 7, 0, getmaxx(), getmaxy()) ||
           RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                  0, getmaxy() - 25, getmaxx(), getmaxy()))
        {
            DrawMainWindow(n);
            DrawStatusBox(n);
        }
        DoEvent(s -> redraw, n);
        /* Redraw the original main window to save original pixels */
        
        //else
        /*if(!s -> dotted)
        {
            //setactivepage(!page);
            buf2 = ALLOC(imagesize(0, 0, getmaxx() / PART, getmaxy() / PART));
            if(buf2 == NULL)exit(1);
            for(i = 0; i < PART; i ++)
                for(j = 0; j < PART; j ++)
                {
                    getimage(i * getmaxx() / PART, j * getmaxy() / PART,
                            (i + 1) * getmaxx() / PART, (j + 1) * getmaxy() / PART, buf2);
                    putimage(i * getmaxx() / PART, j * getmaxy() / PART, buf2, COPY_PUT);
                }
            FREEMEM(buf2);
        }*/
        //if(s -> dotted)
        {
            buf2 = ALLOC(imagesize(s -> childx1, s -> childy1,
                                   s -> childx2, s -> childy2));
            /* Memory allocation for saving the original main window pixels */
            CheckAlloc((void *)buf2);
        
            getimage(s -> childx1, s -> childy1, s -> childx2, s -> childy2, buf2);
            /* Get the original main window pixels */
        }
        
        if(!s -> dotted)
        {
            setactivepage(!s -> page);
            DrawMainWindow(n);
            DrawStatusBox(n);
            DoEvent(s -> redraw, n);
            setactivepage(s -> page);
        }
        
        origx1 = s -> childx1, origy1 = s -> childy1;
        /* Saving original child window coordinate */
        
        putimage(s -> childx1, s -> childy1, buf, COPY_PUT);
        /* Restore the child window */
        
        CleanUp(n);
        deltax = s -> mouse . x - s -> childx1;
        deltay = s -> mouse . y - s -> childy1;
        /* Saving the margin between the mouse pointer and the window */
        
        tx = s -> childx2 - s -> childx1;
        ty = s -> childy2 - s -> childy1;
        SetXRange(deltax, getmaxx() - 1 + deltax - tx);
        SetYRange(deltay, getmaxy() - 22 + deltay - ty);
        
        last_x = s -> mouse . x, last_y = s -> mouse . y;
        /* Saving the last place of mouse pointer */
        
        SetColor(15);    
        setwritemode(1);
        setlinestyle(1,0,1);
        if(s -> dotted)
            rectangle(s -> childx1, s -> childy1, s -> childx2, s -> childy2);
            /* Draw the dotted line frame */        
        
        setlinestyle(0,0,1);
        /* Restore the line style */
    }
    
    if(s -> isdrag && 
      (s -> mouse . x != last_x || s -> mouse . y != last_y))
        if(s -> dotted)
        /* Set to dotted mode */
        {
            SetColor(15);    
            setwritemode(1);
            setlinestyle(1,0,1);
            
            rectangle(s -> childx1, s -> childy1, s -> childx2, s -> childy2);
            /* Draw an dotted rectangle at last location to erase it */
            
            /*if(s -> mouse . x - deltax < 0)
                s -> mouse . x = deltax;
            if(s -> mouse . y - deltay < 0)
                s -> mouse . y = deltay;*/
            tx = s -> childx2 - s -> childx1;
            ty = s -> childy2 - s -> childy1;
            /*if(s -> mouse . x - deltax + tx >= getmaxx())
                s -> mouse . x = getmaxx() - 1 + deltax - tx;
            if(s -> mouse . y - deltay + ty >= getmaxy() - 21)
                s -> mouse . y = getmaxy() - 22 + deltay - ty;*/
            /* Measure to ensure the window to be in the screen range */
                
            s -> childx1 = s -> mouse . x - deltax;
            s -> childy1 = s -> mouse . y - deltay;
            s -> childx2 = s -> childx1 + tx;
            s -> childy2 = s -> childy1 + ty;
            s -> editx1 = s -> childx1 + 77, s -> edity1 = s -> childy1 + 27;
            s -> editx2 = s -> childx2 - 10, s -> edity2 = s -> childy1 + 43;
            if(s -> ischildwindow > 3)
                s -> editx1 += 15;
            if(s -> filehead == NULL)
            {   
                s -> cursorx = s -> editx1;
                s -> cursory = s -> edity1;
            }
            /* Calculate the new window location */
            
            rectangle(s -> childx1, s -> childy1, s -> childx2, s -> childy2);
            /* Draw an dotted rectangle at the new location */
            
            last_x = s -> mouse . x, last_y = s -> mouse . y;
            /* Save the mouse location */
            
            setlinestyle(0, 0, 1);
            /* Restore the line style */
        }
        else
        /* Non-dotted mode */
        /* FIXME: several bugs remaining */
        {
            setactivepage(!s -> page);
            CleanUp(n);
            //clearviewport();
            if(RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                      0, 0, getmaxx(), 20) ||
               RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                      0, 0, 7, getmaxy()) ||
               RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                      getmaxx() - 7, 0, getmaxx(), getmaxy()) ||
               RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                      0, getmaxy() - 25, getmaxx(), getmaxy()))
                redraw = 2;
            putimage(last_x - deltax, last_y - deltay, buf2, COPY_PUT);
            CleanUp(n);
            /*if(s -> mouse . x - deltax < 0)
                s -> mouse . x = deltax, flag = 1;
            if(s -> mouse . y - deltay < 0)
                s -> mouse . y = deltay, flag = 1;*/
            tx = s -> childx2 - s -> childx1;
            ty = s -> childy2 - s -> childy1;
            /*if(s -> mouse . x - deltax + tx >= getmaxx())
                s -> mouse . x = getmaxx() - 1 + deltax - tx, flag = 1;
            if(s -> mouse . y - deltay + ty >= getmaxy() - 21)
                s -> mouse . y = getmaxy() - 22 + deltay - ty, flag = 1;*/
            s -> childx1 = s -> mouse . x - deltax;
            s -> childy1 = s -> mouse . y - deltay;
            s -> childx2 = s -> childx1 + tx;
            s -> childy2 = s -> childy1 + ty;
            s -> editx1 = s -> childx1 + 77, s -> edity1 = s -> childy1 + 27;
            s -> editx2 = s -> childx2 - 10, s -> edity2 = s -> childy1 + 43;
            if(s -> ischildwindow > 3)
                s -> editx1 += 15;
            if(s -> filehead == NULL)
            {   
                s -> cursorx = s -> editx1;
                s -> cursory = s -> edity1;
            }
            CleanUp(n);
            if(RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                      0, 0, getmaxx(), 20) ||
               RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                      0, 0, 7, getmaxy()) ||
               RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                      getmaxx() - 7, 0, getmaxx(), getmaxy()) ||
               RAvsRA(s -> childx1, s -> childy1, s -> childx2, s -> childy2,
                      0, getmaxy() - 25, getmaxx(), getmaxy()) || redraw)
            {
                DrawMainWindow(n);
                DrawStatusBox(n);
                redraw --;
            }
            DoEvent(s -> redraw, n);
            
            getimage(s -> childx1, s -> childy1, s -> childx1 + tx, s -> childy1 + ty, buf2);
            putimage(s -> childx1, s -> childy1, buf, COPY_PUT);
            CleanUp(n);
            
            last_x = s -> mouse . x, last_y = s -> mouse . y;
            setvisualpage(!s -> page);
            delay(5);
            s -> page = !s -> page;
//            CleanUp(n);
        }
    
    if(s -> mouse . release == 1 && s -> isdrag)
    /* Mouse released */
    {
        /*if(s -> page == 1 && !s -> dotted)
        {
            CleanUp(n);
            setactivepage(!s -> page);
            for(i = 0; i < PART; i ++)
                for(j = 0; j < PART; j ++)
                {
                    buftmp = ALLOC(imagesize(0, 0, getmaxx() / PART, getmaxy() / PART));
                    if(buftmp == NULL)exit(1);
                    setactivepage(s -> page);
                    getimage(i * getmaxx() / PART, j * getmaxy() / PART,
                            (i + 1) * getmaxx() / PART, (j + 1) * getmaxy() / PART, buftmp);
                    setactivepage(!s -> page);
                    putimage(i * getmaxx() / PART, j * getmaxy() / PART, buftmp, COPY_PUT);
                    FREEMEM(buftmp);
                }
            setvisualpage(!s -> page);
            CleanUp(n);
            s -> page = !s -> page;
        }*/
        
        s -> isdrag = -1;
        /*if(s -> page == 1)
        {
            setvisualpage(!s -> page);
            s -> page = !s -> page;
        }*/
        
        /*if(s -> childy1 < 20 || redraw)
            DrawMainWindow(n);
        DoEvent(s -> redraw, n);*/
        if(s -> dotted)
        {
            MouseAway(n);
            putimage(origx1, origy1, buf2, COPY_PUT);
            /* Restore the original image */
            
            putimage(s -> childx1, s -> childy1, buf, COPY_PUT);
            /* Put the child window into new place */
            
            MouseAway(n);
        }
        //CleanUp(n);
        
        SetXRange(0, getmaxx());
        SetYRange(0, getmaxy());
        
        FREEMEM(buf2);
        FREEMEM(buf);
        /* Release any allocated memory in this procedure */
        
        s -> isdrag = 0;
    }
}

void CheckEnterSubmit(void *n)
{
    State *s;
    s = (State *)n;
    if(!s -> ischildwindow)
    /* No child window opened, exiting */
        return;
    SubmitButton(n);
    s -> keyboard . key = -1;
}

void SubmitButton(void *n)
{
    MsgBoxButton(n);
    OpenButton(n);
}

void OpenButton(void *n)
{
    char *tmp;
    State *s;
    s = (State *)n;
    if(s -> ischildwindow != 1)
        return;
    tmp = GetChildText(n);
    //FREEMEM(tmp);
    CloseChildWindow(n);
    OpenFile(n, tmp);
}

void MsgBoxButton(void *n)
{
    char *tmp;
    State *s;
    s = (State *)n;
    if(s -> ischildwindow != 99)
        return;
    CloseChildWindow(n);
    if(s -> filehead == NULL)
        NewFile(n);
}

void CancelButton(void *n)
{
    State *s;
    s = (State *)n;
    if(!s -> ischildwindow)
    /* No child window opened, exiting */
        return;
    CloseChildWindow(n);
}
