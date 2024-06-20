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
  editor_info.opened_files_amount = 0;
  initscr();
  noecho();
  raw();
  keypad(stdscr, true);
  timeout(10);
  getmaxyx(stdscr, win_info.height, win_info.width);
  refresh();
}

void closeEditor() {
  closeFiles();
  endwin();
}

int main() {
  int c;

  initEditor();
  startStatusPanel();
  startCodePanel();
  startLinesPanel();

  // start after panels to apply
  basicColors();

  editor_info.active_file = -1; // no opened files
  if (!openFile("files.h")) {
    printw("error while reading file!");
    getch();
    return 1;
  }

  updateCursor(0, 0, code_panel.win);
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
