#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/start_background.h"
#include "images/win_background.h"
#include "images/game_over.h"
#include "images/white_ball.h"

Layer layerArr[5];
Ball b;
Platform p;
char buffer[51];

int main(void) {
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  videoBuffer[1208] = 0x7fff;

  //button shtuff
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial game state
  GBAState state = STARTBG;

  //start gba
  while (1) {
    currentButtons = BUTTONS;  // Load the current state of the buttons

    waitForVBlank();

    switch (state) {
      case STARTBG:       //start screen
        drawFullScreenImageDMA(start_background);
        state = STARTTEXT;
        break;
      case STARTTEXT:
        drawString(80, 100, "BREAKOUT", WHITE);
        if (KEY_DOWN(BUTTON_START, currentButtons)) {       //press return move to PLAY
          state = PLAYCLEAR;
        }
        break;
      case PLAYCLEAR:
        fillScreenDMA(BLACK);
        state = PLAY;
        break;
      case PLAY:        //play screen
        playBreakout(&state); //pass in current buttons pointer(?)
        //button control in playBreakout
        break;
      case WINCLEAR:
        fillScreenDMA(BLACK);
        state = WINBG;
        break;
      case WINBG:         //win screen all bricks cleared
        drawFullScreenImageDMA(win_background);
        state = WINTEXT;
        break;
      case WINTEXT:
        sprintf(buffer, "SCORE: %d", p.score);
        drawString(100, 97, buffer, WHITE);
        if (KEY_DOWN(BUTTON_START, currentButtons)) {   //press return to go to cake
          state = PLAYCLEAR;
        } else if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {   //press delete to go to start
          state = STARTBG;
        }
        break;
      case LOSECLEAR:          //lose screen ball fell off screen
        fillScreenDMA(BLACK);
        state = LOSEBG;
        break;
      case LOSEBG:
        drawFullScreenImageDMA(game_over);
        state = LOSETEXT;
        break;
      case LOSETEXT:
        sprintf(buffer, "SCORE: %d", p.score);
        drawString(120, 97, buffer, WHITE);
        if (KEY_DOWN(BUTTON_START, currentButtons)) {     //press return to play
          state = PLAYCLEAR;
        } else if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {       //press delete to go to start
          state = STARTBG;
        }
        break;
    }
    previousButtons = currentButtons;  // Store the current state of the buttons
  }
  UNUSED(previousButtons);  // You can remove this once previousButtons is used
  return 0;
}


void setUpBricks(void) {                                  //draw and make layerArr and arr
  u16 brickColors[5] = {RED, YELLOW, GREEN, CYAN, BLUE};
  int currRow = 10;
  int currPoints = 5;
  for (int i = 0; i < 5; i++) {               //iterate through layers
    layerArr[i].layerNum = i + 1;
    int currCol = 3;
    for (int j = 0; j < 9; j ++) {            //iterate through columns
      Brick b;
      b.topBorder = currRow;
      b.leftBorder = currCol;
      b.botBorder = currRow + 4;
      b.rightBorder = currCol + 25;
      b.color = brickColors[i];
      b.points = currPoints;
      drawRectDMA(b.topBorder, b.leftBorder, 25, 4, b.color);
      layerArr[i].arr[j] = b;                 //layerArr bricks in each row
      currCol = currCol + 26;
    }
    currRow = currRow + 5;
  }
}

Ball setBall(void) {                      //make ball and draw
  Ball b;
  b.row = 135;
  b.col = 118;
  b.right = b.col + 2;
  b.bot = b.row + 2;
  drawImageDMA(b.row, b.col, 2, 2, whiteball);
  return b;
}

void playBreakout(GBAState *state) {        //game
  setUpBricks();      //set bricks
  makePlatform();       //make draw platform
  b = setBall();            //make draw ball
  trackScore(BLACK);
  int rd = -1;    //starting direction up
  int cd = 1;     //starting direction right
  u32 buttons;
  while (*state == PLAY) {
    waitForVBlank();
    buttons = BUTTONS;
    if (KEY_DOWN(BUTTON_LEFT, buttons)) {     //move platform left
      drawRectDMA(140, p.col, 25, 5, BLACK);
      p.col--;
      p.left--;
      p.right--;
      if (p.col <= 0) {
        p.col = 0;
        p.left = p.col;
        p.right = p.col + 25;
      }
      drawRectDMA(140, p.col, 25, 5, WHITE);
    }
    if (KEY_DOWN(BUTTON_RIGHT, buttons)) {    //move platform right;
      drawRectDMA(140, p.col, 25, 5, BLACK);
      p.col++;
      p.left++;
      p.right++;
      if (p.right >= 240) {
        p.right = 240;
        p.left = p.right - 25;
        p.col = p.left;
      }
      drawRectDMA(140, p.col, 25, 5, WHITE);
    }
    drawRectDMA(b.row, b.col, 2, 2, BLACK);     //clear previous ball
    if (b.row < 0) {    //if ball reaches top border
      rd = 1;
      b.row = 0;
    } else if(b.row > 160) {      //if ball reaches bottom border
      *state = LOSECLEAR;                    //should drop through and go to lose screen
      return;
    } else if (b.row < 35) {      //all bricks above 35 so check for collisions
      for (int i = 0; i < 5; i++) {         //iterate through layerArr
        for (int j = 0; j < 9; j++) {           //iterate through arr
          int bot = layerArr[i].arr[j].botBorder;
          int top = layerArr[i].arr[j].topBorder;
          int right = layerArr[i].arr[j].rightBorder;
          int left = layerArr[i].arr[j].leftBorder;
          u16 color = layerArr[i].arr[j].color;
          if (rd > 0 && cd > 0) {         //moving down right
            if (b.bot == top && b.right > left && b.col < right) {      //hit from top
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                rd = -1;
              }
            } else if (right == left && b.row < bot && b.bot > top) {  //hit from left
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                cd = -1;
              }
            }
          } else if (rd < 0 && cd > 0) {  //moving up right
            if (b.row == bot && b.right > left && b.col < right) {          //hit from bot
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                rd = 1;
              }
            } else if (b.right == left && b.row < bot && b.bot > top) {     //hit from left
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                cd = -1;
              }
            }
          } else if (rd < 0 && cd < 0) {  //moving up left
            if (b.row == bot && b.right > left && b.col < right) {          //hit from bot
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                rd = 1;
              }
            } else if (b.col == right && b.row < bot && b.bot > top) {       //hit from right
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                cd = 1;
              }
            }
          } else if (rd > 0 && cd < 0) {  //moving down left
            if (b.bot == top && b.right > left && b.col < right) {          //hit from top
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                rd = -1;
              }
            } else if (b.col == right && b.row < bot && b.bot > top) {   //hit from right
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                cd = 1;
              }
            }
          }
        }
      }
    }
    if(b.col < 0) {                 //ball reach left border
      cd = 1;
      b.col = 0;
    } else if(b.col > 238) {        //ball reaches right border
      cd = -1;
      b.col = 235;
    }
    if (b.row + 2 >= p.top && b.col >= p.left && b.col + 2 <= p.right) {
      rd = -1;
      b.row = p.top - 2;
    } 
    b.row = b.row + rd;
    b.col = b.col + cd;
    b.right = b.col + 2;
    b.bot = b.row + 2;
    drawImageDMA(b.row, b.col, 2, 2, whiteball);
    delay(1);
    if (p.score == 135) {
      *state = WINCLEAR;
      return;
    }
    if (KEY_DOWN(BUTTON_SELECT, buttons)) {      //return to start screen
      fillScreenDMA(BLACK);
      *state = STARTBG;
      return;
    }
  }
}

void trackScore(u16 color) {
  drawRectDMA(150, 5, 60, 8, BLACK);
  if (color == RED) {
    p.score += 5;
  } else if (color == YELLOW) {
    p.score += 4;
  } else if (color == GREEN) {
    p.score += 3;
  } else if (color == CYAN) {
    p.score += 2;
  } else if (color == BLUE) {
    p.score += 1;
  }
  char buffer[51];
  sprintf(buffer, "SCORE: %d", p.score);
  drawString(150, 5, buffer, WHITE);
  UNUSED(color);
}

void delay(int n) {         //make movement slower
  volatile int x = 0;
  for(int i=0; i<n*8000; i++) {
    x++;
  }
}

void makePlatform(void) {       //make and draw platform
  p.col = 108;
  p.top = 140;
  p.bot = p.top + 5;
  p.left = 108;
  p.right = p.left + 25;
  p.score = 0;
  drawRectDMA(140, p.col, 25, 5, WHITE);
}
