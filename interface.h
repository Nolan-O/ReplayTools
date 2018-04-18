#pragma once

class interface
{
public:
      interface();
      ~interface();
      void init();
      void _scroll(int lines);
      bool input();
      char lastIn;

      int curLine;
      int curCol;
      char* screen;
};

extern interface g_interface;
