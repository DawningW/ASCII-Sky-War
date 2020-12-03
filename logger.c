#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

FILE* file;

void log_init()
{
    file = NULL;
}

void log_close()
{
    if (file) fclose(file);
}

void log_print(enum LOG_LEVEL level, const char* msg, ...)
{
#ifndef _DEBUG
    if (level == LOG_DEBUG) return;
#endif
    va_list args;
    va_start(args, msg);
    switch (level)
    {
    case LOG_DEBUG: fputs("Debug: ", stderr); break;
    case LOG_INFO: fputs("Info: ", stderr); break;
    case LOG_WARNING: fputs("Warning: ", stderr); break;
    case LOG_ERROR: fputs("Error: ", stderr); break;
    case LOG_FATAL: fputs("Fatal: ", stderr); break;
    }
    vfprintf(stderr, msg, args);
    fputc('\n', stderr);
    va_end(args);
}
