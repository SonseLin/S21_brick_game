
#ifndef BRICKGAME_SRC_GUI_SLI_GUI_H_
#define BRICKGAME_SRC_GUI_SLI_GUI_H_

#include "../../brickgame/tetris/bricks_logic.h"
#include "ncurses.h"

#define GAME_WALL_Y_START 0
#define GAME_WALL_X_START 0
#define GAME_WALL_Y_END 22
#define GAME_WALL_X_END 22

#define SCORE_WALL_Y_END 42
#define SCORE_WALL_X_END 22

#define EMPTY_GUI "__"
#define BRICK_GUI "[]"

#endif  // BRICKGAME_SRC_GUI_SLI_GUI_H_

void frontend();

void print_menu();
void print_pause();

void print_game(GameInfo_t game_info);
void print_score_panel(GameInfo_t game_info);
void print_game_panel(GameInfo_t game_info);
void print_close_game(GameInfo_t game_info);
void print_text_to_centr(char *text, int y_pos);
