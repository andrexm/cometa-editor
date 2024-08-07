#pragma once 

#include <ncurses.h>

#include "codepanel.h"
#include "config.h"
#include "cursor.h"
#include "statuspanel.h"

// basic hjkl movements
bool basicMoves(int c) {
  switch (c) {  
    case 'j': // move down
    case KEY_DOWN:
      cursorMoveDown();    
      return true;
      break;
    case 'k': // move up
    case KEY_UP:
      cursorMoveUp();
      return true;
      break;
      
    case 'h': // move left
    case KEY_LEFT:
      cursorMoveLeft();
      return true;
      break;

    case 'l': // move right
    case KEY_RIGHT:
      cursorMoveRight();
      return true;
      break;

    case KEY_NPAGE:
      scrollWindowDown();
      // the next 2 lines: move cursor to the end of that line if necessary
      cursorMoveRight();
      cursorMoveLeft();
      return true;

    case KEY_PPAGE:
      scrollWindowUp();
      // the next 2 lines: move cursor to the end of that line if necessary
      cursorMoveRight();
      cursorMoveLeft();
      return true;

    case KEY_HOME:
      cursorOnLeftSide();
      return true;

    case KEY_END:
      cursorOnRightSide();
      return true;
  }
  return false;
}

// movements involving the 'g' key
bool goMoves(int c) {
  if (c != 'g') return false;
  c = wgetch(code_panel.win); // get the movement char

  // TODO: implement whowing the tips panel

  switch (c) {
    case 'h': // start of line
    case KEY_LEFT:
      cursorOnLeftSide();
      return true;

    case 'j': // end of window
    case KEY_DOWN:
      cursorOnBottomSide();
      return true;

    case 'k': // start of window
    case KEY_UP:
      cursorOnTopSide();
      return true;

    case 'l': // end of line
    case KEY_RIGHT:
      cursorOnRightSide();
      return true;

    case 'g': // go to first line
      cursorGoFirstLine();
      return true;

    case 'e': // go to last line
      cursorGoLastLine();
      return true;
  }
  return false;
}

bool movement(int c) {
  if (basicMoves(c) || goMoves(c)) {
    updateStatus();  
    return true;
}

  return false;
}
