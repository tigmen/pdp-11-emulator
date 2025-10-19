#pragma once

#include <stdio.h>
#include <stdarg.h>

enum LOG_LEVEL  {
    ERROR = 0,
    WARNING,
    INFO,
    DEBUG
};

extern enum LOG_LEVEL current_log_level;

void log(enum LOG_LEVEL, char *, ...);
enum LOG_LEVEL set_log_level(enum LOG_LEVEL);