#pragma once

#include <string.h>
#include <ctype.h>
#include <ncurses.h>

#include "config.h"

#define COLOR_BLACK2 8
#define COLOR_WHITE2 9
#define COLOR_GRAY 10

const char *KEYWORDS[] = {"int", "void", "include", "char"};
const char *test = "void";


// basic colors for all panels
void basicColors() {
  if (!has_colors()) return;
  start_color();
  init_color(COLOR_BLACK2, 100, 100, 100);
  init_color(COLOR_WHITE2, 800, 800, 800);
  init_color(COLOR_GRAY, 392, 454, 545);
  init_pair(1, COLOR_WHITE2, COLOR_BLACK2);
  init_pair(2, COLOR_GRAY, COLOR_BLACK2);
  init_pair(3, COLOR_CYAN, COLOR_BLACK2);
  wbkgd(code_panel.win, COLOR_PAIR(1));
  wbkgd(lines_panel.win, COLOR_PAIR(2));
  bkgd(COLOR_PAIR(2));
  refresh();
  wrefresh(code_panel.win);
  wrefresh(lines_panel.win);
  getch();
}

void printWithColor(char line[5000], WINDOW *win) {
  int charCount = 0, keyCount = 0;
  char buff[50]; // temp keyword
  int buffCount = 0;
  for (; charCount <= strlen(line); charCount++) {
    if (isalpha(line[charCount])) {
      int i = 0;
      while (isalpha(line[charCount + i])) {
        buff[i] = line[charCount+i];
        i++;
      }

      buff[i] = '\0';
      charCount = charCount + i;

      i = 0;
      bool found = false;
      while (KEYWORDS[i]) {
        if (strcmp(KEYWORDS[i], buff) == 0) {
          wattron(win, COLOR_PAIR(3));
          wprintw(win, "%s", buff);
          wattroff(win, COLOR_PAIR(3));
          found = true;
          break;
        }
        i++;
      }
      if (!found) wprintw(win, "%s", buff);
    }
    wprintw(win, "%c", line[charCount]);
  }
}
