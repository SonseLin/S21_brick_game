#ifndef GAME_INFO_H
#define GAME_INFO_H

#include "figure.h"
#include "stdlib.h"

#define bool int
#define true 1
#define false 0

#define HEIGHT 20
#define WIDTH 10


typedef enum {
  Start = 0,
  Pause = 1,
  Terminate = -1,
  Left = 2,
  Right = 3,
  Up = 4,
  Down = 5,
  Action = 6
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  GameInfo_t* game_info;
  bool hold;
  FigureInfo_t* figure;
  int time;
} GameInfoExtended_t;

int **alloc_2d(int row, int column); 

void initGameInfo(GameInfo_t* gi);
GameInfoExtended_t* initGame(GameInfo_t* gi, bool hold, FigureInfo_t* fi, int time);
void terminateGame(GameInfoExtended_t* gi);

void pause(GameInfoExtended_t* gi);
void unpause(GameInfoExtended_t* gi);
void game_over(GameInfoExtended_t* gi);
void terminate(GameInfoExtended_t* gi);

#endif
