#include "common.h"
#include "han.h"

char Lowercase(char ch)
{
    if('A' <= ch && ch <= 'Z')
	return (ch + 'a' - 'A');
    return ch;
}

int NotNameChar(char ch)
{
    if('a' <= ch && ch <= 'z')
	return 0;
    if('A' <= ch && ch <= 'Z')
	return 0;
    if('0' <= ch && ch <= '9')
	return 0;
    if(ch == '_')
	return 0;
    return 1;
}

int IsNumber(char ch)
{
    if('0' <= ch && ch <= '9')
	return 1;
    return 0;
}

void OpenHZK(void *n)
/* Changed. Oct 18. Open the HZK file on the program loading progress */
{
    State *s;
    s = (void *)n;
    s -> hzkfile = fopen("HZK16", "rb");
    if(s -> hzkfile == NULL)
    /* Failed to open the HZK file */
    {
	outtextxy(10, 10, "Cannot open hzk file!\n");
	exit(1);
    }
}

void CloseHZK(void *n)
/* Changed. Oct 18. Close the HZK file when closing program */
{
    State *s;
    s = (void *)n;
    fclose(s -> hzkfile);
}

void disp_hz(void *n,int left,int top,unsigned char byte1,unsigned char byte2,int color)
/* Show a specific Chinese Character */
{
    unsigned char buf[32];
    unsigned char mark;
    long p;
    int i, j, y;
    int quma, weima;
    /* Qu Wei Code */
    
    State *s;
    s = (void *)n;
    if((byte1 >= 0xa1 && byte1 <= 0xfe) && (byte2 >= 0xa1 && byte2 <= 0xfe))
    /* Make sure it is really a Chinese Character */
    {
	quma = byte1 - 0xa0;
	weima = byte2 - 0xa0;
	/* Calculate the Qu Wei Code */
	
	p = (quma - 1) * 94 + weima - 1;
	p *= 32;
	fseek(s -> hzkfile, (long)p, SEEK_SET);
	/* Seeking the character in the HZK file */
	
	fread(buf, sizeof(unsigned char), 32, s -> hzkfile);
	/* Read the Chinese Character Module */
	
	for(i = 0, y = top; i < 31; i += 2, y ++)
	    for(mark = 0x80, j = 0; mark > 0; mark = mark >> 1, j++)
	    {
		if((buf[i] & mark) != 0)
		    putpixel(left + j, y, color);
		if((buf[i + 1] & mark) != 0)
		    putpixel(left + j + 8, y, color);
		/* Put every pixel in the module */
	    }
    }
}

void OutTextxy(void *n, int x, int y, char *p, int color)
/* Output a normal string that may include any character including Chinese */
{
    char blue[32][10];
    char q[2];

    int oldcolor, i, j, l, k = 0;
    char lp = 0;
    void disp_hz(void *n, 
		int left, int top, unsigned char byte1, unsigned char byte2, int color);
    State *s;
    s = (void *)n;
		
    oldcolor=getcolor();
    /* Save the original color */
    
    strcpy(blue[0], "char");
    strcpy(blue[1], "double");
    strcpy(blue[2], "enum");
    strcpy(blue[3], "float");
    strcpy(blue[4], "int");
    strcpy(blue[5], "long");
    strcpy(blue[6], "short");
    strcpy(blue[7], "signed");
    strcpy(blue[8], "struct");
    strcpy(blue[9], "union");
    strcpy(blue[10], "unsigned");
    strcpy(blue[11], "void");
    strcpy(blue[12], "for");
    strcpy(blue[13], "do");
    strcpy(blue[14], "while");
    strcpy(blue[15], "break");
    strcpy(blue[16], "continue");
    strcpy(blue[17], "if");
    strcpy(blue[18], "else");
    strcpy(blue[19], "goto");
    strcpy(blue[20], "switch");
    strcpy(blue[21], "case");
    strcpy(blue[22], "default");
    strcpy(blue[23], "return");
    strcpy(blue[24], "auto");
    strcpy(blue[25], "extern");
    strcpy(blue[26], "register");
    strcpy(blue[27], "static");
    strcpy(blue[28], "const");
    strcpy(blue[29], "sizeof");
    strcpy(blue[30], "typedef");
    strcpy(blue[31], "volatile");
    
    SetColor(color);
    while(*p)
    {
	if(strlen(p) > 1 && (((unsigned char)*p >= 0xa1 && (unsigned char)*p <= 0xfe)
	     && ((unsigned char) * (p + 1) >= 0xa1 && (unsigned char) * (p + 1) <= 0xfe)))
	/* It is a Chinese Character */
	{
		if((x + 16) > getmaxx() || (y + 16) > getmaxy())
		/* Out of screen range */
		    return;
		
		if(k == 0)
		    SetColor(color);
		else
		    k -= 2;
		
		disp_hz(n, x, y, *p, *(p+1), getcolor());
		/* Changed. Oct 18. Provide pointer n to get the HZK file pointer */
		
		p += 2;
		x += 16;
		moveto(x, y);
	}
	else
	{
		moveto(x, y);
		*q = *p;
		*(q + 1) = '\0';
		
		setusercharsize(1, 1, 3, 2);
		settextstyle(TRIPLEX_FONT, HORIZ_DIR, 0);
		/* FIXME: Scaling no use at all */
		
		if(s -> isedit && !s -> ischildwindow && !s -> ispinyin && s -> highlight)
		{
		    i = 0;
		    if(*p == '\"' && !k)
		    {
			SetColor(2);
			k ++;
			while(*(p + k) != '\"' && k < 100)
			    k ++;
			k ++;
		    }
		    
		    if(*p == '\'' && !k)
		    {
			SetColor(2);
			k ++;
			while(*(p + k) != '\'' && k < 100)
			    k ++;
			k ++;
		    }
		    
		    if(*p == '/' && *(p + 1) == '/' && !k)
		    {
			SetColor(7);
			k = 99;
		    }
		    
		    if(*p == '/' && *(p + 1) == '*' && !k)
		    {
			SetColor(7);
			while((*(p + k) != '*' || *(p + k + 1) != '/') && k < 100)
			    k ++;
			k += 2;
		    }
		    
		    if(*p == '#' && !k)
		    {
			SetColor(3);
			k ++;
			while(*(p + k) != ' ' && k < 100)
			    k ++;
			k ++;
		    }
		    
		    if(IsNumber(*p) && !k && NotNameChar(lp))
		    {
			SetColor(6);
			k ++;
			while(IsNumber(*(p + k)) && k < 100)
			    k ++;
			if(!NotNameChar(*(p + k)))
			k = 0;
		    }
		    
		    for(i = 0; NotNameChar(lp) && !k && i < 32; i ++)
		    {
			l = strlen(blue[i]);
			for(j = 0; j < l; j ++)
			    if(*(p + j) != blue[i][j])
				break;
			if(j == l && NotNameChar(*(p + l)))
			{
			    SetColor(9);
			    k = l;
			    break;
			}
		    }
		}
		
		if(k == 0)
		    SetColor(color);
		else
		    k --;
		
		outtextxy(x, y+4, q);
		x += 8;
		lp = *p;
		p ++;
		/* Go to next character */
	}
    }
    SetColor(oldcolor);
}


