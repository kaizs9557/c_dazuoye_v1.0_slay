#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
//这个东西要实现占位符，真是一坨屎！
void wlog(FILE* log, const char* format, ...) {
    time_t present;
    char time_str[20]={0};
    time(&present);
    struct tm *time_info = localtime(&present);
    strftime(time_str, sizeof(time_str), "%Y/%m/%d %H:%M:%S", time_info);
    fprintf(log, time_str);
    fprintf(log, " ");
    va_list args;
    va_start(args, format);
    while (*format) {
        if (*format=='%') {
            format++;
            if (*format=='s') {
                char* str=va_arg(args,char*);
                fprintf(log,"%s", str);
            }
            else if (*format=='%') {
                fputc('%',log);
            }
            else {
                fputc('%',log);
                fputc(*format, log);
            }
        }
        else {
            fputc(*format, log);
        }

        format++;
    }
    fputc('\n', log);
    va_end(args);
}