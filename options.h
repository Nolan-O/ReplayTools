#pragma once

#include "simpleopt.h"

enum { OPT_HELP, OPT_FIN = 100};

extern CSimpleOpt::SOption g_sOptions[];

struct options
{
    bool pHeaderOpt = false;
    bool pStatsOpt = false;
    bool pFramesOpt = false;
    bool pDiffOpt = false;
    bool pIgnoreVecOpt = false;
    bool pNumericKeys = false;
    bool pUninteractive = false;
};

extern void showUsage();
extern options g_options;
