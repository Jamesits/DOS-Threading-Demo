#define FINISHED        0
#define RUNNING 1
#define READY   2
#define BLOCKED 3

typedef int (far * codeptr)(void);
void interrupt (*old_int8)(void);

struct TCB {
    unsigned char       *stack;
    unsigned            ss;
    unsigned            sp;
    char                state;
    char                name[NTEXT];
    struct buffer       *mq;
    semaphore           mutex;
    semaphore           sm;
    struct TCB          *next;
} tcb[NTCB];

struct int_regs {
    unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags, off, seg;
};

void            initTCB();
int             create(char     *name,
                       codeptr  code,
                       int      stck);
void interrupt  swtch();
void            destroy(int id);
void            over();
int             finished();
void            free_all(void);
void interrupt  new_int8();
