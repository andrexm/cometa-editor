#pragma once

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "config.h"
#include "colors.h"
#include "cursor.h"
#include "statuspanel.h"

bool openFile(char *filename) {
  int c = 0; // count lines
  FILE *fp;
  char line[MAX_LINE_SIZE];

  if (!(fp = fopen(filename, "r+"))) fp = fopen(filename, "w+");
  
  // setting basic file data
  editor_info.active_filename = filename;
  editor_info.lines_amount= 0;
  editor_info.active_line = 1;
  editor_info.opened_file = fp;

  while (fgets(line, sizeof(char) * MAX_LINE_SIZE, fp)) {
    strcpy(editor_info.lines[c], line);
    printWithColor(line, code_panel.win);
    editor_info.lines_amount++;
  }

  updateStatus();
  return true;
}

// clear the specified line
void clearLine(int line) {
  move(line, 0);
  clrtoeol();
  strcpy(editor_info.lines[line], "");
}
