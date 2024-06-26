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

// save the lines of the file
char lines[MAX_LINES][MAX_LINE_SIZE];

enum buffer_type {
  EMPTY, // no filename given to the program
  EXISTING_FILE, // filename given and file exists
  EMPTY_FILE // filename given but create the file
};

// information about the text editor
static struct editor_info {
  int lines_amount;
  int active_file;
  int active_line;
  enum buffer_type buffer_type;
  FILE *opened_file;
  char *active_filename;
  char lines[MAX_LINES][MAX_LINE_SIZE];
} editor_info;

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

