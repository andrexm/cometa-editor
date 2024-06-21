#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "codepanel.h"
#include "config.h"
#include "colors.h"
#include "cursor.h"
#include "files.h"
#include "panels.h"
#include "movement.h"
#include "statuspanel.h"

// exit the program when an error is found
void die(char *msg) {
  perror(msg);
  exit(1);
}

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

int main() {
  int c;

  initEditor();
  startStatusPanel();
  startCodePanel();
  startLinesPanel(0);

  // start after panels to apply
  basicColors();

  openFile("files.h");
  updateCursor(0, 0, code_panel.win);
  while (1) {
    c = wgetch(code_panel.win);

    if (movement(c)) continue;
    switch (c) {
      case CTRL_KEY('q'): // close program
        closeEditor();
        return 0;
      case 'b':
        cursorScrollDown();
        break;
      case 'B':
        cursorScrollUp();
        break;
    }
  }
}
