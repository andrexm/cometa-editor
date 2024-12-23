#pragma once

#include <string.h>
#include <ctype.h>
#include <ncurses.h>

#include "config.h"

#define COLOR_BLACK2 8
#define COLOR_WHITE2 9
#define COLOR_GRAY 10
#define COLOR_ORANGE 11
#define COLOR_PURPLE 12
#define COLOR_COMMENT 13
#define COLOR_SKY 14
#define COLOR_EMERALD 15
#define COLOR_GRAY2 16
#define COLOR_BLACK3 17

int selectedColor = 1;
bool startStr = false;
bool isMultilineComment = false; // TODO: implement detection of multiline comments

struct symbol {
  char text[5000];
  int color_code;
} symbol;

// basic colors for all panels
void basicColors() {
  if (!has_colors()) return;
  start_color();
  init_color(COLOR_BLACK2, 100, 100, 100);
  init_color(COLOR_BLACK3, 150, 150, 150);
  init_color(COLOR_WHITE2, 800, 800, 800);
  init_color(COLOR_GRAY, 392, 454, 545);
  init_color(COLOR_ORANGE, 984, 572, 235);
  init_color(COLOR_PURPLE, 192, 180, 505);
  init_color(COLOR_COMMENT, 278, 333, 411);
  init_color(COLOR_SKY, 549, 647, 913);
  init_color(COLOR_EMERALD, 62, 725, 505);
  init_color(COLOR_GRAY2, 580, 639, 721);

  init_pair(1, COLOR_WHITE2, COLOR_BLACK2);
  init_pair(2, COLOR_GRAY, COLOR_BLACK2);
  init_pair(3, COLOR_SKY, COLOR_BLACK2);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK2);
  init_pair(5, COLOR_ORANGE, COLOR_BLACK2);
  init_pair(6, COLOR_PURPLE, COLOR_BLACK2);
  init_pair(7, COLOR_COMMENT, COLOR_BLACK2);
  init_pair(8, COLOR_EMERALD, COLOR_BLACK2);
  init_pair(9, COLOR_GRAY2, COLOR_BLACK2);
  init_pair(10, COLOR_WHITE, COLOR_BLACK3);

  wbkgd(code_panel.win, COLOR_PAIR(1));
  wbkgd(lines_panel.win, COLOR_PAIR(2));
  wbkgd(status_panel.win, COLOR_PAIR(10));
  bkgd(COLOR_PAIR(2));

  refresh();
  wrefresh(code_panel.win);
  wrefresh(lines_panel.win);
  getch();
}

bool isSpecial(char c) {
  char specials[] = {'(', ')', '{', '}', ',', '.', '[', ']', ';', '?', '|', '<', '>', '!', '?', '&', '=', '#'};
  int i = 0;
  while (specials[i]) {
    if (specials[i] == c) return true;
    i++;
  }
  return false;
}

// the next symbol to be printed, eg: keyword, comment, function call, ...
//return the number of characters read
int findNextSymbol(size_t charPosition, char *line) {
  //find comments
  if (line[charPosition] == '/' && line[charPosition + 1] == '/') {
    int i = 0;
    while (line[charPosition + i] != '\0') {
      symbol.text[i] = line[charPosition + i];
      i++;
    }
    symbol.text[charPosition + i] = '\0';
    symbol.color_code = 7;
    return i;
  }
  
  // find special character
  if (isSpecial(line[charPosition])) {
    symbol.text[0] = line[charPosition];
    symbol.text[1] = '\0';
    symbol.color_code = 9;
    return 1;
  }

  // find strings
  if (line[charPosition] == '"') {
    int i = 1;
    char find = line[charPosition];

    symbol.text[0] = line[charPosition];
    while (line[charPosition + i] && line[charPosition + i] != find) {
      if (line[charPosition + i + 1] == '\0') {
        symbol.text[1] = '\0';
        symbol.color_code = 1;
        return 1;
      }
      symbol.text[i] = line[charPosition + i];
      i++;
    }
    symbol.text[i] = line[charPosition + i];
    symbol.text[i + 1] = '\0';
    symbol.color_code = 5;
    return i + 1;
  }
  // end find strings

  // find single quotes strings
  if (line[charPosition] == '\'') {
    int i = 1;
    char find = line[charPosition];

    symbol.text[0] = line[charPosition];
    while (line[charPosition + i] && line[charPosition + i] != find && line[charPosition] != '\\') {
      if (line[charPosition + i + 1] == '\0') {
        symbol.text[1] = '\0';
        symbol.color_code = 1;
        return 1;
      }
      symbol.text[i] = line[charPosition + i];
      i++;
    }
    symbol.text[i] = line[charPosition + i];
    symbol.text[i + 1] = '\0';
    symbol.color_code = 5;
    return i + 1;
  }
  // end find single quotes strings

  // find names
  if (isalpha(line[charPosition])) {
    int i = 0;
    //char buff[50];
    
    // save the word in symbol.text
    while (isalpha(line[charPosition + i]) || isdigit(line[charPosition + i]) || line[charPosition + i] == '_') {
      symbol.text[i] = line[charPosition + i]; // FIX: the error should be here
      i++;
    }
    symbol.text[i] = '\0';
    symbol.color_code = 3; // default color

    // the word is a function
    if (line[charPosition + i] == '(' || (line[charPosition + i + 1] == '(' && line[charPosition + i] == ' ')) symbol.color_code = 8;

    // the word is a property or method of a struct
    if (line[charPosition - 1] == '.') symbol.color_code = 3;

    // the word is inside a <>
    if (line[charPosition - 1] == '<') symbol.color_code = 3;

    // print it white when struct, array or there is a word before it
    if ((isalpha(line[charPosition - 2]) && line[charPosition - 1] == ' ' && line[charPosition + i] != '(') || line[charPosition + i] == '[') symbol.color_code = 1;
    if (line[charPosition + i] == '.' && line[charPosition - 1] != '<') symbol.color_code = 1;

    return i;
  }
  // end find names

  // is number
  if (isdigit(line[charPosition])) {
    symbol.text[0] = line[charPosition];
    symbol.text[1] = '\0';
    symbol.color_code = 4;
    return 1;
  }

  // nothing special, return basic text
  symbol.text[0] = line[charPosition];
  symbol.text[1] = '\0';
  symbol.color_code = 1;
  return 1;
}

void printWithColor(char line[5000], WINDOW *win) {
  size_t charPosition = 0;

  for (; charPosition <= strlen(line);) {
    // get the next symbol to the symbol global variable
    charPosition = charPosition + findNextSymbol(charPosition, line);

    // print the text with its color
    wattron(win, COLOR_PAIR(symbol.color_code));
    wprintw(win, "%s", symbol.text);
    wattroff(win, COLOR_PAIR(symbol.color_code));
  }
}
