#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "codepanel.h"
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
  int c;

  initEditor();
  startCodePanel();
  startLinesPanel();

  // start after panels to apply
  basicColors();

  if (!openFile("files.h")) {
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

    if (c == 'j' || c == KEY_DOWN) cursorMoveDown(code_panel.win);
    if (c == 'k' || c == KEY_UP) cursorMoveUp(code_panel.win);
    if (c == 'h' || c == KEY_LEFT) cursorMoveLeft(code_panel.win);
    if (c == 'l' || c == KEY_RIGHT) cursorMoveRight(code_panel.win);
  }
}
