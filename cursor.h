#pragma once

#include "config.h"
#include <ncurses.h>

void updateCursor(int y, int x, WINDOW *win) {
  getyx(cursor.win, cursor.previousy, cursor.previousx);
  wmove(win, y, x);
  cursor.y = y;
  cursor.x = x;
  cursor.previouswin = cursor.win;
  cursor.win = win;
}
