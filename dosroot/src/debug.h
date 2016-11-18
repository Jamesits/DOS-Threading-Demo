#ifndef __DEBUG_H__
#define __DEBUG_H__

#define DEBUG_PERROR
#define DEBUG_PRINT_TCB
#define DEBUG_ENABLE_FILE_REDIRECTION
#define DEBUG_FILE "DEBUG.LOG"
#define DEBUG_LOG_LEVEL WARNING
#define DEBUG_OUTPUT_FILE stderr
#define DEBUG_FLUSH_BUFFER

typedef enum loglevel {INFO, DEBUG, WARNING, ERROR, CRITICAL, PROMPT} loglevel;

void far print_tcb();
int far lprintf(loglevel level, const char *format, ...);
void far init_dbg();
void far end_dbg();

#define PrintRegs() { \
    lprintf(INFO, "Registers: AX=%04x BX=%04x CX=%04x DX=%04x CS=%04x DS=%04x SS=%04x ES=%04x SP=%04x BP=%04x DI=%04x SI=%04x\n", _AX, _BX, _CX, _DX, _CS, _DS, _SS, _ES, _SP, _BP, _DI, _SI); \
}

#endif
