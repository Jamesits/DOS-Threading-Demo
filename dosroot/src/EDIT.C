#include "edit.h"
#include "common.h"
#include "mouse.h"
#include "file.h"

void OutPutMain(void *n)
{
	int t, tx1, tx2, ty1, ty2;
	State *s;
	s = (State *)n;
	t = s -> ischildwindow;
	tx1 = s -> editx1, tx2 = s -> editx2;
	ty1 = s -> edity1, ty2 = s -> edity2;
	s -> editx1 = 10, s -> edity1 = 50;
    s -> editx2 = getmaxx() - 10, s -> edity2 = getmaxy() - 28;
	s -> ischildwindow = 0;
	OutPutXY(n);
	s -> ischildwindow = t;
	s -> editx1 = tx1, s -> editx2 = tx2;
	s -> edity1 = ty1, s -> edity2 = ty2;
}

void OutPutXY(void *n)
/* put out a txt in a rectangle */
{
	int i,m=0;
	char str[78];
	//char str[100];
	Char *ch;
	Row *rowtmp;
	State *s;
	int num;
	/* the most char a row can store */
	int x1, y1, x2, y2;
	
	x1 = 10, y1 = 50;
	x2 = getmaxx() - 10, y2 = getmaxy() - 28;
	s = (State *)n;
	num = (s -> editx2 - s -> editx1)/8 + 1;
	if(!s -> ischildwindow)
	{
		RowCount(n);
		rowtmp = s -> filehead;
		if(s -> isedit == 1 && s -> filehead != NULL)
		/* judge the edit mode */
		{
			setfillstyle(SOLID_FILL,WHITE);
			bar(x1,y1,x2,y2);
			/* draw the txt rectangle */
			settextstyle(0,0,1);
			setcolor(BLACK);
			do
			{
				ch = rowtmp -> ch;
				for(i = 0; i < 78 &&(i <= num - 2)&&(ch != NULL)&&(ch -> ch != 0); i++)
				{
					str[i] = ch -> ch;
					ch = ch -> next;
				}
				str[i] = '\0';
				/* store the ch in the Struct */
				OutTextxy(n,x1 + 1,y1 + m + 2,str,0);
				m += 16;
				if(i == num - 1)
				/* change the row if it is over the box */
				{
					for(i = 0;ch != NULL;i++)
					{
						str[i] = ch -> ch;
						ch = ch -> next;
					}
					OutTextxy(n,x1 + 1,y1 + m + 2,str,0);
					m += 16;
				}
				rowtmp = rowtmp -> next;
			}while((rowtmp != NULL)&&(m <= y2 - y1));
		}
	}
	else if(s -> ischildwindow && s -> isedit && !s -> isdrag)
	{
		if(s -> childhead != NULL)
		{
			rowtmp = s -> childhead;
			ch = rowtmp -> ch;
			for(i = 0;ch != NULL;i++)
			{
				str[i] = ch -> ch;
				ch = ch -> next;
			}
			setfillstyle(SOLID_FILL,WHITE);
			bar(s -> editx1,s -> edity1,s -> editx2,s -> edity2);
			/* draw the txt rectangle */
			settextstyle(0,0,1);
			setcolor(BLACK);
			OutTextxy(n,s -> editx1,s -> edity1,str,0);
		}
	}
}

char *GetChildText(void *n)
{
	State *s;
	int i;
	Char *ch;
	char *childtext;
	
	childtext = (char *)ALLOC(20*sizeof(char));
	CheckAlloc((void *)childtext);
	s = (State *)n;
	if(s -> childhead == NULL)
		return;
	ch = s -> childhead -> ch;
	for(i = 0;ch != NULL && ch -> ch != 0 && i < 20 ;i++)
	{
		childtext[i] = ch -> ch;
		ch = ch -> next;
	}
	return childtext;
}

char *GetChildText2(void *n)
{
	State *s;
	int i;
	Char *ch;
	char *childtext;
	
	childtext = (char *)ALLOC(20*sizeof(char));
	CheckAlloc((void *)childtext);
	s = (State *)n;
	if(s -> childhead2 == NULL)
		return;
	ch = s -> childhead2 -> ch;
	for(i = 0;ch != NULL;i++)
	{
		childtext[i] = ch -> ch;
		ch = ch -> next;
	}
	return childtext;
}

void PageDown(void *n)
/* move page down by one row */
{
	int i;
	Row *headline,*tmp,*lastline;
	State *s;
	
	s = (State *)n;
	headline = s -> filehead;
	tmp = s -> filehead;
	lastline = NULL;
	/* save the filehead in case of loss it */
	if(s -> isedit == 1)
	/* judge the edit mode */
	{
		setfillstyle(SOLID_FILL,WHITE);
		bar(s -> editx1,s -> edity1,s -> editx2,s -> edity2);
		/* draw the txt rectangle */
		for(i = 0;i <= s -> pagemovecount && headline != NULL; i++)
		{
			lastline = headline;
			headline = headline -> next;
		}
		if(i == s -> pagemovecount + 1)
		{
			s -> pagemovecount = s -> pagemovecount + 1;
			s -> filehead = headline;
		}
		else
			s -> filehead = lastline;
		OutPutXY((void *)s);
		s -> filehead = tmp;
		/* restore the filehead */
	}
}

void PageUp(void *n)
/* move page up by one row */
{
	int i;
	Row *headline,*tmp;
	State *s;
	s = (State *)n;
	headline = s -> filehead;
	tmp = s -> filehead;
	
	/* save the filehead in case of loss it */
	if(s -> isedit == 1)
	/* judge the edit mode */
	{
		setfillstyle(SOLID_FILL,WHITE);
		bar(s -> editx1,s -> edity1,s -> editx2,s -> edity2);
		/* draw the txt rectangle */
		for(i = 0;i < s -> pagemovecount - 1 && headline != NULL; i++)
		{
			headline = headline -> next;
		}
		if(i == s -> pagemovecount - 1)
		{
			s -> pagemovecount = s -> pagemovecount - 1;
			s -> filehead = headline;
		}
		else
			s -> filehead = tmp;
		OutPutXY((void *)s);
		s -> filehead = tmp;
		/* restore the filehead */
	}
}

void BackSpace(void *n)
/*del the NO.N char in Row M*/
{
	State *s;
	Char *q1,*q2;
	Row *q,*line,*line1;
	int i,j,M,N;
	Char *ch;
	
	s = (State *)n;
	if(!s -> isedit || s -> ispinyin)
	/* it is strange here... */
		return;
	if(!s -> ischildwindow)
	{
		q = s -> filehead;
		line = s -> filehead;
		
		M = s -> currentrow;
		N = s -> currentcolumn - 1;
		if(M == 1 && N == 0)
			return;
			
		if(M > 1 && N == 0)
		/* in the first char of a row move to the end of the front row */
		{
			for(i = 1;i < s -> currentrow - 1 ;i++)
			/* find the front row */
			{
				line = line -> next;
			}
			ch = line -> ch;
			for(j = 1;ch != NULL;j++)
			/* caculate the num of the char */
			{
				ch = ch -> next;
			}
			//if(s -> cursory > s -> edity1)
			if(s -> currentrow >= 1)
			{
				//ClrCur(n);
				//s -> cursorx =  j * 8 + s -> editx1 - 8;
				//s -> cursory -= 16;
				s -> currentcolumn = j;
				s -> currentrow -= 1;
				//DrawCur(n);
			}
			M = M - 1;
			N = j;
		}
		for(i = 1; i < M;i++)
		{
			line = line -> next;
		}
		line1 = line -> next;
		q1 = line -> ch;
		
		if(LeftHZ(n) == 1)
		/* BACKSPACE the left char of the cursor when it is a HZ */
		{
			for(i = 1;i < N - 2;i++)
			{
				q1 = q1 -> next;
			}
			q2 = q1 -> next;
			q2 = q2 -> next;
			if(N == 2)
			{
				line -> ch = q2;
			}
			else
			{
				q1 -> next = q2 -> next;
			}
			s -> filehead = q;
			CleanUp(n);
			//s -> cursorx -= 8;
			s -> currentcolumn -= 2;
			OutPutXY(n);
			CleanUp(n);
		}
		else
		{
			for(i = 1;i < N-1;i++)
			{
				q1 = q1 -> next;
			}
			q2 = q1 -> next;
			if(N == 1)
			{
				line -> ch = q1 -> next;
			}
			else
			{
				q1 -> next = q2 -> next;
			}
			s -> filehead = q;
			CleanUp(n);
			//s -> cursorx -= 8;
			s -> currentcolumn -= 1;
			OutPutXY(n);
			CleanUp(n);
		}
	}
	else if(s -> ischildwindow && s -> isedit)
	/* deal with the childwindow edit mode */
	{
		line = s -> childhead;
		q2 = line -> ch;
		N = s -> currentcolumn;
		//printf("%d",N);
		if(N == 1)
			return ;
		else
		{
			if(N == 2)
			{
				q1 = q2 -> next;
				line -> ch = q1;
			}
			else if(N > 2)
			{
				for(i = 1;i < N - 2;i++)
				{
					q2 = q2 -> next;
				}
				//printf("%c",q -> ch);
				q1 = q2 -> next;
				//printf("%c",q1 -> ch);
				q2 -> next = q1 -> next;
			}
			s -> childhead = line;
			CleanUp(n);
			s -> currentcolumn -= 1;
			OutPutXY(n);
			CleanUp(n);
		}
	}
}

void Delete(void *n)
/*del the NO.N char in Row M*/
{
	State *s;
	Char *q1,*q2;
	Row *q,*line,*line1;
	int i,j,M,N;
	Char *ch,*tmpch;
	Char *nextch;
	Char *nextch1;
	
	s = (State *)n;
	if(!s -> isedit || s -> ispinyin)
	/* it is strange here...it has been solved */
		return;
	if(!s -> ischildwindow)
	{
		q = s -> filehead;
		line = s -> filehead;
		
		M = s -> currentrow;
		N = s -> currentcolumn;
		
		for(i = 1; i <= M - 1;i++)
		{
			line = line -> next;
		}
		q1 = line -> ch;
		line1 = line -> next;
		
		ch = line -> ch;
		for(j = 2;ch -> next -> next != NULL;j++)
		{
			ch = ch -> next;
		}
		/* calculate the num of the char in current row */
		
		if((M == s -> rowcount) && (N == j))
			return;
		/* if it is the last chat in a text */
		/*for(i = 1; i <= M;i++)
		{
			line = line -> next;
		}
		q1 = line -> ch;
		line1 = line -> next;
		
		ch = line -> ch;
		for(j = 1;ch != NULL;j++)
		{
			ch = ch -> next;
		}*/
		
		if(N == j)
		/* put the first char of next row in the end of the current row */
		{
			nextch = ch -> next;
			tmpch = line1 -> ch;
			nextch1 = tmpch -> next;
			//printf("%c",tmpch -> next -> ch);
			ch -> next = tmpch;
			tmpch -> next = nextch;
			line1 -> ch = nextch1;
			//printf("%c",nextch1 -> ch);
		}	
		else
		{
			if(RightHZ(n) == 1)
			{
				for(i = 1;i < N - 1;i++)
				{
					q1 = q1 -> next;
				}
				q2 = q1 -> next;
				q2 = q2 -> next;
				if(N == 1)
				{
					line -> ch = q2;
				}
				else
				{
					q1 -> next = q2 -> next;
				}
			}
			else
			{
				for(i = 1;i < N - 1;i++)
				{
					q1 = q1 -> next;
				}
				q2 = q1 -> next;
				if(N == 1)
				{
					line -> ch = q1 -> next;
				}
				else
				{
					q1 -> next = q2 -> next;
				}
			}
		}
		s -> filehead = q;
		CleanUp(n);
		//s -> cursorx -= 8;
		//s -> currentcolumn -= 1;
		OutPutXY(n);
		CleanUp(n);
	}
	else if(s -> ischildwindow && s -> isedit)
	{
		line = s -> childhead;
		q2 = line -> ch;
		N = s -> currentcolumn;
		
		ch = line -> ch;
		for(j = 1;ch -> ch != '\0';j++)
		{
			ch = ch -> next;
		}
		//printf("%d",N);
		if(j == N)
			return ;
			
		if(N == 1)
		{
			q1 = q2 -> next;
			line -> ch = q1;
		}
		else if(N > 1)
		{
			for(i = 1;i < N - 1;i++)
			{
				q2 = q2 -> next;
			}
			q1 = q2 -> next;
			q2 -> next = q1 -> next;
		}
		s -> childhead = line;
		CleanUp(n);
		//s -> cursorx -= 8;
		//s -> currentcolumn -= 1;
		OutPutXY(n);
		CleanUp(n);
	}
}

void SwitchCurrent(int *column, int *row)
/* switch the big text and the childwindow */
{
	static int column2 = 1, row2 = 1;
	static time = 0;
	int tmp;
	tmp = column2; column2 = *column; *column = tmp;
	tmp = row2; row2 = *row; *row = tmp;
	time ++;
	if(time == 2)
	{
		time = 0;
		column2 = 1;
		row2 = 1;
	}
}

void InitChildhead(void *n)
{
	State *s;
	Char *ch;
	Row *head;
	s = (State *)n;
	
	s -> childhead = ALLOC(sizeof(Row));
	CheckAlloc((void *)(s -> childhead));
	head = s -> childhead;
	s -> childhead -> ch = ALLOC(sizeof(Char));
	CheckAlloc((void *)(s -> childhead -> ch));
	ch = head -> ch;
	ch -> ch = '\0';
	//printf("%d",ch -> ch);
	ch -> next = NULL;
	
	SwitchCurrent(&s -> currentcolumn, &s -> currentrow);
}

void InitChildhead2(void *n)
{
	State *s;
	Char *ch;
	Row *head;
	s = (State *)n;
	
	s -> childhead2 = ALLOC(sizeof(Row));
	CheckAlloc((void *)(s -> childhead2));
	head = s -> childhead2;
	s -> childhead2 -> ch = ALLOC(sizeof(Char));
	CheckAlloc((void *)(s -> childhead2 -> ch));
	ch = head -> ch;
	ch -> ch = '\0';
	//printf("%d",ch -> ch);
	ch -> next = NULL;
}

void FreeChildhead(void *n)
{
	State *s;
	s = (State *)n;
	FREEMEMRow(s -> childhead);
	s -> childhead = NULL;
	
	SwitchCurrent(&s -> currentcolumn, &s -> currentrow);
}

void FreeChildhead2(void *n)
{
	State *s;
	s = (State *)n;
	FREEMEMRow(s -> childhead2);
	s -> childhead2 = NULL;
}

void DrawCur(void *n)
/* draw the cursor */
{
	State *s;
	s = (State *)n;
	setwritemode(1);
	setlinestyle(0,0,1);
	setcolor(15);
	if(s -> currentcolumn >= 79)
	{
		s -> cursorx = (s -> currentcolumn - 78 - 1)*8 + s -> editx1;
		s -> cursory = (s -> currentrow + 1 - 1)*16 + s -> edity1;
	}
	/* change the row in the end but currentcolumn remain */
	else
	{
		s -> cursorx = (s -> currentcolumn - 1)*8 + s -> editx1;
		s -> cursory = (s -> currentrow - 1)*16 + s -> edity1;
	}
	/* caculate the cursor position from current(row&column) */
	MouseAway(n);
	line(s -> cursorx ,s -> cursory,s -> cursorx ,s -> cursory + 16);
	MouseAway(n);
	s -> iscursor = !s -> iscursor;
	
	GetCurPos(n);
	/* caculate the currentrow & the currentcolumn of the cursor */
	//printf("%d,%d\t",s -> cursorx,s -> cursory);
}

void ClrCur(void *n)
{
	State *s;
	s = (State *)n;
	if(!(s -> iscursor))
		return;
	if(s -> currentcolumn >= 79)
	{
		s -> cursorx = (s -> currentcolumn - 78 - 1)*8 + s -> editx1;
		s -> cursory = (s -> currentrow + 1 - 1)*16 + s -> edity1;
	}
	/* change the row in the end but currentcolumn remain */
	else
	{
		s -> cursorx = (s -> currentcolumn - 1)*8 + s -> editx1;
		s -> cursory = (s -> currentrow - 1)*16 + s -> edity1;
	}
	/* caculate the cursor position from current(row&column) */
	
	setlinestyle(0,0,1);
	setcolor(15);
	setwritemode(1);
	line(s -> cursorx ,s -> cursory,s -> cursorx ,s -> cursory + 16);
	s -> iscursor = 0;
}

void FlashCur(void *n)
{
	State *s;
	static int last_x = 0, last_y = 0, last_edit = 1;
	s = (State *)n;
	if(s -> currentcolumn >= 79)
	{
		s -> cursorx = (s -> currentcolumn - 78 - 1)*8 + s -> editx1;
		s -> cursory = (s -> currentrow + 1 - 1)*16 + s -> edity1;
	}
	/* change the row in the end but currentcolumn remain */
	else
	{
		s -> cursorx = (s -> currentcolumn - 1)*8 + s -> editx1;
		s -> cursory = (s -> currentrow - 1)*16 + s -> edity1;
	}
	/* caculate the cursor position from current(row&column) */
	
	if(s -> cursortime == -1)
		s -> cursortime = biostime(0, 0);
		/* it means 1/18.4 second */
	if(!s -> isedit)
	{
		ClrCur(n);
		last_edit = 0;
		return;
	}
	setwritemode(1);
	if(last_x != s -> editx1 || last_y != s -> edity1 || last_edit != s -> isedit)
	{
		ClrCur(n);
		s -> cursorx = s -> editx1;
	    s -> cursory = s -> edity1;
		if(!s -> ischildwindow && (s -> currentcolumn != 1 || s -> currentrow != 1))
		{
			//(s -> cursory - (s -> edity1))/16 + 1;
			//(s -> cursorx  - (s -> editx1 ))/8 + 1;
			s -> cursorx += (s -> currentcolumn - 1) * 8 ;
			s -> cursory += (s -> currentrow - 1) * 16;
			/* caculate back from currentcolumn & currentrow to cursor(x,y) */
		}
		s -> cursortime = biostime(0, 0) - 12;
		DrawCur(n);
		last_x = s -> editx1, last_y = s -> edity1;
	}
	if(biostime(0, 0) - s -> cursortime >= 12)
	{
		DrawCur(n);
		s -> cursortime = biostime(0, 0);
	}
	last_edit = 1;
	
	/*if(time(0) - t >= 2)
	{
		ClrCur(s);
		t = time(0);
	}*/
}

void CursorUp(void *n)
/* move cursor up by a row */
{
	Row *headline;
	Char *ch;
	State *s;
	int num,sum,k,i,j;
	/*  avoid to use editx2, that maybe error */
	/*  avoid to use edity2, that maybe error */
	
	int p;
	/* store the HZ position in the front row */
	s = (State *)n;
	num = (s -> editx2 - s -> editx1)/8;
	sum = (s -> edity2 - s -> edity1)/16;
	if(!s -> ischildwindow)
	{
		if(!s -> isedit )
			return;
		//if(s -> cursory == s -> edity1)
		if(s -> currentrow == 1)
		{
			if(s -> filehead != NULL)
			{
				CleanUp(n);
				PageUp(n);
				CleanUp(n);
			}
			/* page up */
			ClrCur(n);
			s -> currentcolumn = 1;
			DrawCur(n);	
			/* deal the situation of the row is the first one */	
		}
		/* PageUp when in front row */
		/*if(s -> cursory >= s -> edity1 + 16)
		{
			ClrCur(n);
			s -> cursory -= 16;
			DrawCur(n);
		}*/
		//if(s -> cursory > s -> edity1)
		if( s -> currentrow > 1)
		{
			headline = s -> filehead;
			for(k = 1;k <= s -> currentrow - 2;k++)
			{
				headline = headline -> next;
			}
			ch = headline -> ch;
			for(i = 1;ch != NULL;i++)
			{
				ch = ch ->next;
			}
			/* calculate the whole num of the front row */
			/*if(s -> currentrow == 1)
			{
				ClrCur(n);
				s -> currentcolumn = 1;
				DrawCur(n);
			}*/
			headline = headline -> next;
			ch = headline -> ch;
			for(j = 1;ch != NULL;j++)
			{
				ch = ch ->next;
			}
			/* calculate the whole num of the current row */
			//if((i >= j) || (s -> cursorx < i*8 + s -> editx1 - 8))
			
			if((i >= j) || (s -> currentcolumn < i - 1))
			{
				if(UpHZ(n) == 1)
				{
					p = FindUpHZPosition(n);
					ClrCur(n);
					s -> currentcolumn = p;
					s -> currentrow -= 1;
					DrawCur(n);
				}
				else
				{
					ClrCur(n);
					//s -> cursory -= 16;
					s -> currentrow -= 1;
					DrawCur(n);
				}
			}
			/* deal the situation of the cursor whose cursor(x) is smaller then the end of front row  */
			else
			{
				ClrCur(n);
				//s -> cursorx = i*8 + s -> editx1 - 16;
				//s -> cursory -= 16;
				s -> currentcolumn = i - 1;
				s -> currentrow -= 1;
				DrawCur(n);
			}
			/* deal the situation of the cursor whose cursor(x) is larger then the end of front row */
			
		}
		s -> cursortime = biostime(0, 0) - 12;
	}
	else if(s -> ischildwindow && s -> isedit)
	{
		ClrCur(n);
		s -> currentcolumn = 1;
		DrawCur(n);
	}
}

void CursorDown(void *n)
/* move cursor down by a row */
{
	Row *headline;
	Char *ch;
	State *s;
	int num,sum,i,j,k;
	/*  avoid to use editx2, that maybe error */
	/*  avoid to use edity2, that maybe error */
	s = (State *)n;
	num = (s -> editx2 - s -> editx1)/8;
	sum = (s -> edity2 - s -> edity1)/16;
	if(!s -> ischildwindow)
	{
		if(!s -> isedit )
			return;
		//if(s -> cursory == sum * 16 + s -> edity1)
		if(s -> currentrow == sum)
		/* PageDown when in last row */
		{
			if(s -> filehead != NULL)
			{
				CleanUp(n);
				PageDown(n);
				CleanUp(n);
				/* in stead of MouseAway(n) */
			}
		}
		/*if(s -> cursory <= sum * 16 + s -> edity1 -16 )
		{
			headline = s -> filehead;
			for(i = 0;i <= s -> currentrow && headline != NULL; i++)
			{
				headline = headline -> next;
			}*/
			/* avoid cursor move down at last line of the txt */
			/*if(i == s -> currentrow + 1)
			{
				ClrCur(n);
				s -> cursory += 16;
				DrawCur(n);
			}*/
		//if(s -> cursory <= (s -> rowcount*16 + s -> edity1 -16))
		if(s -> currentrow == s -> rowcount)
		/* put the cursor in the end of the row when in the last row */
		{
			headline = s -> filehead;
			for(i = 1;i < s -> currentrow && headline != NULL;i++)
			{
				headline = headline -> next;
			}
			ch = headline -> ch;
			for(j = 1;ch -> ch != '\0' && ch -> next != NULL;j++)
			{
				ch = ch -> next;
			}
			ClrCur(n);
			s -> currentcolumn = j;
			DrawCur(n);
		}
		else if(s -> currentrow <= s -> rowcount - 1)
		{
			headline = s -> filehead;
			
			for(k = 1;k <= s -> currentrow - 1;k++)
			{
				headline = headline -> next;
			}
			ch = headline -> ch;
			for(i = 1;ch != NULL;i++)
			{
				ch = ch ->next;
			}
			//if(headline -> next == NULL)
			/* deal the situation of the row is the end one */
			//{
			//	ClrCur(n);
				//s -> cursorx = s -> editx1;
				//s -> cursory += 16;
				//s -> currentcolumn = 1;
				//s -> currentrow += 1;
				//DrawCur(n);
			//}
			headline = headline -> next;
			ch = headline -> ch;
			for(j = 1;ch != NULL;j++)
			{
				ch = ch ->next;
			}
			//if((i <= j) || (s -> cursorx < j*8 + s -> editx1 - 8))
			if((i <= j) || (s -> currentcolumn < j - 1))
			{
				if(DownHZ(n) == 1)
				{
					k = FindDownHZPosition(n);
					ClrCur(n);
					s -> currentrow += 1;
					s -> currentcolumn = k;
					DrawCur(n);
				}
				else
				{
					ClrCur(n);
					//s -> cursory += 16;
					s -> currentrow += 1;
					DrawCur(n);
				}
			}
			/* deal the situation of the cursor whose cursor(x) is smaller then the end of next row  */
			else
			{
				ClrCur(n);
				//s -> cursorx = j*8 + s -> editx1 - 16;
				//s -> cursory += 16;
				s -> currentcolumn = j - 1;
				s -> currentrow += 1;
				DrawCur(n);
			}
			/* deal the situation of the cursor whose cursor(x) is larger then the end of next row */
		}
		s -> cursortime = biostime(0, 0) - 12;
	}
	else if(s -> ischildwindow && s -> isedit)
	{
		headline = s -> childhead;
		ch = headline -> ch;
		for(i = 1;ch -> next != NULL;i++)
		{
			ch = ch -> next;
		}
		ClrCur(n);
		s -> currentcolumn = i;
		DrawCur(n);
	}
}

void CursorLeft(void *n)
{
	int i,j;
	Row *headline;
	Char *ch;
	State *s;
	int num,sum;
	/*  avoid to use editx2, that maybe error */
	/*  avoid to use edity2, that maybe error */
	s = (State *)n;
	headline = s -> filehead;
	/* judge the childwindow mode */
	num = (s -> editx2 - s -> editx1)/8;
	sum = (s -> edity2 - s -> edity1)/16;
	//printf("%d",LeftHZ(n));
	if(!s -> ischildwindow)
	{
		if(!s -> isedit )
			return;
		//if((s -> cursorx <= s -> editx1) && (s -> cursory <= s -> rowcount *16 + s -> edity1))
		if((s -> currentcolumn <= 1) && (s -> currentrow <= s -> rowcount))
		{
			for(i = 1;i < s -> currentrow - 1 ;i++)
			/* find the front row */
			{
				headline = headline -> next;
			}
			ch = headline -> ch;
			for(j = 1;ch != NULL;j++)
			/* caculate the num of the char */
			{
				ch = ch -> next;
			}
			//if(s -> cursory > s -> edity1)
			if(s -> currentrow > 1)
			{
				ClrCur(n);
				/*s -> cursorx =  j * 8 + s -> editx1 - 16;
				s -> cursory -= 16;*/
				s -> currentcolumn = j - 1;
				s -> currentrow -= 1;
				DrawCur(n);
			}
		}
		/* move the cursor from the left to the end char in front row */
		/*else if(s -> cursorx >= s -> editx1 + 8)
		{
			ClrCur(n);
			s -> cursorx -= 8;
			DrawCur(n);
		}*/
		else if(s -> currentcolumn >= 2)
		{
			ClrCur(n);
			if(LeftHZ(n) == 1)
			{
				s -> currentcolumn -= 2;
			}
			else
			{
				s -> currentcolumn -= 1;
			}
			DrawCur(n);
		}
		s -> cursortime = biostime(0, 0) - 12;
	}
	else if(s -> ischildwindow && s -> isedit)
	{
		/*if((s -> cursorx >= s -> editx1 + 8)&&(s -> cursorx <= s -> editx2 ))
		{
			ClrCur(n);
			s -> cursorx -= 8;
			DrawCur(n);
		}*/
		if((s -> currentcolumn >= 2) && (s -> currentcolumn <= num))
		{
			ClrCur(n);
			if(LeftHZ(n) == 1)
			{
				s -> currentcolumn -= 2;
			}
			else
			{
				s -> currentcolumn -= 1;
			}
			DrawCur(n);
		}
		//s -> cursortime = biostime(0, 0) - 12;
	}
}

void CursorRight(void *n)
{
	int i,j;
	Row *headline;
	Row *line;
	Char *ch;
	State *s;
	int num,sum;
	/*  avoid to use editx2, that maybe error */
	/*  avoid to use edity2, that maybe error */
	s = (State *)n;
	//printf("%d",RightHZ(n));
	num = (s -> editx2 - s -> editx1)/8;
	sum = (s -> edity2 - s -> edity1)/16;
	//printf("%d|%d\t",s -> cursorx,num);
	if(!s -> ischildwindow)
	{
		if(!s -> isedit )
			return;
		/*if((s -> cursorx  == (num * 8 + s -> editx1)) && (s -> cursory <= (sum * 16 + s -> edity1) - 16))
		{
			ClrCur(n);
			s -> cursorx = s -> editx1;
			s -> cursory += 16;
			DrawCur(n);
		}*/
		if((s -> currentcolumn == num + 1) && (s -> currentrow <= sum - 1))
		{
			ClrCur(n);
			//printf("inside");
			if(RightHZ(n) == 1)
			{
				s -> currentcolumn += 2;
			}
			else
			{
				s -> currentcolumn += 1;
			}
			//s -> currentrow += 1;
			DrawCur(n);
		}
		/* move the cursor from the right to the left in next row */
		else if(s -> currentcolumn > num + 1)
		{
			headline = s -> filehead;
			/* judge the childwindow mode */
			for(i = 0;i < s -> currentrow ;i++)
			{
				ch = headline -> ch;
				headline = headline -> next;
				for(j = 0;j <= s -> currentcolumn && ch != NULL;j++)
				/* find the last char of the row */
				{
					ch = ch -> next;
				}
			}
			if(j == s -> currentcolumn + 1)
			{
				ClrCur(n);
				/*s -> cursorx += 8;*/
				if(RightHZ(n) == 1)
				{
					s -> currentcolumn += 2;
				}
				else
				{
					s -> currentcolumn += 1;
				}
				DrawCur(n);
			}
			else if(s -> currentrow <= (s -> rowcount - 1))
			{
				ClrCur(n);
				s -> currentcolumn = 1;
				s -> currentrow += 1;
				DrawCur(n);
			}
		}
		/*else if(s -> cursorx <= (num * 8 + s -> editx1 - 8))*/
		else if(s -> currentcolumn <= num)
		/* in the whole row */
		{
			headline = s -> filehead;
			/* judge the childwindow mode */
			for(i = 0;i < s -> currentrow ;i++)
			{
				ch = headline -> ch;
				headline = headline -> next;
				for(j = 0;j <= s -> currentcolumn && ch != NULL;j++)
				/* find the last char of the row */
				{
					ch = ch -> next;
				}
			}
			if(j == s -> currentcolumn + 1)
			{
				ClrCur(n);
				/*s -> cursorx += 8;*/
				if(RightHZ(n) == 1)
				{
					s -> currentcolumn += 2;
				}
				else
				{
					s -> currentcolumn += 1;
				}
				DrawCur(n);
			}
			/*else if(s -> cursory <= ((s -> rowcount - 1) *16 + s -> edity1))
				{
					ClrCur(n);
					s -> cursorx = s -> editx1;
					s -> cursory += 16;
					DrawCur(n);
				}*/
			else if(s -> currentrow <= (s -> rowcount - 1))
			{
				ClrCur(n);
				s -> currentcolumn = 1;
				s -> currentrow += 1;
				DrawCur(n);
			}
		}
		/* move the cursor from the right to the front char in next row */
		s -> cursortime = biostime(0, 0) - 12;
	}
	else if(s -> ischildwindow && s -> isedit)
	{
		line = s -> childhead;
		ch = line -> ch;
		for(j = 1;ch -> next != NULL;j++)
		{
			ch = ch -> next;
		}
		
		if((s -> currentcolumn >= 1)&&(s -> currentcolumn < j))
		{
			ClrCur(n);
			s -> currentcolumn += 1;
			DrawCur(n);
		}
		//s -> cursortime = biostime(0, 0) - 12;
	}
}

void GetCurPos(void *n)
/* caculate the currentrow & the currentcolumn of the cursor */
{
	int testrow;
	State *s;
	s = (State *)n;
	if(!s -> isedit || s -> ischildwindow)
		return;
	//s -> currentrow = (s -> cursory - (s -> edity1))/16 + 1;
	//s -> currentcolumn = (s -> cursorx  - (s -> editx1 ))/8 + 1;
	//testrow = (s -> cursory - (s -> edity1))/16;
}

void RowCount(void *n)
/* count the sum of the row */
{
	Row *count,*tmp;
	State *s;
	s = (State *)n;
	if(!s -> isedit || s -> ischildwindow)
		return ;
	/* save the filehead in Struct State */
	count = s -> filehead;
	if( s -> filehead != NULL)
	{
		tmp = count;
		s -> rowcount = 1;
		while(count -> next != NULL)
		{
			count = count -> next;
			s -> rowcount +=1;
		}
		s -> filehead = tmp;
	}
	else
	{
		s -> rowcount = 0;
	}
}

void MousetoCursor(void *n)
/* left click mouse and then move the cursor to the current position */
{
	Row *headline;
	Char *ch;
	State *s;
	int x,y,key,i,j;
	int k;
	Row *line;
	Char *tmpch;
	s = (State *)n;
	if(!s -> isedit || !PinRA(s -> mouse.x, s->mouse.y, s->editx1, s->edity1,s->editx2,s->edity2))
		return;
	if(!s -> ischildwindow)
	{
		headline = s -> filehead;
		if(headline == NULL)
			return;
		x = (s -> mouse . x - s -> editx1) / 8 + 1;
		/* the currentcolumn the Mouse in */
		y = (s -> mouse . y - s -> edity1) / 16 + 1;
		/* the currentrow the Mouse in */
		key = s -> mouse . key;
		if(key == 1)
		{
			/*ClrCur(n);
			s -> cursortime = biostime(0, 0) - 12;
			s -> cursorx = x*8 + s -> editx1;
			s -> cursory = y*16 + s -> edity1;
			DrawCur(n);*/
			if(y > s -> rowcount)
			/* mouse is under the bottom of the text */
			{
				ClrCur(n);
				s -> cursortime = biostime(0, 0) - 12;
				//s -> cursory = s -> rowcount * 16 + s -> edity1;
				//s -> cursorx = s -> editx1;
				s -> currentrow = s -> rowcount;
				
				line = s -> filehead;
				for(i = 1;i < s -> rowcount && line != NULL;i++)
				{
					line = line -> next;
				}
				if(line == NULL)
					return;
				tmpch = line -> ch;
				for(i = 1;tmpch != NULL && tmpch -> next != NULL;i++)
				{
					tmpch = tmpch -> next;
				}
				k = i ;
				s -> currentcolumn = k;
				DrawCur(n);
			}
			else
			{
				for(i = 1; i < y && headline != NULL; i++)
				{
					headline = headline -> next;
				}
				if(headline == NULL)
					return;
				ch = headline -> ch;
				for(j = 1; ch != NULL;j++)
				{
					ch = ch -> next;
				}
				if(x > j - 2)
				{
					ClrCur(n);
					s -> cursortime = biostime(0, 0) - 12;
					//s -> cursorx = (j - 1)*8 + s -> editx1 - 8;
					//s -> cursory = y*16 + s -> edity1;
					s -> currentcolumn = j - 1;
					s -> currentrow = y;
					DrawCur(n);
				}
				else
				{
					ClrCur(n);
					s -> cursortime = biostime(0, 0) - 12;
					//s -> cursorx = x*8 + s -> editx1;
					//s -> cursory = y*16 + s -> edity1;
					s -> currentcolumn = x ;
					s -> currentrow = y;
					DrawCur(n);
				}
			}
		}
	}
	else if(s -> ischildwindow && s -> isedit)
	{
		
	}
}

void LineFeed(void *n)
/* put the last char of the current row to the head of a new one */
{
	State *s;
	Row *tmprow;
	/* the current row */
	Row *nextrow;
	/* the next row */
	Row *newrow;
	/* the new row */
	Char *last;
	/* the last char of current row */
	Char *tmpch;
	Char *newhead;
	int MaxColumn;
	int i,j,m;
	
	s = (State *)n;
	tmprow = s -> filehead;
	m = s -> currentrow;
	MaxColumn = (s -> editx2 - s -> editx1)/8 + 1;
	/* caculate the column of the row */
	for(i = 1;i <= m - 1 ;i++)
	{
		tmprow = tmprow -> next;
	}
	/* find the current row */
	tmpch = tmprow -> ch;
	for(i = 1;tmpch -> next -> next != NULL;i++)
	{
		tmpch = tmpch -> next;
	}
	/* find the last char */
	last = tmpch;
	//printf("%c",last -> ch);
	nextrow = tmprow -> next;
	//printf("%d|%d",i,MaxColumn);
	if(i == MaxColumn)
	{
		newrow = ALLOC(sizeof(Row));
		CheckAlloc((void *)newrow);
		newrow -> ch = '\0';
		newrow -> next -> ch = NULL;
		//nextrow = tmprow -> next;
		tmprow -> next = newrow;
		newrow -> next = nextrow;
		//printf("inside");
	}
		tmpch -> ch = '\0';
		tmpch -> next = NULL;
		newhead = newrow -> ch;
		newrow -> ch = last;
		last -> next = newhead;
}

void HZInsert(void *n)
/*insert a char in front of the No.N char in Row M*/
{
	State *s;
	int i,M,N;
	Row *head;
	/* the head of edit mode */
	Row *childrow;
	Char *childchar;
	/* the head of edit mode */
	Char *word,*q,*tmpchar;
	Row *line,*line1;
	
	s = (State *)n;
	//printf("%d",last_ischildwindow);
	/* judge the childwindow's state */
	if(!s -> isedit || s -> chinese)
		return;
	word = ALLOC(sizeof(Char));
	CheckAlloc((void *)word);
	M = s -> currentrow;
	N = s -> currentcolumn;
	
	/*for(i=0;i<26;i++)
	{
		if((s -> keyboard . key & 0xFF00) == s -> map . chs[i] && 
			!(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
		{
			if((s->keyboard.modifier & LEFTSHIFT)||(s->keyboard.modifier & RIGHTSHIFT))
				word -> ch = 'A'+i;
			else
				word -> ch = 'a'+i;
		}
	}*/
	/* get the kb key */
	
	if(!s -> ischildwindow)
	/* not in the childwindow */
	{
		line = s -> filehead;
		head = s -> filehead;
		
		for(i = 1; i < M; i++)
		{
			line = line -> next;
		}
		line1 = line -> next;
		q = line -> ch;
		for(i = 1;i < N - 1;i++)
		{
			q = q -> next;
		}
		/* find the right position to insert the char */
		
		if(N == 1)
		/* insert the char in the first of a row */
		{
			line -> ch = word;
			word -> next = q;
		}
		else
		{
			tmpchar = q -> next;
			q -> next = word;
			word -> next = tmpchar;
		}
		//LineFeed(n);
		s -> filehead = head;
		CleanUp(n);
		//s -> cursorx += 8;
		s -> currentcolumn += 1;
		OutPutXY(n);
		CleanUp(n);
	}
	else if(s -> ischildwindow)
	/* in the childwindow */
	{
		/*if(s -> childhead == NULL)
		{
			childrow = ALLOC(sizeof(Row));
			s -> childhead -> ch = ALLOC(sizeof(Char));
			childrow -> ch -> ch = '\0';
			childrow -> ch -> next = NULL;
		}*/
		
		childrow = s -> childhead;
		childchar = childrow -> ch;
		//printf("%d",N);
		if(childchar -> ch == '\0')
		{
			childrow -> ch = word;
			word -> next = childchar;
			childchar = childrow -> ch;
		}
		else
		{
			for(i = 1;i < N - 1;i++)
			{
				//printf("%d",N);
				childchar = childchar -> next;
			}
			tmpchar = childchar -> next;
			childchar -> next = word;
			word -> next = tmpchar;
			s -> childhead = childrow;
		}
		
		CleanUp(n);
		//s -> cursorx += 8;
		s -> currentcolumn += 1;
		OutPutXY(n);
		CleanUp(n);
	}
}

void Insert(void *n,char *hz)
/*insert a string in front of the No.N char in Row M*/
{
	State *s;
	Row *head;
	Row *line;
	Char *ch;
	Char *tmpch;
	Char *nextch;
	Char *word1,*word2;
	Char *word;
	/* get the two char of a HZ */
	//Char *t;char test[100];/* just a test */
	int M,N;
	int i;
	
	s = (State *)n;
	
	if(!s -> ischildwindow)
	{
		M = s -> currentrow;
		N = s -> currentcolumn;
		//word = (Char *)hz;
		head = s -> filehead;
		if(head == NULL)
			return;
		line = head;
		
		//if(!s -> chinese)
		//	return ;
		/* judge the chinese insert mode */
		for(i = 1;i < M && line != NULL ;i ++)
		{
			line = line -> next;
		}
		if(line == NULL)
			return;
		ch = line -> ch;
		for(i = 1;i < N - 1 && ch != NULL ;i++)
		{
			ch = ch -> next;
		}
		if(ch == NULL)
			return;
		nextch = ch -> next;
			
		tmpch = ch;
		if( N == 1 )
		/* input HZ in the head of a Row */
		{
			nextch = line -> ch;
			word1 = ALLOC(sizeof(Char));
			CheckAlloc((void *)word1);
			//word2 = ALLOC(sizeof(Char));
			word1 -> ch = hz[0];
			//word2 -> ch = hz[1];
			line -> ch = word1;
			word1 -> next = nextch;
			//word1 -> next = word2;
			//word2 -> next = nextch;
			tmpch = line -> ch;
			for(i = 1;hz[i] != '\0';i++)
			{
				word2 = ALLOC(sizeof(Char));
				CheckAlloc((void *)word2);
				word2 -> ch = hz[i];
				tmpch -> next = word2;
				word2 -> next = nextch;
				tmpch = word2;
			}
			/*for(i = 0;hz[i] != '\0';i++)
			{
				if(i == 0)
				{
					line -> ch -> ch = hz[i];
					ch = line -> ch;
					tmpch = ch;
				}
				else
				{
					word = malloc(sizeof(Char));
					word -> ch = hz[i];
					tmpch -> next = word;
					word -> next = nextch;
					tmpch = word;
				}
			}*/
			s -> filehead = head;
			CleanUp(n);
			s -> currentcolumn += i;
			OutPutXY(n);
			CleanUp(n);
		}
		else
		{
			for(i = 0;hz[i] != '\0';i++)
			{
				word = ALLOC(sizeof(Char));
				CheckAlloc((void *)word);
				word -> ch = hz[i];
				tmpch -> next = word;
				word -> next = nextch;
				tmpch = word;
			}
			s -> filehead = head;
			CleanUp(n);
			s -> currentcolumn += i;
			OutPutXY(n);
			CleanUp(n);
		}
	//	for(i = 0;hz[i] != '\0';i++)
	//		;
		
	//	if(i == 2)
	//	{
	//		word1 = malloc(sizeof(Char));
	//		word2 = malloc(sizeof(Char));
			//OutTextxy(n,300,10,hz,0);
			//OutTextxy(n,330,10,"测试",0);
			//for(i = 0;/*i <= 2*/hz[i] != '\0';i++)
			//{
	//		word1 -> ch = hz[0];
	//		word2 -> ch = hz[1];
			/*if(word -> ch == -1)
			{
				FREEMEM(word);
				return;
			}*/
	//		ch -> next = word1;
	//		word1 -> next = word2;
	//		word2 -> next = nextch;
	//		s -> filehead = head;
	//		CleanUp(n);
	//		s -> currentcolumn += 2;
	//		OutPutXY(n);
	//		CleanUp(n);
	//	}
	//	if(i == 1)
	//	{
	//		word1 = malloc(sizeof(Char));
	//		word1 -> ch = hz[0];
	//		ch -> next = word1;
	//		word1 -> next = nextch;
	//		s -> filehead = head;
	//		CleanUp(n);
	//		s -> currentcolumn += 1;
	//		OutPutXY(n);
	//		CleanUp(n);
	//	}
		//}
		/*t = line -> ch;
		for(i = 0;t != NULL;i++)
		{
			test[i] = t -> ch;
			t = t -> next;
		}
		test[i] = '\0';
		OutTextxy(n,320,20,test,0);*/
		//printf("%d",i);
	}
	else if(s -> ischildwindow && s -> isedit)
	/* in the childwindow */
	{
		N = s -> currentcolumn;
		head = s -> childhead;
		if(head == NULL)
			return;
		line = head;
		ch = line -> ch;
		nextch = ch;
		if(ch == NULL)
			return;
		if(ch -> ch == '\0')
		{
			word1 = ALLOC(sizeof(Char));
			CheckAlloc((void *)word1);
			word1 -> ch = hz[0];
			line -> ch = word1;
			//printf("%c",hz[0]);
			word1 -> next = ch;
			for(i = 1;hz[i] != '\0';i++)
			{
				word2 = ALLOC(sizeof(Char));
				CheckAlloc((void *)word2);
				word2 -> ch = hz[i];
				ch -> next = word2;
				word2 -> next = nextch;
				ch = word2;
			}
		}
		else
		{
			for(i = 1;i < N - 1 && ch != NULL;i++)
			{
				ch = ch -> next;
			}
			if(ch == NULL)
				return;
			nextch = ch -> next;
			for(i = 0;hz[i] != '\0';i++)
			{
				word2 = ALLOC(sizeof(Char));
				CheckAlloc((void *)word2);
				word2 -> ch = hz[i];
				ch -> next = word2;
				word2 -> next = nextch;
				ch = word2;
			}
		}
		s -> childhead = head;
		CleanUp(n);
		s -> currentcolumn += i;
		OutPutXY(n);
		CleanUp(n);
	}
}

void EnterKey(void *n)
/* add the function of pressing Enter Key */
{
	State *s;
	Row *head;
	Row *line;
	Row *newrow;
	Char *ch;
	Char *tmp;
	int M,N;
	int i;
	
	s = (State *)n;
	
	if((!s -> isedit) || (s -> ischildwindow) || s -> ispinyin)
		return ;
		
	head = s -> filehead;
	M = s -> currentrow;
	/* record the current row */
	N = s -> currentcolumn;
	/* record the current column */
	line = head;
	if(M <= s -> rowcount)
	{
		for(i = 1;i <= M;i++)
		{
			line = line -> next;
		}
		ch = line -> ch;
		for(i = 1;i <= N;i++)
		{
			ch = ch -> next;
		}
		tmp = ch;
		ch = '\0';
		ch -> next = NULL;
		newrow = ALLOC(sizeof(Row));
		CheckAlloc((void *)newrow);
		newrow -> ch = tmp;
	}
	ClrCur(n);
	s -> currentcolumn = 1;
	s -> currentrow += 1;
	DrawCur(n);
}

/*Row *NewFile(char *NewFile, Event *readerr)
 open a new file 
{
	Char *ch;
	Row *head;
	Row *row;
	FILE *fp;
	if(!s -> isedit)
		return ;
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

void ChosenArea(void *n)
/* chose a string and color it BLUE */
{
	State *s;
	int i;
	int x1,y1;
	int x2,y2;
	Row *row;
	Char *ch;
	char str[77];
	if(!s -> ischildwindow ||
	  (!PinRA(s -> mouse.x, s->mouse.y, s->editx1, s->edity1,s->editx2,s->edity2)))
        return;
    s = (State *)n;
    row = s -> filehead;
    if((!s -> isdrag) && s -> mouse . key == 1)
    /* Dragging start! */
    {
		x1 = (s -> mouse . x - s -> editx1) / 8 + 1;
		/* the currentcolumn the Mouse in */
		y1 = (s -> mouse . y - s -> edity1) / 16 + 1;
		/* the currentrow the Mouse in */	
	}
	if(s -> isdrag)
	{
		x2 = (s -> mouse . x - s -> editx1) / 8 + 1;
		/* the currentcolumn the Mouse in */
		y2 = (s -> mouse . y - s -> edity1) / 16 + 1;
		/* the currentrow the Mouse in */
	}
	//setwritemode(1);
	setfillstyle(1,BLUE);
	bar(x1 * 8 + s -> editx1,y1 * 8 + s -> edity1,
	    x2 * 8 + s -> editx1,y2 * 8 + s -> edity1 + 16);
	for(i = 1;i <= y1;i++)
	{
		row = row -> next;
	}
	ch = row -> ch;
	for(i = 1;i <= x1;i++)
	{
		ch = ch -> next;
	}
	for(i = x1;i <= x2;i++)
	{
		str[i - x1] = ch -> ch;
	}
	str[x2 + 1] = '\0';
	OutTextxy(n,x1 * 8 + s -> editx1,y1 * 8 + s -> edity1,str,0);
	
}

/*
void CtrlX(void *n,void *first,void *end)
{
	State *s;
}

void CtrlC(void *n,void *first,void *end)
{
	State *s;
}

void CtrlV(void *n,void *first,void *end)
{
	State *s;
}
*/

//if(strlen(p) > 1 && (((unsigned char)*p >= 0xa1 && (unsigned char)*p <= 0xfe)
//     && ((unsigned char) * (p + 1) >= 0xa1 && (unsigned char) * (p + 1) <= 0xfe)))
/* 在以*p的字符串中,判断是否为汉字 */

int LeftHZ(void *n)
/* there is a HZ on the left side of the cursor */
{
	State *s;
	int m,k;
	int i;
	char p;
	Char *ch;
	Row *row;
	//int Q1 = 0xa1,Q2 = 0xfe;
	s = (State *)n;
	m = s -> currentrow;
	k = s -> currentcolumn;
	k -= 1;
	row = s -> filehead;
	for(i = 1;i < m;i++)
	{
		row = row -> next;
	}
	ch = row -> ch;
	for(i = 1;i < k ;i++)
	{
		ch = ch -> next;
	}
	p = ch -> ch;
	//printf("%c|%d|%d|%d\t",p,Q2,(unsigned char)p,Q1);
	if((unsigned char)(p) >= 0xa1 && (unsigned char)(p) <= 0xfe)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int RightHZ(void *n)
/* there is a HZ on the right side of the cursor */
{
	State *s;
	int m,k;
	int i;
	char p;
	Char *ch;
	Row *row;
	//int Q1 = 0xa1,Q2 = 0xfe;
	s = (State *)n;
	m = s -> currentrow;
	k = s -> currentcolumn;
	k -= 1;
	row = s -> filehead;
	for(i = 1;i < m;i++)
	{
		row = row -> next;
	}
	ch = row -> ch;
	for(i = 1;i < k + 1 ;i++)
	{
		ch = ch -> next;
	}
	p = ch -> ch;
	//printf("%c|%d|%d|%d\t",p,Q2,(unsigned char)p,Q1);
	if((unsigned char)(p) >= 0xa1 && (unsigned char)(p) <= 0xfe)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int UpHZ(void *n)
/* there is a HZ on the top side of the cursor */
{
	State *s;
	int m,k;
	int i;
	char q,p;
	Char *ch;
	Row *row;
	//int Q1 = 0xa1,Q2 = 0xfe;
	s = (State *)n;
	m = s -> currentrow;
	k = s -> currentcolumn;
	k -= 1;
	row = s -> filehead;
	for(i = 1;i < m - 1 && row != NULL;i++)
	{
		row = row -> next;
	}
	ch = row -> ch;
	for(i = 1;i < k && ch != NULL;i++)
	{
		ch = ch -> next;
	}
	q = ch -> ch;
	p = ch -> next -> ch;
	//printf("%c|%c\t",q,p);
	//printf("%c|%d|%d|%d\t",p,Q2,(unsigned char)p,Q1);
	if(((unsigned char)q >= 0xa1 && (unsigned char)q <= 0xfe)
		&&(unsigned char)(p) >= 0xa1 && (unsigned char)(p) <= 0xfe)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int DownHZ(void *n)
/* there is a HZ on the bottom side of the cursor */
{
	State *s;
	int m,k;
	int i;
	char q,p;
	Char *ch;
	Row *row;
	//int Q1 = 0xa1,Q2 = 0xfe;
	s = (State *)n;
	m = s -> currentrow;
	k = s -> currentcolumn;
	m += 1;
	row = s -> filehead;
	for(i = 1;i < m && row != NULL;i++)
	{
		row = row -> next;
	}
	ch = row -> ch;
	for(i = 1;i < k - 1 && ch != NULL;i++)
	{
		ch = ch -> next;
	}
	q = ch -> ch;
	p = ch -> next -> ch;
	//printf("%c|%c\t",q,p);
	//printf("%c|%d|%d|%d\t",p,Q2,(unsigned char)p,Q1);
	if(((unsigned char)q >= 0xa1 && (unsigned char)q <= 0xfe)
		&&(unsigned char)(p) >= 0xa1 && (unsigned char)(p) <= 0xfe)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int FindUpHZPosition(void *n)
/* calculate the HZ positon in the front row */

{
	State *s;
	Row *line;
	Char *ch;
	int i;
	int m,k;
	
	s = (State *)n;
	s = (State *)n;
	line = s -> filehead;
	m = s -> currentrow;
	k = s -> currentcolumn;
	m = m - 1;
	for(i = 1;i < m && line != NULL;i++)
	{
		line = line -> next;
	}
	ch = line -> ch;
	for(i = 1;i < k && ch != NULL;i++)
	{
		if((unsigned char)(ch -> ch) >= 0xa1 
			&& (unsigned char)(ch -> ch) <= 0xfe)
		{
			ch = ch -> next;
			i += 1;
			ch = ch -> next;
			//i += 1;
		}
		else
		{
			ch = ch -> next;
		}
	}
	return (i - 2);
}

int FindDownHZPosition(void *n)
/* calculate the HZ positon in the next row */
{
	State *s;
	Row *line;
	Char *ch;
	int i;
	int m,k;
	
	s = (State *)n;
	s = (State *)n;
	line = s -> filehead;
	m = s -> currentrow;
	k = s -> currentcolumn;
	m = m + 1;
	for(i = 1;i < m && line != NULL;i++)
	{
		line = line -> next;
	}
	ch = line -> ch;
	for(i = 1;i < k && ch != NULL;i++)
	{
		if((unsigned char)(ch -> ch) >= 0xa1 
			&& (unsigned char)(ch -> ch) <= 0xfe)
		{
			ch = ch -> next;
			i += 1;
			ch = ch -> next;
			//i += 1;
		}
		else
		{
			ch = ch -> next;
		}
	}
	return (i - 2);
}

char LeftChar(void *n)
{
	State *s;
	Row *row;
	Char *ch;
	int M,N;
	int i;
	
	s = (State *)n;
	M = s -> currentrow;
	N = s -> currentcolumn;
	row = s -> filehead;
	if(N == 1)
		return 0;
	for(i = 1;i < M;i++)
	{
		row = row -> next;
	}
	ch = row -> ch;
	for(i = 1;i < N - 1;i++)
	{
		ch = ch -> next;
	}
	//printf("%c",ch -> ch);
	return (ch -> ch);
}

void Home(void *n)
/* put the cursor in the first of the currentrow */
{
	State *s;
	
	s = (State *)n;
	if(!s -> ischildwindow)
	{
		ClrCur(n);
		s -> currentcolumn = 1;
		DrawCur(n);
	}
	else if(s -> ischildwindow && s -> isedit)
	{
		ClrCur(n);
		s -> currentcolumn = 1;
		DrawCur(n);
	}
}

void CtrlHome(void *n)
/* put the cursor in the first of the firstrow */
{
	State *s;
	
	s = (State *)n;
	
	ClrCur(n);
	s -> currentcolumn = 1;
	s -> currentrow = 1;
	DrawCur(n);	
}

void End(void *n)
/* put the cursor in the end of the currentrow */
{
	State *s;
	int i;
	Row *line;
	Char *ch;
	s = (State *)n;
	
	if(!s -> ischildwindow)
	{
		line = s -> filehead;
		for(i = 1;i < s -> currentrow && line != NULL;i++)
		{
			line = line -> next;
		}
		ch = line -> ch;
		for(i = 1;ch != NULL && ch -> next != NULL;i++)
		{
			ch = ch -> next;
		}
		ClrCur(n);
		s -> currentcolumn = i;
		DrawCur(n);
	}
	else if(s -> ischildwindow && s -> isedit)
	{
		line = s -> childhead;
		ch = line -> ch;
		for(i = 1;ch != NULL && ch -> next != NULL;i++)
		{
			ch = ch -> next;
		}
		ClrCur(n);
		s -> currentcolumn = i;
		DrawCur(n);
	}
}

void CtrlEnd(void *n)
/* put the cursor in the end of the currentrow */
{
	State *s;
	int i;
	Row *line;
	Char *ch;
	
	s = (State *)n;
	line = s -> filehead;
	for(i = 1;i != s -> rowcount;i++)
	{
		line = line -> next;
	}
	ch = line -> ch;
	for(i = 1;ch != NULL && ch -> next != NULL;i++)
	{
		ch = ch -> next;
	}
	ClrCur(n);
	s -> currentcolumn = i;
	s -> currentrow = s -> rowcount;
	DrawCur(n);
}
