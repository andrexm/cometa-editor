#pragma once

#include <math.h>
#include <ncurses.h>

#include "config.h"


// draw the lines panel
void startLinesPanel(int start_at) {
  WINDOW *lines = newwin(win_info.height, 7, 0, 0);
  lines_panel.win = lines;
  lines_panel.height = win_info.height;
  lines_panel.width = 7;
  wrefresh(lines);

  // draw numbers
  int c = 1;
  while (c <= lines_panel.height - 2) {
    wmove(lines_panel.win, c - 1, lines_panel.width - (int)log10(c) - 3);
    wprintw(lines_panel.win, "%d", start_at++);
    c++;
  }
  wrefresh(lines_panel.win);
}

// draw the panel for showing file content
void startCodePanel() {
  WINDOW *code = newwin(win_info.height - 2, win_info.width - 7, 0, 7);
  wrefresh(code);
  code_panel.win = code;
  code_panel.height = win_info.height - 2;
  code_panel.width= win_info.width - 6;
  keypad(code_panel.win, true);
  wrefresh(code);
}

// draw the panel for showing the status bar
void startStatusPanel() {
  WINDOW *status = newwin(1, win_info.width, win_info.height - 2, 0);
  status_panel.win = status;
  status_panel.height = 1;
  status_panel.width= win_info.width;
  keypad(status_panel.win, true);
  wrefresh(status);
}
