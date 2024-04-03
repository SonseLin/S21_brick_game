#ifndef FIGURE_H
#define FIGURE_H

typedef struct {
  int x;
  int y;
  int pattern;
  int state;
  int possible_rotations;
  int color;
} FigureInfo_t;

typedef struct FigureContainer {
  FigureInfo_t* current;
  struct FigureContainer* next;
} FigureContainer;

FigureInfo_t* initFigure();

FigureContainer* createContainer();
void appendToContainer(FigureContainer* fc, FigureInfo_t* fi);
void freeContainer(FigureContainer* fc);

void rotateFigure(FigureInfo_t* fi);
void moveFigureRight(FigureInfo_t* fi);
void moveFigureLeft(FigureInfo_t* fi);
void moveFigureDown(FigureInfo_t* fi);

#endif
