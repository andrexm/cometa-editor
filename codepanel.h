#pragma once

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "colors.h"
#include "config.h"
#include "cursor.h"
#include "panels.h"
#include "statuspanel.h"
#include "linespanel.h"
#include "files.h"


void cursorScrollDown() {
  int linepos = editor_info.active_line;
  int c = 0; // line on code panel
  int lines_qty = editor_info.lines_amount;

  // scroll until the code finish at the middle of the screen
  if (editor_info.active_line >= lines_qty - code_panel.height / 2) return;

  curs_set(0);
  wclear(code_panel.win);
  while (c < code_panel.height && (linepos + code_panel.height) > c) {
    wmove(code_panel.win, c, 0);
    printWithColor(lines[linepos], code_panel.win);
    c++;
    linepos++;
  }
  curs_set(1);
  editor_info.active_line += 1;
  updateLinesPanel(editor_info.active_line);
  updateStatus();
}

void cursorScrollUp() {
  int linepos = editor_info.active_line;
  int c = 0; // line on code panel

  // scroll until the code finish at the middle of the screen
  if ((editor_info.active_line - 1) <= 0) return;

  curs_set(0);
  wclear(code_panel.win);
  while (c < code_panel.height) {
    wmove(code_panel.win, c, 0);
    printWithColor(lines[linepos-2], code_panel.win);
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
  // nothing happens if the cursor is already on top
  if (cursor.y == 0) {
    cursorScrollUp();
    return;
  }

  // get new cursor x position
  int new_x_pos = cursor.x;
  int linelen = getLineLen(previousLineNumber() - 1); // length of previous line
  if (linelen < new_x_pos) new_x_pos = linelen;

  // update cursor to the above line
  updateCursor(cursor.y - 1, new_x_pos, win);
}

// use linelen, if the x position on the new line is greater then the line length, move to its len
void cursorMoveDown(WINDOW *win) {
  // nothing happens at the end of the file
  if ((cursor.y > editor_info.lines_amount - editor_info.active_line)) return;

  // get new cursor x position
  int new_x_pos = cursor.x;
  int linelen = getLineLen(nextLineNumber()); // length of next line
  if (linelen < new_x_pos) new_x_pos = linelen;

  // move down when there are more lines to show
  if (cursor.y == code_panel.height - 1) {
    cursorScrollDown();
    return;
  }
  updateCursor(cursor.y + 1, new_x_pos, win);
}

// go to the right side of the current line
void cursorMoveRight(WINDOW *win) {
  int linelen = getLineLen(nextLineNumber() - 1);
  if ((cursor.x == code_panel.width - 2) || linelen < cursor.x + 1) return;
  updateCursor(cursor.y, cursor.x + 1, win);
}

// go to the left side of the current line
void cursorMoveLeft(WINDOW *win) {
  if (cursor.x == 0) return;
  updateCursor(cursor.y, cursor.x - 1, win);
}

// position the cursor at the bottom or the last line
void cursorOnBottomSide(WINDOW *win) {
  if (cursor.y > editor_info.lines_amount - editor_info.active_line) return;

  // get the maximum position the cursor can go on the bottom
  int pos = editor_info.lines_amount - editor_info.active_line;
  if (pos > code_panel.height) pos = code_panel.height - 1;

  // get the maximum position at right the cursor can go
  int new_x_pos = getLineLen(editor_info.active_line + code_panel.height - 2);
  if (cursor.x < new_x_pos) new_x_pos = cursor.x;

  // then go down
  updateCursor(pos, new_x_pos, win);
}

// position the cursor at the top side
void cursorOnTopSide() {
  // get the maximum position at right the cursor can go
  int new_x_pos = getLineLen(editor_info.active_line - 1);
  if (cursor.x < new_x_pos) new_x_pos = cursor.x;

  updateCursor(0, new_x_pos, code_panel.win);
}

// position the cursor at the left side
void cursorOnLeftSide() {
  updateCursor(cursor.y, 0, code_panel.win);
}

void cursorOnRightSide(WINDOW *win) {
  int linelen = getLineLen(nextLineNumber() - 1);
  updateCursor(cursor.y, linelen, win);
}

