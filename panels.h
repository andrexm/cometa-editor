#pragma once

#include <math.h>
#include <ncurses.h>

#include "config.h"
#include "linespanel.h"


// draw the lines panel
void startLinesPanel() {
  WINDOW *lines = newwin(win_info.height, 7, 0, 0);
  int start_at = 1;
  lines_panel.win = lines;
  lines_panel.height = win_info.height - 2;
  lines_panel.width = 7;
  wrefresh(lines);

  // draw numbers
  updateLinesPanel(1);
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
