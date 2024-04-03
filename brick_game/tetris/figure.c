#include "figure.h"

#include "game_info.h"

FigureInfo_t* initFigure() {
  FigureInfo_t* fi = malloc(sizeof(FigureInfo_t*) * 2);
  fi->x = WIDTH / 2;
  fi->y = 2;
  fi->pattern = rand() % 7;
  fi->possible_rotations = fi->pattern > 2 ? 2 : 4;
  fi->state = 0;
  // fi->color =
  return fi;
}

typedef struct {
  FigureInfo_t* current;
  FigureInfo_t* next;
} FigureContainer;