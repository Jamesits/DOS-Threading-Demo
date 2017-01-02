#include "pinyin.h"
#include "common.h"

void IMSwitch(void *n)
/* Input method switch (en <=> zh) */
{
    State *s;
    s = (State *)n;
    if(s -> isedit)
    {
        s -> chinese = !s -> chinese;
        s -> chipunc = s -> chinese;
        //s -> fullwidth = s -> chinese;
    }
}

void PuncSwitch(void *n)
/* Punctuation switch (en <=> zh) */
{
    State *s;
    s = (State *)n;
    if(s -> isedit && s -> chinese)
    {
        s -> chipunc = !s -> chipunc;
    }
}

void WidthSwitch(void *n)
/* Width switch (fullwidth <=> halfwidth) */
{
    State *s;
    s = (State *)n;
    if(s -> isedit)
    {
        s -> fullwidth = !s -> fullwidth;
    }
}

void CheckIMSwitch(void *n)
/* Check if a switch should be made */
{
    State *s;
    s = (State *)n;
    
    if(s -> ischildwindow)
    /* Force child window to use half-width English input */
    {
        s -> chinese = 0;
        s -> chipunc = 0;
        s -> fullwidth = 0;
        return;
    }
    
    /* Check mouse click event */
    if(s -> isedit && s -> mouse . key &&
       PinRA(s -> mouse . x, s -> mouse . y,
             getmaxx() - 23, getmaxy() - 20, getmaxx() - 6, getmaxy() - 4))
        IMSwitch(n);
    if(s -> isedit && s -> mouse . key &&
       PinRA(s -> mouse . x, s -> mouse . y,
             getmaxx() - 40, getmaxy() - 20, getmaxx() - 24, getmaxy() - 4))
        PuncSwitch(n);
    if(s -> isedit && s -> mouse . key &&
       PinRA(s -> mouse . x, s -> mouse . y,
             getmaxx() - 57, getmaxy() - 20, getmaxx() - 41, getmaxy() - 4))
        WidthSwitch(n);
}

void PinyinInput(void *n)
/* Pinyin input function */
{
    static char buf[50] = {0};
    /* Buffer to save current inputed pinyin */
    
    static char sheng, yun;
    /* Cache to save current inputed initial consonant and vowel */
    
    static char last_chinese = 0;
    /* Cache to save last chinese indicator */
    
    int i, j, k = 0;
    
    int new_sheng = 0, new_yun = 0;
    /* Cache to save new initial consonant and vowel for comparison */
    
    int tmpx;
    /* Save available location for input panel */
    
    char temp[2] = {0};
    /* Temp character to show (a character and a '\0') */
    
    char currectpinyin = 0;
    /* Check if the input is a complete pinyin */
    
    static char lastcurrectpinyin = 0;
    /* Check last state of currectpinyin indicator */
    
    char code[57][5] = {
    /* The main table of pinyin */
        {""},
        {"b"},
        {"c"},
        {"ch"},
        {"d"},
        {"f"},
        {"g"},
        {"h"},
        {"j"},
        {"k"},
        {"l"},
        {"m"},
        {"n"},
        {"p"},
        {"q"},
        {"r"},
        {"s"},
        {"sh"},
        {"t"},
        {"w"},
        {"x"},
        {"y"},
        {"z"},
        {"zh"},
        {"a"},
        {"ai"},
        {"an"},
        {"ang"},
        {"ao"},
        {"e"},
        {"ei"},
        {"en"},
        {"eng"},
        {"er"},
        {"i"},
        {"ia"},
        {"ian"},
        {"iang"},
        {"iao"},
        {"ie"},
        {"in"},
        {"ing"},
        {"iong"},
        {"iu"},
        {"o"},
        {"ong"},
        {"ou"},
        {"u"},
        {"ua"},
        {"uai"},
        {"uan"},
        {"uang"},
        {"ue"},
        {"ui"},
        {"un"},
        {"uo"},
        {"v"}
    };
    
    State *s;
    s = (State *)n;
    
    if(!s -> isedit)
        return;
        
    if(s -> cursorx + 200 > s -> editx2)
    /* If cursor follow is out of place, re-locate it into the edit area */
        tmpx = s -> editx2 - 200;
    else
        tmpx = s -> cursorx;
        
    if(!s -> chinese && s -> chinese != last_chinese)
    /* Re-initialize the indicators */
    {
        s -> ispinyin = 0;
        s -> sheng = 0, s -> yun = 0;
        memset(buf, 0, 50);
        OutPutXY(n);
        last_chinese = s -> chinese;
        return;
    }
    else if(!s -> chinese)
        return;
    last_chinese = s -> chinese;
    /* Save last state of chinese indicator */
    
    j = s -> ispinyin;
    for(i = 0; i < 26; i ++)
	{
		if((s -> keyboard . key & 0xFF00) == s -> map . chs[i] && 
			!(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
        /* Pressed a key among 'A' to 'Z' */
		{
			if((s -> keyboard . modifier & LEFTSHIFT) || (s -> keyboard . modifier & RIGHTSHIFT))
            /* Shift is pressed, so get a capital letter */
				buf[s -> ispinyin ++] = 'A'+i;
			else
            /* Save a lower-case letter */
				buf[s -> ispinyin ++] = 'a'+i;
		}
	}
    
    if((s -> keyboard . key & 0xFF00) == EQUAL && 
        !(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
    /* Set candidate pinyin list to next page */
        s -> pinyinpage ++;
    else if((s -> keyboard . key & 0xFF00) == MINUS && 
            !(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
    /* Set candidate pinyin list to next page */
        s -> pinyinpage --;
    else if((s -> keyboard . key & 0xFF00) == BACKSPACE && 
            !(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT)
            && s -> ispinyin)
    {
        s -> ispinyin --;
        buf[s -> ispinyin] = 0;
        if(s -> ispinyin == 0)
        {
            memset(buf, 0, 50);
            CleanUp(n);
            OutPutXY(n);
            CleanUp(n);
            return;
        }
        j --;
        setfillstyle(SOLID_FILL, 7);
        MouseAway(n);
        bar(tmpx + 4 + 8 * j, s -> cursory + 20, tmpx + 12 + 8 * j, s -> cursory + 32);
        MouseAway(n);
    }
    else if(s -> keyboard . key != -1 && j == s -> ispinyin && s -> ispinyin)
    {
        if((s -> keyboard . key & 0xFF00) == ENTER && 
            !(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
            Insert(n, buf);        
        s -> ispinyin = 0;
        //s -> sheng = 0, s -> yun = 0;
        memset(buf, 0, 50);
        if(j > 0)
        {
            CleanUp(n);
            OutPutXY(n);
            CleanUp(n);
        }
        //s -> keyboard . key = -1;
        return;
    }
    else if(j == 0 && s -> ispinyin == 1)
    {
        MouseAway(n);
        
        DrawButton(n, tmpx, s -> cursory + 16, tmpx + 200, s -> cursory + 56, buf);
        SetColor(8);
        line(tmpx + 6, s -> cursory + 34, tmpx + 194, s -> cursory + 34);
        SetColor(15);
        line(tmpx + 6, s -> cursory + 35, tmpx + 194, s -> cursory + 35);
        MouseAway(n);
    }
    else if(j != s -> ispinyin)
    {
        
        temp[0] = buf[j];
        OutTextxy(n, tmpx + 4 + 8 * j, s -> cursory + 20, temp, 0);
    }
    
    for(i = 1; i < 24; i ++)
    {
        for(j = 0; j < strlen(code[i]); j ++)
        {
            if(code[i][j] != buf[j])
                break;
            else if(j == strlen(code[i]) - 1)
            {
                currectpinyin ++;
                new_sheng = i;
                k = j + 1;
            }
        }
    }
    if(new_sheng != s -> sheng)
    {
        s -> sheng = new_sheng;
        s -> pinyinpage = 0;
    }
    
    for(i = 24; i < 57; i ++)
    {
        for(j = 0; j < strlen(code[i]); j ++)
        {
            if(code[i][j] != buf[j + k])
                break;
            else if(j == strlen(code[i]) - 1)
            {
                currectpinyin ++;
                new_yun = i;
            }
        }
    }
    if(new_yun != s -> yun)
    {
        s -> yun = new_yun;
        s -> pinyinpage = 0;
    }
    
    if(currectpinyin == 1 && currectpinyin != lastcurrectpinyin)
    {
        MouseAway(n);
        DrawButton(n, tmpx, s -> cursory + 16, tmpx + 200, s -> cursory + 56, buf);
        SetColor(8);
        line(tmpx + 6, s -> cursory + 34, tmpx + 194, s -> cursory + 34);
        SetColor(15);
        line(tmpx + 6, s -> cursory + 35, tmpx + 194, s -> cursory + 35);
        OutTextxy(n, tmpx + 4, s -> cursory + 20, buf, 0);
        MouseAway(n);
    }
    lastcurrectpinyin = currectpinyin;
}

void PinyinShow(void *n)
{
    State *s;
    char filename[20];
    char buf[1500] = {0}, temp[50], tmpinsert[3] = {0};
    char a, b;
    int yun, tmpx;
    static char lastyun = -1, lastsheng = -1, lastpage = 0, lastpinyin = 0;
    int t = 0, i;
    FILE *fp;
    
    s = (State *)n;
    if(!s -> isedit || !s -> ispinyin)
    {
        if(!lastpinyin)
        {
            lastyun = -1, lastsheng = -1;
            lastpinyin = s -> ispinyin;
            return;
        }
    }
    if(lastyun == s -> yun && lastsheng == s -> sheng && lastpage == s -> pinyinpage)
        if(!(!s -> ispinyin && lastpinyin))
        {
            lastpinyin = s -> ispinyin;
            return;
        }
    lastyun = s -> yun, lastsheng = s -> sheng, lastpage = s -> pinyinpage;
    
    if(s -> cursorx + 200 > s -> editx2)
        tmpx = s -> editx2 - 200;
    else
        tmpx = s -> cursorx;
        
    sprintf(filename, "pinyin\\%d.txt", s -> sheng);
    if((fp = fopen(filename, "r")) == NULL)
        printf("ERROR!");
    while((fscanf(fp, "%c%c|%d\n", &a, &b, &yun)) != EOF)
    {
        if(yun == s -> yun && t < 1500)
        {
            buf[t ++] = a;
            buf[t ++] = b;
        }
        else if(t != 0)
            break;
    }
    fclose(fp);
    
    if(t == 0)
    {
        lastpinyin = s -> ispinyin;
        return;
    }
    if(!s -> ispinyin && lastpinyin)
    {
        for(i = 1; i < 6; i ++)
            if((s -> keyboard . key & 0xFF00) == s -> nummap . num[i] && 
               !(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
            {
                if(s -> pinyinpage * 10 + i * 2 - 1 >= t)
                    break;
                tmpinsert[0] = buf[s -> pinyinpage * 10 + i * 2 - 2];
                tmpinsert[1] = buf[s -> pinyinpage * 10 + i * 2 - 1];
                Insert(n, tmpinsert);
                s -> keyboard . key = -1;
                break;
            }
        if((s -> keyboard . key & 0xFF00) == SPACE && 
           !(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
        {
            if(s -> pinyinpage * 10 + 1 < t)
            {
                tmpinsert[0] = buf[s -> pinyinpage * 10];
                tmpinsert[1] = buf[s -> pinyinpage * 10 + 1];
                Insert(n, tmpinsert);
                s -> keyboard . key = -1;
            }
        }
        //s -> sheng = 0, s -> yun = 0;
        //lastyun = s -> yun, lastsheng = s -> sheng;
        lastpinyin = s -> ispinyin;
        return;
    }
    setfillstyle(SOLID_FILL, 7);
    MouseAway(n);
    bar(tmpx + 4, s -> cursory + 38, tmpx + 196, s -> cursory + 54);
    MouseAway(n);
    while(s -> pinyinpage * 10 >= t)
        s -> pinyinpage --;
    if(s -> pinyinpage < 0)
        s -> pinyinpage = 0;
    for(i = s -> pinyinpage * 10; i < t && i < (s -> pinyinpage + 1) * 10; i += 2)
    {
        sprintf(temp, "%d.%c%c", (i - s -> pinyinpage * 10) / 2 + 1, buf[i], buf[i + 1]);
        MouseAway(n);
        OutTextxy(n, tmpx + 4 + (i - s -> pinyinpage * 10) * 20, s -> cursory + 38, temp, 0);
        MouseAway(n);
    }
    lastpinyin = s -> ispinyin;
}
