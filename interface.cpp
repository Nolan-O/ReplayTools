#include "interface.h"
#include <curses.h>

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
                // code for arrow up
                break;
            case 'B':
                // code for arrow down
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

interface g_interface;
