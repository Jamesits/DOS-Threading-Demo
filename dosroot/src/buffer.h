struct buffer{
	int id;
	int size;
	char text[NTEXT];
	struct buffer *next;
}buf[NBUF], *freebuf;

void initBuf();
struct buffer *getbuf();
void insert(struct buffer **mq, struct buffer *buff);
void send(char *receiver, char *a, int size);
struct buffer *remov(struct buffer **mq, int sender);
int receive(char *sender, char *b);
