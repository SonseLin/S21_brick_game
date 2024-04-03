#include "figure.h"
#include "game_info.h"

void initFigure(FigureInfo_t* fi) {
  fi->x = WIDTH / 2;
  fi->y = 2;
  fi->pattern = rand() % 7;
  fi->possible_rotations = fi->pattern > 2 ? 2 : 4;
  fi->state = 0;
  // fi->color = 
}
