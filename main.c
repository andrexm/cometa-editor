#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "files.h"


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
  refresh();
  timeout(10);
  colorGreen();
  clear();
}

int main() {
  char c;

  initEditor();
  if (!openFile("t.txt")) {
    printw("error while reading file!");
    getch();
    return 1;
  }

  while (1) {
    c = getch();
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
