#include "../../cli/gui/interface.h"
#include "figure.h"
#include "game_info.h"
#include "logic.h"

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, 1);
  nodelay(stdscr, 1);
  shizophreniya();

  GameInfo_t* game_info = initGameInfo();
  FigureInfo_t* figure_info = initFigure();
  figure_info->pattern = 2;
  GameInfoExtended_t* gie = initGame(game_info, false, figure_info, 0);

  FigureContainer* container = createContainer();
  container->current = figure_info;

  while (gie->game_info->pause != -1) {
    clear();
    print_game(gie);
    print_next_figure(gie->figure);
    print_border();
    int c = getch();
    refresh();
    napms(50 * gie->game_info->speed + 50);
    if (c == 'p') {
      gie->game_info->pause == 1 ? unpause(gie) : pause(gie);
    }
    while (gie->game_info->pause == 1) {
      c = getch();
      if (c == 'p') {
        gie->game_info->pause = 0;
      }
    }
    if (c == 'q') {
      terminate(gie);
    }
  }
  freeGame(gie);
  nodelay(stdscr, 0);
  getch();
  // add endgame data
  curs_set(1);
  endwin();
  return 0;
}
