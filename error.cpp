#include "error.h"
#include <stdlib.h>

void fatal(const char* msg, ...)
{
    va_list v;
    printf(P_COLOR_RED ">> Fatal : " P_COLOR_RESET);
    printf(msg, v);
    printf("\n");
    exit(EXIT_FAILURE);
}

void soft(const char* msg, ...)
{
    va_list v;
    printf(P_COLOR_RED ">> : " P_COLOR_RESET);
    printf(msg, v);
    printf("\n");
}