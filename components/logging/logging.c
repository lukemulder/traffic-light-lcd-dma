/*****************************************************************************
* | File        : logging.c
* | Author      : Luke Mulder
* | Function    : Debug utilities for logging system events
* | Info        :
*   Provides a flexible logging mechanism to assist in debugging applications.
******************************************************************************/

#include "logging.h"

void logging(const char *file, int line, const char *func, LogLevel_e level, const char *log_str, ...) {
    va_list args;
    va_start(args, log_str);

    const char* level_str = "";
    switch(level) {
        case ERROR: level_str = ERROR_STR; break;
        case WARNING: level_str = WARNING_STR; break;
        case INFO: level_str = INFO_STR; break;
        default: level_str = NONE_STR; break;
    }

    if(level != NONE) {
        printf("[%s] %s:%d %s() - ", level_str, file, line, func);
        vprintf(log_str, args);
        printf("\n");
    }

    va_end(args);
}