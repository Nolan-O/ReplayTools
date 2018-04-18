#include "options.h"
#include <stdio.h>

options g_options;

void showUsage()
{
    printf(
        "Usage: rpts [options] file\n"
        "\n"
        "-h                 Prints header data\n"
        "-r                 Prints the data in the run stats block\n"
        "-f                 Prints data in every frame\n"
        "-d, --diff         Prints diffs between frames\n"
        "-i                 Ignore vectors in frame output\n"
        "-n                 Display keys non-numeically"
        "\n"
    );
    exit(EXIT_SUCCESS);
}

CSimpleOpt::SOption g_sOptions[] =
{
    {1, "-h", SO_NONE},
    {2, "-r", SO_NONE},
    {3, "-f", SO_NONE},
    {4, "-n", SO_NONE},
    {4, "--none", SO_NONE},
    {5, "--nocolor", SO_NONE},
    {6, "-d", SO_NONE},
    {6, "--diff", SO_NONE},
    {7, "-i", SO_NONE},
    {8, "--dump", SO_NONE},
    {OPT_HELP, "--help", SO_NONE},
    SO_END_OF_OPTIONS
};
