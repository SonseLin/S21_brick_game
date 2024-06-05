#include "brickgame/tetris/bricks_logic.h"
#include "gui/sli/gui.h"

/**
 * @brief Initializes ncurses settings and starts the game loop
 *
 * @return int 0 on success, -1 on failure
 */
int main() {
  init_ncurses_settings();
  putchar(KEY_ENTERR);
  putchar(KEY_LEFT);
  putchar(KEY_LEFT);
  gameloop();
  endwin();

  return 0;
}