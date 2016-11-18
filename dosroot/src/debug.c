#include <DOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "debug.h"
#include "thread.h"

const char *tcb_status_text[] = {"FINISHED", "RUNNING", "READY", "BLOCKED", "ERROR"};
const char *loglevel_text[] = {"INFO", "DEBUG", "WARNING", "ERROR", "CRITICAL", 0};
#ifdef DEBUG_ENABLE_FILE_REDIRECTION
FILE *debug_file;
#endif

void far init_dbg() {
#ifdef DEBUG_ENABLE_FILE_REDIRECTION
    debug_file = fopen(DEBUG_FILE, "w+");
    if (!debug_file) {
        fprintf(stderr, "Error opening file %s\n", DEBUG_FILE);
        exit(-1);
    }
#endif
    lprintf(INFO, "Compiled time: %s %s\n", __DATE__, __TIME__);
    lprintf(INFO, "Current OS version: %u.%u\n", _osmajor, _osminor);
}

void far end_dbg() {
#ifdef DEBUG_ENABLE_FILE_REDIRECTION
    fclose(debug_file);
#endif
}

int far lprintf(loglevel level, const char far *format, ...)
{
    va_list args;
    int ret;
    int i;
    //begin_transaction();
#ifdef DEBUG_PERROR
    if (errno) perror("thread");
#endif

#ifdef DEBUG_ENABLE_FILE_REDIRECTION
    if (loglevel_text[level]) {
        fprintf(debug_file, "[%u][%s]\t", (unsigned)time(NULL), loglevel_text[level]);
        for (i = 0; i < get_transaction_level(); ++i) fprintf(debug_file, "----");
    }
    va_start(args, format);
    ret = vfprintf(debug_file, format, args);
    va_end(args);
    fflush(debug_file);
#endif

    if (DEBUG_LOG_LEVEL > level) return ret;
    if (loglevel_text[level]) {
        fprintf(DEBUG_OUTPUT_FILE, "[%s]\t", loglevel_text[level]);
        for (i = 0; i < get_transaction_level(); ++i) fprintf(DEBUG_OUTPUT_FILE, "----");
    }
    va_start(args, format);
    ret = vfprintf(DEBUG_OUTPUT_FILE, format, args);
    va_end(args);
#ifdef DEBUG_FLUSH_BUFFER
    fflush(DEBUG_OUTPUT_FILE);
#endif
    //end_transaction();
    return ret;
}

void far print_tcb() {
#ifdef DEBUG_PRINT_TCB
    int i;
    int current_thread_state;
    //begin_transaction();
    lprintf(INFO, ">>>> TCB status\n");
    lprintf(INFO, "\tLast running: %d, Next running: %d, DOS Busy: %d\n", get_last_running_thread_id(), get_next_running_thread_id(), DosBusy());
    lprintf(INFO, "\tID\tName\t\tStack\t\tSS:SP\t\tState\n");
    for (i = 0; i < tcb_count; ++i) {
        current_thread_state = tcb[i].state;
        if (current_thread_state < 0 || current_thread_state > 3) current_thread_state = 4;
        lprintf(INFO, "\t%d\t%s\t\t0x%Fp\t0x%Np:0x%Np\t%d %s\n", i, tcb[i].name, tcb[i].stack, tcb[i].ss, tcb[i].sp, current_thread_state, tcb_status_text[current_thread_state]);
    }
    //end_transaction();
#endif
}
