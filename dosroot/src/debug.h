#ifndef __DEBUG_H__
#define __DEBUG_H__

// #define DEBUG
#define DEBUG_SEM

#define PrintRegs() { \
    printf("AX=%04x BX=%04x CX=%04x DX=%04x CS=%04x DS=%04x SS=%04x ES=%04x SP=%04x BP=%04x\n", _AX, _BX, _CX, _DX, _CS, _DS, _SS, _ES, _SP, _BP); \
}

void print_tcb();

#endif
