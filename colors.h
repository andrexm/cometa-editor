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

const char *KEYWORDS[] = {"int", "void", "char", "include", "while", "for", "if", "else", "return"};
const char *test = "void";

int selectedColor = 1;
bool startStr = false;
bool isMultilineComment = false; // TODO: implement detection of multiline comments

// basic colors for all panels
void basicColors() {
  if (!has_colors()) return;
  start_color();
  init_color(COLOR_BLACK2, 100, 100, 100);
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

  wbkgd(code_panel.win, COLOR_PAIR(1));
  wbkgd(lines_panel.win, COLOR_PAIR(2));
  bkgd(COLOR_PAIR(2));

  refresh();
  wrefresh(code_panel.win);
  wrefresh(lines_panel.win);
  getch();
}

bool isSpecial(char c) {
  char specials[] = {'(', ')', '{', '}', ',', '.', '[', ']', ';', '?', '|'};
  int i = 0;
  while (specials[i]) {
    if (specials[i] == c) return true;
    i++;
  }
  return false;
}

void printWithColor(char line[5000], WINDOW *win) {
  int charCount = 0, keyCount = 0;
  char buff[50]; // temp keyword
  int buffCount = 0;
  bool isComment = false;
  for (; charCount <= strlen(line); charCount++) {
    // start a comment
    if (line[charCount] == '/' && line[charCount + 1] == '/') isComment = true;
    
    // detect words
    if (isalpha(line[charCount])) {
      int i = 0;
      while (isalpha(line[charCount + i])) {
        buff[i] = line[charCount+i];
        i++;
      }

      buff[i] = '\0';
      charCount = charCount + i;

      // start color for functions
      if (line[charCount] == '(') {
        selectedColor = 8;
      }

      i = 0;
      bool found = false;
      while (KEYWORDS[i]) {
        if (strcmp(KEYWORDS[i], buff) == 0 && selectedColor == 1 && !isComment) {
          wattron(win, COLOR_PAIR(3));
          wprintw(win, "%s", buff);
          wattroff(win, COLOR_PAIR(3));
          found = true;
          break;
        }
        i++;
      }
      if (!found) {
        if (isComment) selectedColor = 7;
        wattron(win, COLOR_PAIR(selectedColor));  
        wprintw(win, "%s", buff);
        wattroff(win, COLOR_PAIR(selectedColor));
      }
    }
      // end color for functions
      if (line[charCount] == '(') {
        selectedColor = 1;
      }

    if ((isdigit(line[charCount]) || line[charCount] == '!') && selectedColor == 1 && !isComment) {
      wattron(win, COLOR_PAIR(4));
      wprintw(win, "%c", line[charCount]);
      wattroff(win, COLOR_PAIR(4));
      continue;
    }

    // create functions to split into words and to split between keys (e.g., < and >)
    // split between symbols (e.g., "")
    if (line[charCount] == '"' && startStr == false && !isComment) {
      startStr = true;
      selectedColor = 5;
    } else if (line[charCount] == '"' && startStr == true && !isComment) {
      startStr = false;
      wattron(win, COLOR_PAIR(selectedColor));
      wprintw(win, "%c", line[charCount]);
      wattroff(win, COLOR_PAIR(selectedColor));
      selectedColor = 1;
      continue;
    }

    // print line as comment
    if (line[charCount] == '/' && line[charCount+1] == '/') {
      isComment = true;
      selectedColor = 7;
    }

    // print line with color 3
    if (line[charCount] == '#' && !isComment) selectedColor = 3;

    if (isSpecial(line[charCount]) && !isComment) {
      wattron(win, COLOR_PAIR(9));
      wprintw(win, "%c", line[charCount]);
      wattroff(win, COLOR_PAIR(9));
      continue;
    }

    wattron(win, COLOR_PAIR(selectedColor));
    wprintw(win, "%c", line[charCount]);
    wattroff(win, COLOR_PAIR(selectedColor));
  }
  selectedColor = 1;
}

