#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "files.h"
#include "panels.h"

// exit the program when an error is found
void die(char *msg) {
  perror(msg);
  exit(1);
}


void colorGreen() {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(1));
}

void stopColorGreen() {
  attroff(COLOR_PAIR(1));
}

void initEditor() {
  editor_info.opened_files_amount = 0;
  initscr();
  noecho();
  raw();
  keypad(stdscr, true);
  timeout(10);
  colorGreen();
  clear();
  getmaxyx(stdscr, win_info.height, win_info.width);
  refresh();
}

int main() {
  char c;

  initEditor();
  startCodePanel();
  startLinesPanel();

  if (!openFile("main.c")) {
    printw("error while reading file!");
    getch();
    return 1;
  }

  wmove(code_panel.win, 0, 0);
  while (1) {
    c = wgetch(code_panel.win);
    if (c == CTRL_KEY('q')) {
      printw("closing?\r\n");
      refresh();
      closeFiles();
      break;
    }

    if (c == 'c') {
      clearLine(0, &files[0]);
    }
  }

  endwin();
}
