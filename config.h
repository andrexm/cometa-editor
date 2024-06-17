#pragma once
#include <stdio.h>

/*
* definitions about the program
*/

// max of 10,000 characters per line
#define MAX_LINE_SIZE 10000

// max of 5,000 lines
#define MAX_LINES 5000

// return CTRL + X
#define  CTRL_KEY(k) ((k) & (0x1f))

// information about the text editor
struct editor_info {
  int opened_files_amount;
};

// information about the opened file
struct opened_file {
  FILE *file;
  char *name;
  int count_lines;
  char *lines[MAX_LINES];
};

struct editor_info editor_info;

// array of opened files
// the '+1' is used as an empty item to be copied when a file is closed
struct opened_file files[FOPEN_MAX + 1];
