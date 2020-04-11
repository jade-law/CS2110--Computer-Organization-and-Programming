#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //

void startScreen(void);

typedef struct platform {
  int col;
  int top;
  int bot;
  int left;
  int right;
  int score;
} Platform;

typedef struct brick {
  int row;
  int col;
  int topBorder;
  int botBorder;
  int leftBorder;
  int rightBorder;
  u16 color;
  int points;
} Brick;

typedef struct layer {
  int layerNum;
  Brick arr[9];
} Layer;

typedef enum {
  LEFT,
  RIGHT,
} Direction;

typedef struct ball {
  int row;
  int col;
  int bot;
  int right;
} Ball;

typedef enum {
  STARTBG,
  STARTTEXT,
  PLAYCLEAR,
  PLAY,
  WINCLEAR,
  WINBG,
  WINTEXT,
  LOSECLEAR,
  LOSEBG,
  LOSETEXT,
} GBAState;

void makePlatform(void);
void playBreakout(GBAState *state);
void setUpBricks(void);
void delay(int i);
Ball setBall(void);
void trackScore(u16 color);

#endif
