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

void initFigure(FigureInfo_t* fi);


#endif
