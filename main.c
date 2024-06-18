#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "colors.h"
#include "files.h"
#include "panels.h"

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
  char c;

  initEditor();
  startCodePanel();
  startLinesPanel();

  // start after panels to apply
  basicColors();

  if (!openFile("main.c")) {
    printw("error while reading file!");
    getch();
    return 1;
  }

  wmove(code_panel.win, 0, 0);
  while (1) {
    c = wgetch(code_panel.win);
    if (c == CTRL_KEY('q')) {
      closeEditor();
      break;
    }

    if (c == 'c') {
      clearLine(0, &files[0]);
    }
  }
}
