#pragma once

#include <math.h>
#include <ncurses.h>

#include "config.h"

void updateLinesPanel(int start_at) {
  // draw numbers
  wclear(status_panel.win);
  int c = 1;

  while (c <= lines_panel.height) {
    if (start_at <= editor_info.lines_amount) {
      // print numbers
      wmove(lines_panel.win, c - 1, lines_panel.width - (int)log10(start_at) - 3);
      wprintw(lines_panel.win, "%d", start_at++);
    } else {
      // clear position and print a '~'
      wclrtobot(lines_panel.win);
      wmove(lines_panel.win, c - 1, lines_panel.width - 3);
      wprintw(lines_panel.win, "%c", '~');
    }
    c++;
  }
  wrefresh(lines_panel.win);
}
