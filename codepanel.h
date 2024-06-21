#pragma once

#include "colors.h"
#include "config.h"
#include "cursor.h"
#include "panels.h"
#include "statuspanel.h"
#include <stdio.h>
#include <ncurses.h>

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
  int lines = editor_info.lines_amount;

  //if (files[editor_info.active_file].count_lines <= linepos) return;
  wclear(code_panel.win);
  while (c <= code_panel.height && editor_info.active_line + code_panel.height >= c) {
    // read each line saved in the array
    char *line = editor_info.lines[c + editor_info.active_line]; // FIX: lines with }
    wmove(code_panel.win, c, 0);
    //wprintw(code_panel.win, "%s", line);
    printWithColor(line, code_panel.win);
    c++;
    linepos++;
  }
  editor_info.active_line++;
  updateStatus();
  startLinesPanel(editor_info.active_line);
}
void cursorScrollUp();
void cursorScrollRight();
void cursorScrollLeft();

void cursorGoTo();
