#ifndef PL0_COMPILER_LOGGER_H
#define PL0_COMPILER_LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void handle_err(const char *format, ...);
void log_warning(const char *format, ...);

#endif // PL0_COMPILER_LOGGER_H
