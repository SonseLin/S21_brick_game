#include "../../../gui/sli/gui.h"
#include "../bricks_logic.h"
#include "string.h"
/**
 * @brief Main game loop that controls the flow of the game.
 *
 * This function initializes the game state, enters the main game loop where it
 * processes user actions, updates the game state, and renders the game until
 * the game is over. It handles game initialization, running the game loop
 * (including calling the backend logic and frontend rendering), and cleanup
 * after the game ends. If an error occurs during game initialization, it prints
 * an error message.
 */
void gameloop() {
  GameInfoExtended_t game_info_extnd;

  int error = init_game_info(&game_info_extnd);

  if (!error) {
    Automaton_t *automaton = getAutomaton();
    UserAction_t user_action = Start;
    int tick_count = 0;
    int collision = 0;
    game_info_extnd.speed = 100;

    frontend();
    init_after_menu(&user_action);

    if (user_action == Terminate)
      *automaton = GameOver;
    else
      *automaton = Spawn;

    while (*automaton != GameOver) {
      backend(&game_info_extnd, &user_action, &tick_count, &collision);
      frontend();
    }

    clear_cache_terminal();
    free_game_info(&game_info_extnd);
    free_api_game_info();
  } else {
    printf("Allocate memory error. Restart the Game.\n");
  }
}

/**
 * @brief Handles the backend logic of the game during the game loop.
 *
 * This function is responsible for managing the game's state transitions based
 * on the current state of the automaton and user actions. It processes game
 * logic such as spawning figures, moving figures, checking for collisions,
 * updating scores, and determining game over conditions. It also handles game
 * pause and resume functionality. After processing the game logic, it updates
 * the game state to be used by the frontend for rendering.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing
 * extended game information.
 * @param user_action Pointer to the UserAction_t enum indicating the current
 * user action.
 * @param tick_count Pointer to an integer tracking the number of ticks since
 * the last action.
 * @param collision Pointer to an integer indicating whether a collision has
 * occurred. 1 or 0.
 */

void backend(GameInfoExtended_t *game_info, UserAction_t *user_action,
             int *tick_count, int *collision) {
  Automaton_t *automaton = getAutomaton();

  if (*automaton == Spawn) {
    spawn_figure_to_game(game_info);
    *collision = 0;
    *automaton = Moving;
  } else if (game_info->pause) {
    clear_cache_terminal();
    game_info->pause = 0;
    *user_action = Start;
  } else if (*automaton == Moving) {
    if (skip_tick(game_info, tick_count)) {
      *automaton = Shifting;
    } else {
      if (*user_action == Pause) {
        game_info->pause = 1;
      } else {
        game_move_procces(game_info, user_action, collision);
      }
      if (*collision)
        *automaton = Collided;
      else if (*user_action == Terminate)
        *automaton = GameOver;
    }
  } else if (*automaton == Collided) {
    score_update(game_info);
    copy_next_to_field(game_info, GAME_FIELD_Y_END, GAME_FIELD_X_END);
    *automaton = Attaching;
  } else if (*automaton == Attaching) {
    if (can_spawn_figure(game_info))
      *automaton = Spawn;
    else
      *automaton = GameOver;
  } else if (*automaton == Shifting) {
    *automaton = Moving;
  } else if (*automaton == Start_automaton) {
    *automaton = Spawn;
  }
  copy_game_info_extended_to_api(game_info);
}

/**
 * @brief Processes the movement of the game figure based on user actions.
 *
 * This function retrieves the current user action and determines if a collision
 * occurs with the next move. If no collision is detected, it proceeds to move
 * the figure according to the user's action. It also introduces a short delay
 * after processing the move to regulate the game's pace.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing
 * extended game information.
 * @param user_action Pointer to the UserAction_t enum indicating the current
 * user action. This parameter is updated to the latest user action at the
 * beginning of the function.
 * @param collision Pointer to an integer that will be set to 1 if a collision
 * is detected, or 0 otherwise. This parameter is used to control the game flow
 * based on collision status.
 */
void game_move_procces(GameInfoExtended_t *game_info, UserAction_t *user_action,
                       int *collision) {
  *user_action =
      get_user_action();  // Update the user action to the latest input
  if ((*collision = is_collision(game_info)) ==
      0) {  // Check for collision and proceed if none
    move_figure(user_action,
                game_info);  // Move the figure based on the user action
  }
  napms(10);  // Introduce a short delay to regulate game pace
}

/**
 * @brief initializes the user action after the menu
 *
 * This function initializes the user action to "Action" and waits for the user
 * to either press "Start" or "Terminate". If the user presses "Start", the
 * function sets the user action to "Start" and exits the loop. If the user
 * presses "Terminate", the function sets the user action to "Terminate" and
 * exits the loop.
 *
 * @param user_action pointer to the user action variable that will be updated
 * with the latest user action
 */

void init_after_menu(UserAction_t *user_action) {
  *user_action = Action;
  while (*user_action != Terminate && *user_action != Start) {
    *user_action = get_user_action();
    if (*user_action == Start) {
      break;
    }
  }
}

/**
 * @brief Determines if a game tick should be skipped based on the game's speed
 * setting.
 *
 * This function checks if the number of ticks since the last action has reached
 * the threshold defined by the game's speed setting. If the threshold is
 * reached, the function resets the tick count, moves the game figure down by
 * one position, and adds the next position of the figure to the game. This
 * simulates the automatic downward movement of the game figure. The function
 * then marks the tick as skipped. If the threshold is not reached, it simply
 * increments the tick count. This mechanism controls the pace of the game,
 * making the game figure move down automatically at a speed determined by the
 * game's current speed setting.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing
 * extended game information.
 * @param tick_count Pointer to an integer tracking the number of ticks since
 * the last action. This value is reset to 0 if the tick is skipped, or
 * incremented otherwise.
 *
 * @return int Returns 1 if the tick is skipped (indicating that the figure has
 * been moved down and the game state updated), or 0 if the tick is not skipped.
 */

int skip_tick(GameInfoExtended_t *game_info, int *tick_count) {
  int is_skipped = 0;

  if (*tick_count >= game_info->speed) {
    *tick_count = 0;
    move_pos_figure_down(game_info);
    add_next_pos_figure_to_game(game_info);
    is_skipped = 1;
  }
  *tick_count += 1;

  return is_skipped;
}

/**
 * @brief Clears the terminal input buffer.
 *
 * This function reads characters from the terminal input buffer until it
 * encounters the Enter key (KEY_ENTERR). It is used to ensure that any pending
 * input characters are consumed and do not affect subsequent reads from the
 * input. This is particularly useful for clearing any residual input, such as
 * when pausing the game and resuming it, to prevent unintended actions upon
 * resumption.
 */

void clear_cache_terminal() {
  char off_pause;
  while ((off_pause = getch()) != KEY_ENTERR) {
    ;
  }
}

/**
 * @brief Updates the game score based on the number of filled rows, and checks
 * for level up conditions.
 *
 * This function first checks for any full rows in the game field and calculates
 * the score based on the number of filled rows cleared. It then updates the
 * game score accordingly. After updating the score, it checks if the conditions
 * for leveling up are met based on the score achieved. If so, it increases the
 * game level and adjusts the game speed to make the game more challenging.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing
 * extended game information, including the current score and level.
 */
void score_update(GameInfoExtended_t *game_info) {
  int count_fill_rows =
      check_full_rows(game_info);     // Calculate the number of full rows
  int last_score = game_info->score;  // Store the current score before updating
  add_score(game_info,
            count_fill_rows);    // Update the score based on filled rows
  lvlUp(game_info, last_score);  // Check and process level up conditions
}

/**
 * @brief Removes a full line from the game field by shifting all rows above it
 * down.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing
 * extended game information.
 * @param start_row The row index of the first row of the full line to be
 * removed.
 */

void remove_full_line(GameInfoExtended_t *game_info, int start_row) {
  for (int i = start_row; i > 0; i--) {
    for (int j = 0; j < GAME_FIELD_X_END; j++) {
      game_info->next[i][j] = game_info->next[i - 1][j];
    }
  }

  for (int j = 0; j < GAME_FIELD_X_END; j++) {
    game_info->next[0][j] = EMPTY;
  }
}

/**
 * @brief Checks and counts the number of full rows in the game field.
 *
 * This function iterates through the game field from the bottom up, checking
 * each row to determine if it is full (i.e., no empty spaces). A row is
 * considered full if all its cells are occupied by a part of a game figure.
 * When a full row is found, it is removed by calling the remove_full_line
 * function, and the count of full rows is incremented. The process stops either
 * when all rows have been checked or after finding and removing four full rows,
 * as removing more than four rows in a single action is not a standard Tetris
 * feature.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing
 * extended game information, including the current state of the game field.
 *
 * @return int The number of full rows found and removed from the game field.
 */
int check_full_rows(GameInfoExtended_t *game_info) {
  int count_fill_rows = 0;
  for (int i = GAME_FIELD_Y_END - 1; i >= 0 && count_fill_rows < 4; i--) {
    int is_row_full = 1;
    for (int j = GAME_FIELD_X_END - 1; j >= 0; j--) {
      if (game_info->next[i][j] == EMPTY) {
        is_row_full = 0;
        break;
      }
    }
    if (is_row_full) {
      remove_full_line(game_info, i);
      count_fill_rows++;
      i++;  // Increment i to recheck the same row index after rows above have
            // been shifted down
    }
  }

  return count_fill_rows;
}

/**
 * @brief Updates the game score based on the number of filled rows cleared.
 *
 * This function increases the game score according to the number of consecutive
 * rows cleared in a single move. The scoring is based on classic scoring rules
 * where clearing more rows at once results in a higher score increase.
 * Specifically, clearing one row adds 100 points, two rows add 300 points,
 * three rows add 700 points, and clearing four rows (also known as a "Tetris")
 * adds 1500 points. This incentivizes clearing multiple rows simultaneously.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing the
 * game's current state, including the score.
 * @param count_fill_rows The number of filled rows that have been cleared. This
 * value determines how much the score will be increased.
 */

/**
 * @brief Updates the game score based on the number of filled rows cleared.
 *
 * This function increases the game score according to the number of consecutive
 * rows cleared in a single move. The scoring is based on classic scoring rules
 * where clearing more rows at once results in a higher score increase.
 * Specifically, clearing one row adds 100 points, two rows add 300 points,
 * three rows add 700 points, and clearing four rows (also known as a "Tetris")
 * adds 1500 points. This incentivizes clearing multiple rows simultaneously.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing the
 * game's current state, including the score.
 * @param count_fill_rows The number of filled rows that have been cleared. This
 * value determines how much the score will be increased.
 */
void add_score(GameInfoExtended_t *game_info, int count_fill_rows) {
  switch (count_fill_rows) {
    case 1:
      game_info->score += 100;
      break;
    case 2:
      game_info->score += 300;
      break;
    case 3:
      game_info->score += 700;
      break;
    case 4:
      game_info->score += 1500;
      break;
    default:
      break;
  }
}
/**
 * @brief Updates the game level and speed based on the score achieved.
 *
 * This function checks if the conditions for leveling up are met based on the
 * score achieved. If so, it increases the game level and adjusts the game speed
 * to make the game more challenging.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing
 * extended game information, including the current score and level.
 * @param last_score The previous score before the current update. This value is
 * used to determine if a level up condition has been met.
 */
void lvlUp(GameInfoExtended_t *game_info, int last_score) {
  if ((game_info->score / 600) > (last_score / 600)) {
    game_info->level++;
    if (game_info->speed != 10) game_info->speed -= 10;
  }
}
/**
 * @brief Copies the contents of the next game field to the current game field.
 *
 * This function copies the contents of the next game field (which is used for
 * temporary storage during gameplay) to the current game field, overwriting any
 * existing contents. The function iterates through each row and column of the
 * next game field and copies the corresponding cell value to the current game
 * field.
 *
 * @param game_info Pointer to the GameInfoExtended_t structure containing
 * extended game information, including the current state of both the next and
 * current game fields.
 * @param rows The number of rows in the game field.
 * @param cols The number of columns in the game field.
 */
void copy_next_to_field(GameInfoExtended_t *game_info, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      game_info->field[i][j] = game_info->next[i][j];
    }
  }
}