#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

#include "../../brick_game/tetris/game_info.h"
#include "../../brick_game/tetris/logic.h"

#define O_Y_ALIGNMENT 1
#define O_X_ALIGNMENT 2
#define X_WIDTH 6

void shizophreniya();
UserAction_t get_user_input();

void print_game(GameInfoExtended_t* gie);
void print_border();
void print_next_figure(FigureInfo_t* fi);

#endif  // !DEBUG
