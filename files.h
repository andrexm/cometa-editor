#pragma once

#include <stdio.h>
#include <ncurses.h>

#include "colors.h"
#include "config.h"

// read a file and save it on the opened struct
bool openFile(char *filename) {
  int c = 0; // count the number of lines
  int opened_files = editor_info.opened_files_amount; // the number of opened files
  char line[MAX_LINE_SIZE]; // each line of the file
  FILE *file;

  // TODO: verify if the file is already opened
  // TODO: verify if there is capacity to save the file on the files struct

  file = fopen(filename, "r+"); // open the file if it exists
  if (!file) file = fopen(filename, "w+"); // create the file if it not exists

  struct opened_file opened_file; // create file data struct
  opened_file.file = file; // add 'file' to the struct
  opened_file.name = filename; // add 'filename' to the struct

  // how many lines the file has?
  while (fgets(line, sizeof(char) * MAX_LINE_SIZE, file)) {
    // print lines on visible area <2 is the status bar and command bar at the bottom>
    if ((c + 2) <= win_info.height) {
      printWithColor(line, code_panel.win);  
      //wprintw(code_panel.win, "%s", line);
    }
    opened_file.lines[c] = line; // add each line to the buffer
    c++;
  }
  wrefresh(code_panel.win);

  opened_file.count_lines = c;
  opened_files++;
  // add file struct to files array
  files[opened_files] = opened_file;
  editor_info.opened_files_amount++;

  refresh();
  return true;
}

// show file data on screen
void showFile(struct opened_file *file) {
  int i = 0;
  while (i < file->count_lines) {
    wprintw(code_panel.win, "%s\r\n", file->lines[i]);
    i++;
  }
}

// close opened files
void closeFiles() {
  int c = 0;
  for (c = 0; c < editor_info.opened_files_amount; c++) {
    // TODO: try to understand why the code below fails
    //fclose(files[c].file);
    files[c] = files[c + 1];
    refresh();
  }
}

// clear the specified line
void clearLine(int line, struct opened_file *ofp) {
  move(line, 0);
  clrtoeol();
  ofp->lines[line] = "";
}
