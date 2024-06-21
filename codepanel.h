#pragma once

#include <stdio.h>
#include <ncurses.h>

#include "colors.h"
#include "config.h"
#include "cursor.h"
#include "panels.h"
#include "statuspanel.h"
#include "linespanel.h"

void cursorScrollDown() {
  int linepos = editor_info.active_line;
  int c = 0; // line on code panel
  int lines_qty = editor_info.lines_amount;

  // scroll until the code finish at the middle of the screen
  if (editor_info.active_line >= lines_qty - code_panel.height / 2) return;

  curs_set(0);
  wclear(code_panel.win);
  while (c < code_panel.height && (linepos + code_panel.height) >= c) {
    wmove(code_panel.win, c, 0);
    printWithColor(lines[linepos+1], code_panel.win);
    c++;
    linepos++;
  }
  curs_set(1);
  editor_info.active_line++;
  updateLinesPanel(editor_info.active_line);
  updateStatus();
}

void cursorScrollUp() {
  int linepos = editor_info.active_line;
  int c = 0; // line on code panel
  int lines_qty = editor_info.lines_amount;

  // scroll until the code finish at the middle of the screen
  if ((editor_info.active_line - 1) <= 0) return;

  curs_set(0);
  wclear(code_panel.win);
  while (c < code_panel.height) {
    wmove(code_panel.win, c, 0);
    printWithColor(lines[linepos], code_panel.win);
    c++;
    linepos++;
  }
  curs_set(1);
  editor_info.active_line--;
  updateLinesPanel(editor_info.active_line);
  updateStatus();
}

void cursorScrollRight();
void cursorScrollLeft();

void cursorGoTo();

void cursorMoveUp(WINDOW *win) {
  if (cursor.y == 0) {
    cursorScrollUp();
    return;
  }
  updateCursor(cursor.y - 1, cursor.x, win);
}

void cursorMoveDown(WINDOW *win) {
  if (cursor.y == code_panel.height - 1) {
    cursorScrollDown();
    return;
  }
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

