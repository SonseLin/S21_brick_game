#include "figure.h"

#include "game_info.h"

FigureInfo_t* initFigure() {
  FigureInfo_t* fi = malloc(sizeof(FigureInfo_t*) * 2);
  fi->x = WIDTH / 2;
  fi->y = 3;
  fi->pattern = rand() % 7;
  fi->possible_rotations = fi->pattern > 2 ? 2 : 4;
  fi->state = 0;
  // fi->color =
  return fi;
}

FigureContainer* createContainer() {
  return malloc(sizeof(FigureContainer) * 2);
}

void appendToContainer(FigureContainer* fc, FigureInfo_t* fi) {
  while (fc->next != NULL) {
    fc = fc->next;
  }
  FigureContainer* new = createContainer();
  new->current = fi;
  fc->next = new;
}

void freeContainer(FigureContainer* fc) {
  if (fc != NULL) {
    while (fc->next != NULL) {
      FigureContainer* tmp = fc->next;
      free(fc->current);
      free(fc);
      fc->next = tmp;
    }
    free(fc->current);
    free(fc);
  }
}

void rotateFigure(FigureInfo_t* fi) {
  fi->state = (fi->state + 1) % fi->possible_rotations;
}

void moveFigureRight(FigureInfo_t* fi) { fi->x += 1; }
void moveFigureLeft(FigureInfo_t* fi) { fi->x -= 1; }
void moveFigureDown(FigureInfo_t* fi) { fi->y += 1; }