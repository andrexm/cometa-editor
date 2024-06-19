#pragma once

#include "config.h"
#include "cursor.h"
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

void cursorScrollDown();
void cursorScrollUp();
void cursorScrollRight();
void cursorScrollLeft();

void cursorGoTo();
