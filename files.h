#pragma once

#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "colors.h"
#include "cursor.h"
#include "errors.h"
#include "statuspanel.h"
#include "linespanel.h"

// return the length of a given line in the file
int getLineLen(int line) {
  int len = strlen(lines[line]) - 1;
  if (len < 0) len = 0;
  return len;
}

// return the corresponding number of the above line, ex. '1' if the cursor is at second line
int previousLineNumber() {
  return cursor.y + editor_info.active_line - 1;
}

int nextLineNumber() {
  return cursor.y + editor_info.active_line;
}

// is the given value at the end of the current line of the file?
bool endOfLine(int linelen) {
  return (cursor.x == code_panel.width - 2) || linelen < cursor.x + 1;
}

// is the given value at the end of the current file?
bool endOfFile() {
  return (editor_info.active_line + cursor.y - 1) >= editor_info.lines_amount;
}

// when no file name is given
void startEmptyBuffer() {
    editor_info.lines_amount = 1;
    editor_info.active_line = 1;
    editor_info.active_filename = (char*)"[blank]";
    editor_info.buffer_type = EMPTY;

    strcpy(lines[0], "");
    
    updateLinesPanel(1);
    updateStatus();
    wmove(code_panel.win, 0, 0);
}

// show lines with color
void showLines() {
  int c = 0;
  while (c < code_panel.height) {
    wmove(code_panel.win, c, 0);
    if (c < code_panel.height) {
      printWithColor(lines[c], code_panel.win);
      c++;
    } else { break; }
  }
}

bool openFile(char *filename) {
  int c = 0; // count lines
  FILE *fp;

  // open file if it exists
  if (access(filename, F_OK) != -1) fp = fopen(filename, "r+");
  // create file if it don't exists
  if (access(filename, F_OK) == -1) fp = fopen(filename, "w+");
  // show an error message if both operations don't work
  if (!fp) {
    die("Error while opening/creating file");
    return false;
  }

  // setting basic file data
  editor_info.active_filename = filename;
  editor_info.lines_amount= 0;
  editor_info.active_line = 1;
  editor_info.opened_file = fp;

  while (fgets(lines[c], sizeof(char) * MAX_LINE_SIZE, fp)) {
    //memcpy(editor_info.lines[c], line, sizeof(line));
    editor_info.lines_amount++;
    c++;
  }
  showLines();
  wmove(code_panel.win, 0, 0);
  updateStatus();
  updateLinesPanel(editor_info.active_line);
  return true;
}


// clear the specified line
void clearLine(int line) {
  move(line, 0);
  clrtoeol();
  strcpy(lines[line], "");
}
