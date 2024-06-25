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
      cursorMoveDown(code_panel.win);    
      return true;
      break;
    case 'k': // move up
    case KEY_UP:
      cursorMoveUp(code_panel.win);
      return true;
      break;
      
    case 'h': // move left
    case KEY_LEFT:
      cursorMoveLeft(code_panel.win);
      return true;
      break;

    case 'l': // move right
    case KEY_RIGHT:
      cursorMoveRight(code_panel.win);
      return true;
      break;
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
      cursorOnLeftSide(code_panel.win);
      return true;

    case 'j': // end of window
    case KEY_DOWN:
      cursorOnBottomSide(code_panel.win);
      return true;

    case 'k': // start of window
    case KEY_UP:
      cursorOnTopSide(code_panel.win);
      return true;

    case 'l': // end of line
    case KEY_RIGHT:
      cursorOnRightSide(code_panel.win);
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
