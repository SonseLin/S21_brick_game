#include "../../../gui/sli/gui.h"
#include "../bricks_logic.h"

/**
 * @brief Initializes the game information.
 *
 * This function initializes the game information by allocating memory and
 * initializing the game field and current figure.
 *
 * @param game_info A pointer to the GameInfoExtended_t structure to be
 * initialized.
 *
 * @return int Returns 0 if the initialization is successful, otherwise returns
 * an error code.
 */
int init_game_info(GameInfoExtended_t *game_info) {
  int error = 0;

  error = alloc_game_info(game_info);

  if (!error) {
    init_figure(game_info);
    init_field(game_info);
  }

  return error;
}

/**
 * @brief Initializes the game field and game information.
 *
 * This function initializes the game field and game information by setting all
 * cells in the field to EMPTY, and initializing the game information attributes
 * such as score, high score, level, speed, pause, and lose flags.
 *
 * @param game_info A pointer to the GameInfoExtended_t structure to be
 * initialized.
 */
void init_field(GameInfoExtended_t *game_info) {
  for (int i = 0; i < GAME_FIELD_Y_ALLOC; i++) {
    for (int j = 0; j < GAME_FIELD_X_ALLOC; j++) {
      game_info->field[i][j] = EMPTY;
      game_info->next[i][j] = EMPTY;
    }
  }

  game_info->score = 0;
  game_info->high_score = 0;
  game_info->level = 0;
  game_info->speed = 0;
  game_info->pause = 0;
  game_info->lose = 0;
}

/**
 * @brief Initializes the current and next game figures and spawns the current
 * figure to the game field.
 *
 * This function initializes the current and next game figures by setting all
 * cells in their respective arrays to EMPTY, then it retrieves the next figure,
 * copies it to the current figure, retrieves the next figure again, and finally
 * spawns the current figure to the game field.
 *
 * @param game_info A pointer to the GameInfoExtended_t structure containing
 * game information and figures.
 */
void init_figure(GameInfoExtended_t *game_info) {
  // Initialize the current and next game figures by setting all cells to EMPTY
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game_info->figure_current->figure[i][j] = EMPTY;
      game_info->figure_next->figure[i][j] = EMPTY;
    }
  }

  // Retrieve the next figure and copy it to the current figure
  get_figure_next(game_info);
  copy_figure_next_to_current(game_info);

  // Retrieve the next figure again
  get_figure_next(game_info);

  // Spawn the current figure to the game field
  spawn_figure_to_game(game_info);
}

/**
 * @brief Initializes the ncurses settings for the game interface.
 *
 * This function initializes the ncurses settings for the game interface by
 * performing the following actions:
 * - Initializes the standard screen.
 * - Enters cbreak mode, allowing characters to be input without waiting for a
 * newline.
 * - Enables the keypad for the standard screen, allowing the program to capture
 * special keys such as function keys.
 * - Disables echoing of characters entered by the user.
 * - Sets the cursor visibility to be invisible.
 * - Enables non-blocking input mode for the standard screen, allowing the
 * program to check for input without blocking.
 */
void init_ncurses_settings() {
  initscr();             // Initializes the standard screen
  cbreak();              // Enters cbreak mode
  keypad(stdscr, TRUE);  // Enables the keypad for the standard screen
  noecho();              // Disables echoing of characters entered by the user
  curs_set(FALSE);       // Sets the cursor visibility to be invisible
  nodelay(stdscr,
          TRUE);  // Enables non-blocking input mode for the standard screen
}
