#include "game_info.h"
#include <stdlib.h>

int **alloc_2d(int row, int column) {
    int **arr = malloc(row * column * sizeof(int) + row * sizeof(int*));
    int *ptr = (int*) (arr + row);
    for(int i = 0; i < row; i++) {
        arr[i] = ptr + i * column;
    }
    return arr;
}

// TODO CHANGE HIGH SCORE AND FIELDS
void initGameInfo(GameInfo_t* game_info) {
  game_info->field = alloc_2d(HEIGHT, WIDTH);
  game_info->next = NULL;
  game_info->score = 0;
  game_info->high_score = 0;
  game_info->level = 0;
  game_info->speed = 0;
  game_info->pause = 0;
}


void terminateGame(GameInfoExtended_t *gi) {
  if(gi != NULL) {
  if(gi->game_info->next != NULL) {
    free(gi->game_info->next);
  }
  if(gi->game_info->field != NULL) {
    free(gi->game_info->field);
  }
  if(gi->figure != NULL) {
    free(gi->figure);
  }
  free(gi);
  }
}

void pause(GameInfoExtended_t *gi) {
  gi->game_info->pause = 1;
}

void unpause(GameInfoExtended_t *gi) {
  gi->game_info->pause = 0;
}

void game_over(GameInfoExtended_t* gi) {

}

void terminate(GameInfoExtended_t *gi) {
  gi->game_info->pause = -1;
}
