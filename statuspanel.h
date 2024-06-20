#pragma once

#include <math.h>
#include <ncurses.h>

#include "config.h"
#include "cursor.h"

void clearStatus() {
  int s = win_info.width;
  wmove(status_panel.win, 0, 0);
  while (s > 0) {
    wprintw(status_panel.win, " ");
    s--;
  }
}

// print status, filename (opened file) and line/column the cursor is
void setStatus(char *filename) {
  // the default status is "NORMAL"
  char editor_status[8] = "NORMAL";
  // calculate how many spaces the numbers for position take
  int length = (int)log10(cursor.y + 1) + (int)log10(cursor.x + 1) + 2;
  
  clearStatus();
  // go to status bar and print status and file name
  wmove(status_panel.win, 0, 0);
  wprintw(status_panel.win, " %s     %s",
          editor_status, filename);

  // print the numbers for line and column
  wmove(status_panel.win, 0, win_info.width - (length + 3));
  wprintw(status_panel.win, "%d:%d", cursor.x + 1, cursor.y + 1);

  // go back to code panel and refresh status panel
  wmove(code_panel.win, cursor.y, cursor.x);
  wrefresh(status_panel.win);
}

void updateStatus() {
  char *name, *blank = "blank";
  name = (editor_info.active_file == -1) ? blank : editor_info.active_filename;
  curs_set(0);
  setStatus(name);
  curs_set(1);
}
