void f1(void)
{
	long i,j,k;
	for(i=0;i<1000;i++){
		putchar('a');
		for(j=0;j<1000;j++)
			for(k=0;k<100;k++);
	}
}

void f2(void)
{
	long i,j,k;
	for(i=0;i<100;i++){
		putchar('b');
		for(j=0;j<1000;j++)
			for(k=0;k<100;k++);
	}
}

void f3(void)
{
	long i,j,k;
	for(i=0;i<1000;i++){
		putchar('c');
		for(j=0;j<1000;j++)
			for(k=0;k<100;k++);
	}
}

void f4()
{
	int i;
	for(i = 0; i < 10; i++){
		wait(&mutex);
		n++;
		printf(" %d", n);
		signal(&mutex);
		sleep(1);
	}
}

void f5()
{
	int i;
	for(i = 0; i < 5; i++){
		wait(&mutex);
		n--;
		printf(" %d ", n);
		signal(&mutex);
		sleep(1);
	}
}

void prdc()
{
	int tmp, i;
	for(i = 1; i <= 10; i++)
	{
		tmp = i * i;
		printf("prdc %d\n", tmp);
		wait(&empty);
		wait(&mutex);
		intbuf[in] = tmp;
		in = (in + 1) % NBUF;

		signal(&mutex);
		signal(&full);

	}
}

void cnsm()
{
	int tmp, i;
	for(i = 1; i <= 10; i++)
	{
		wait(&full);
		wait(&mutex);
		tmp = intbuf[out];
		out = (out + 1) % NBUF;

		signal(&mutex);
		signal(&empty);
		printf("Out %d: %d\n", i, tmp);
		sleep(2);
	}
}

void sender(void)
{
	int i,j;
	char a[10];
loop:
	for(i=0;i<10;i++){
		strcpy(a,"message");
		a[7]='0'+n;
		a[8]=0;
		send("receiver",a,strlen(a));
		printf("sender:Message \"%s\"  has been sent\n",a);
		n++;
	}
	receive("receiver",a);
	if (strcmp(a,"ok")!=0){
		printf("Not be committed,Message should be resended!\n");
		goto loop;
	}else
		printf("Committed,Communication is finished!\n");
}

void receiver(void)
{
	int i,j,size;
	char b[10];
	for(i=0;i<10;i++){
		b[0]=0;
		while((size=receive("sender",b))==-1);
		printf("receiver: Message is received--");
		for(j=0;j<size;j++)
			putchar(b[j]);
		printf("\n");
	}
	strcpy(b,"ok");
	send("sender",b,3);
}
