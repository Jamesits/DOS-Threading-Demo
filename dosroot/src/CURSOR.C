void Cursor(void *n)
{
	int key,i;
	int x,y;
    State huge *s;
    s = (State huge *)n;
	x = s -> editx1;
	y = s -> edity1;
	MoveCur(x,y);
}

void DrawCur(int x,int y)
{
	setlinestyle(0,0,3);
	setcolor(BLUE);
	line(x,y,x,y+16);
}

void ClrCur(int x,int y)
{
	setlinestyle(0,0,3);
	setcolor(WHITE);
	line(x,y,x,y+16);
}

void MoveCur(int x,int y)
{
	int key;
	long t;
	t = time(0);
	while(key != ESC)
	{
		key = bioskey(1);
		if(time(0) - t == 1)
		{
			DrawCur(x,y);
		}
		if(time(0) - t == 2)
		{
			ClrCur(x,y);
			t = time(0);
		}
		if(key)
			key = bioskey(0);
		if((key == UP)||(key == DOWN)||(key == LEFT)||(key == RIGHT))
		{
			if((key == UP)&&(y >= 32))
			{
				ClrCur(x,y);
				y -= 16;
			}
			if((key == DOWN)&&(y <= 400))
			{
				ClrCur(x,y);
				y += 16;
			}
			if((key == LEFT)&&(x >= 24))
			{
				ClrCur(x,y);
				x -= 8;
			}
			if((key == RIGHT)&&(x <= 600))
			{
				ClrCur(x,y);
				x += 8;
			}
		}
	}
	ClrCur(x,y);
}
