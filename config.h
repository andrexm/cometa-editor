#pragma once
#include <stdio.h>
#include <ncurses.h>

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
static struct editor_info {
  int opened_files_amount;
  int active_file;
  struct opened_file *opened_file;
  char *active_filename;
} editor_info;

// information about the opened file
struct opened_file {
  FILE *file;
  char *name;
  int count_lines;
  char *lines[MAX_LINES];
};

// array of opened files
// the '+1' is used as an empty item to be copied when a file is closed
static struct opened_file files[FOPEN_MAX + 1];

// points to the active index on opened_files
static int active_file = -1;

// panels
static struct panel {
  WINDOW *win;
  int width;
  int height;
} code_panel, lines_panel, status_panel, command_panel;

// info about the terminal
static struct window_info{
  int height;
  int width;
} win_info;

// cursor tracking
static struct cursor {
  int y;
  int x;
  int previousy;
  int previousx;
  WINDOW *win;
  WINDOW *previouswin;
} cursor;

