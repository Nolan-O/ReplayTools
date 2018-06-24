#pragma once

#include <stdio.h>
#include "data.h"

class interface
{
public:
      interface();
      ~interface();
      void init();
      void _scroll(int lines);
      void drawAtFrame(int frame);
      bool input();
      char lastIn;

      int curLine;
      int curCol;
      char* screen;
};

struct state
{
    int frameCt;
    bool hasRunStats;
    FILE* replayFile;
    uint headerlen;
    r_header header;
    r_runStats runStats;

    //File-format stuff
    uint firstFrameOffset;

    //Stuff for interractive mode
    uint frameIdx;
};

extern state g_state;
extern interface g_interface;
