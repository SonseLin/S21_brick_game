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

typedef struct {
  FigureInfo_t* current;
  FigureContainer* next;
} FigureContainer;

FigureInfo_t* initFigure();

FigureContainer* createContainer();
void appendToContainer(FigureContainer* fc, FigureInfo_t* fi);
void freeContainer(FigureContainer* fc);

#endif
