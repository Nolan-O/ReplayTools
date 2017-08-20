#pragma once

#include <stdio.h>

#define P_COLOR_RED     "\x1b[31m"
#define P_COLOR_GREEN   "\x1b[32m"
#define P_COLOR_YELLOW  "\x1b[33m"
#define P_COLOR_BLUE    "\x1b[34m"
#define P_COLOR_PURPLE  "\x1b[35m"
#define P_COLOR_CYAN    "\x1b[36m"
#define P_COLOR_RESET   "\x1b[0m"

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