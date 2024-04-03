#ifndef GAME_INFO_H
#define GAME_INFO_H

#include "figure.h"

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
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

GameInfo_t* initGameInfo();
GameInfoExtended_t* initGame(GameInfo_t* gi, bool hold, FigureInfo_t* fi, int time);
void terminateGame(GameInfoExtended_t* gi);

#endif
