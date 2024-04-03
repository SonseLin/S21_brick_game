#include "game_info.h"



// TODO CHANGE HIGH SCORE AND FIELDS
void init_game_info(GameInfo_t* game_info) {
  game_info->field = NULL;
  game_info->next = NULL;
  game_info->score = 0;
  game_info->high_score = 0;
  game_info->level = 0;
  game_info->speed = 0;
  game_info->pause = 0;
}

void init_figure(FigureInfo_t* figure) {
  figure->x = 0;
  figure->y = 0;
  figure->pattern = 0;
  figure->state = 0;
  figure->possible_rotations = 0;
  figure->color = 0;
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
