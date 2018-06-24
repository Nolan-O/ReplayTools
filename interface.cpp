#include "interface.h"
#include "options.h"
#include "data.h"
#include <curses.h>

extern void parseFrame(FILE* file, r_frame* frame);

interface::interface() :
    curCol(0), curLine(0)
{
}

interface::~interface()
{
    endwin();
}

void interface::init()
{
    initscr();
    cbreak();
    noecho();
    clear();
    screen = new char[COLS * LINES];
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    g_state.frameIdx = 1;
}

void interface::drawAtFrame(int idx) {
    char frameString[335]; //longest possible frame string
    r_frame lastFrame;
    uint n = idx;
    fseek(g_state.replayFile, g_state.firstFrameOffset + n * 40, SEEK_SET);
    char fileOffsetStr[3];
    sprintf(fileOffsetStr, "%d", ftell(g_state.replayFile));
    mvaddstr(LINES - 1, 0, fileOffsetStr);
    for (uint i = 1; i < LINES; ++i) {
        r_frame curFrame;
        parseFrame(g_state.replayFile, &curFrame);

        //The frame compares its self to another frame
        curFrame.discreteStatStep(&lastFrame, n + i);

        if (g_options.pFramesOpt)
            frameToString(frameString, n + i, &lastFrame, &curFrame);

        mvaddnstr(i-1, 0, frameString, COLS);
        memcpy(&lastFrame, &curFrame, sizeof(r_frame));
    }
    refresh();
    return;
}

void interface::_scroll(int lines)
{
    return;
}

bool interface::input()
{
    lastIn = getch();
    if (lastIn == '\033') { //Ctrl or arrow keys
        getch(); // skip the [
        switch(getch()) { // the real value
            case 'A':
            g_state.frameIdx--;
            drawAtFrame(g_state.frameIdx);
                break;
            case 'B':
                g_state.frameIdx++;
                drawAtFrame(g_state.frameIdx);
                break;
     /*       case 'C':
                // code for arrow right
                break;
            case 'D':
                // code for arrow left
                break;*/
        }
    }

    return true;
}


state g_state;
interface g_interface;
