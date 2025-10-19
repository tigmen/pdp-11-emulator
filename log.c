#include "log.h"

void log(enum LOG_LEVEL log_level, char * fmt, ...) {
    if(log_level <= current_log_level) {
        va_list p_arg;
        va_start(p_arg, fmt);

        FILE * log_file = fopen("log", "a");
        if(log_file == NULL) {
            exit(1);
        }

        switch (log_level)
        {
        case ERROR:
            fprintf(log_file, "==ERROR==\n");
            break;
        
        case WARNING:
            fprintf(log_file, "--WARNING--\n");
            break;
        
        case INFO:
            fprintf(log_file, "<INFO>\n");
            break;
        
        case DEBUG:
            fprintf(log_file, "::DEBUG::\n");
            break;
        
        default:
            break;
        }

        vfprintf(log_file, fmt, p_arg);
        fprintf(log_file, "\n");

        fclose(log_file);

        va_end(p_arg);
    }
}

enum LOG_LEVEL set_log_level(enum LOG_LEVEL level) {
    enum LOG_LEVEL last_level = current_log_level;
    current_log_level = level;

    return last_level;
}