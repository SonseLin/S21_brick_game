#include "figure.h"
#include "game_info.h"

int main() {
  GameInfo_t* game_info;
  FigureInfo_t* figure_info;
  initGameInfo(game_info);
  initFigure(figure_info);
  
  GameInfoExtended_t* gie;
  initGame(game_info, false, figure_info, 0);
  while(gie->game_info->pause >= 0) {

  }
  // add endgame data
}
