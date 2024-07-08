#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "colors.h"
#include "files.h"
#include "panels.h"
#include "movement.h"


void initEditor() {
  initscr();
  noecho();
  raw();
  keypad(stdscr, true);
  timeout(10);
  getmaxyx(stdscr, win_info.height, win_info.width);
  refresh();
}

void closeEditor() {
  endwin();
}

int main(int argv, char *argc[]) {
  int c;

  initEditor();
  startStatusPanel();
  startCodePanel();
  startLinesPanel();

  // start after panels to apply
  basicColors();

  // open file or start a blank buffer
  if (argv >= 2) openFile(argc[1]);
  else startEmptyBuffer();
  
  while (1) {
    c = wgetch(code_panel.win);

    if (movement(c)) continue;
    switch (c) {
      case CTRL_KEY('q'): // close program
        closeEditor();
        return 0;
    }
  }
}
