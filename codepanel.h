#pragma once

#include <stdio.h>
#include <ncurses.h>

#include "colors.h"
#include "config.h"
#include "cursor.h"
#include "panels.h"
#include "statuspanel.h"
#include "linespanel.h"

void cursorMoveUp(WINDOW *win) {
  if (cursor.y == 0) return;
  updateCursor(cursor.y - 1, cursor.x, win);
}

void cursorMoveDown(WINDOW *win) {
  if (cursor.y == code_panel.height - 1) return;
  updateCursor(cursor.y + 1, cursor.x, win);
}

void cursorMoveRight(WINDOW *win) {
  if (cursor.x == code_panel.width - 2) return;
  updateCursor(cursor.y, cursor.x + 1, win);
}

void cursorMoveLeft(WINDOW *win) {
  if (cursor.x == 0) return;
  updateCursor(cursor.y, cursor.x - 1, win);
}

void cursorScrollDown() {
  int linepos = editor_info.active_line;
  int c = 0; // line on code panel
  int lines_qty = editor_info.lines_amount;

  // scroll until the code finish at the middle of the screen
  if (editor_info.active_line >= lines_qty - code_panel.height / 2) return;

  wclear(code_panel.win);
  while (c < code_panel.height && (linepos + code_panel.height) >= c) {
    wmove(code_panel.win, c, 0);
    printWithColor(lines[linepos+1], code_panel.win);
    c++;
    linepos++;
  }
  editor_info.active_line++;
  updateLinesPanel(editor_info.active_line);
  updateStatus();
}

void cursorScrollUp();
void cursorScrollRight();
void cursorScrollLeft();

void cursorGoTo();
