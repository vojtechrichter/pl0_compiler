#include "logger.h"

void handle_err(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    fprintf(stderr, "\t[INTERNAL_ERROR]: ");
    vfprintf(stderr, format, args);

    va_end(args);

    exit(EXIT_FAILURE);
}

void log_warning(const char *format, ...)
{

    va_list args;
    va_start(args, format);

    fprintf(stdout, "\t[INTERNAL_WARNING]: ");
    vfprintf(stdout, format, args);

    va_end(args);
}
