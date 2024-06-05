#include <time.h>

#include "../bricks_logic.h"
#include "../figure_samples/figure_samples.h"
/**
 * @brief Moves the figure according to the user action.
 *
 * This function moves the figure in the game according to the user's action.
 * It checks the validity of the move and updates the game state accordingly.
 *
 * @param user_action The action to be performed on the figure.
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 */
void move_figure(UserAction_t *user_action, GameInfoExtended_t *game_info) {
  int can_move = 1;
  int **temp_rotated_figure = rotated_figure(game_info);
  switch (*user_action) {
    case Down:
      move_pos_figure_down(game_info);
      break;
    case Left:
      if ((can_move = can_move_left(game_info)) == 1)
        move_pos_figure_left(game_info);
      break;
    case Right:
      if ((can_move = can_move_right(game_info)) == 1)
        move_pos_figure_right(game_info);
      break;
    case Action:
      if ((can_move = can_rotate(game_info, temp_rotated_figure, can_move)) ==
          1)
        rotate_figure(game_info, temp_rotated_figure);
      free_temp_figure(temp_rotated_figure, 4);
      break;
    default:
      break;
  }

  if (can_move) add_next_pos_figure_to_game(game_info);
}

int getRandomFigureNumber() { return rand() % 7 + 1; }

void clear_next_figure(GameInfoExtended_t *game_info) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_info->figure_next->figure[i][j] == BRICK)
        game_info->figure_next->figure[i][j] = EMPTY;
    }
  }
}

void clear_current_figure(GameInfoExtended_t *game_info) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_info->figure_current->figure[i][j] == BRICK)
        game_info->figure_current->figure[i][j] = EMPTY;
    }
  }
  game_info->figure_current->x_figure = 0;
  game_info->figure_current->y_figure = 0;
}
/**
 * @brief Generates a new figure for the next drop.
 *
 * This function generates a new figure for the next drop in the game. It clears
 * the current next figure and then selects a random figure from the available
 * ones.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 */
void get_figure_next(GameInfoExtended_t *game_info) {
  /**
   * @brief Clears the next figure.
   *
   * This function clears the current next figure by setting all its bricks to
   * empty.
   *
   * @param game_info A pointer to the GameInfoExtended_t struct containing the
   * game state.
   */
  clear_next_figure(game_info);

  int figure_num = getRandomFigureNumber();
  // int figure_num = 6;
  if (figure_num == 4) {
    // cursed japan number
    figure_num++;
  }
  switch (figure_num) {
    case 1:
      getFigureSnakeRight(game_info);
      break;
    case 2:
      getFigureBox(game_info);
      break;
    case 3:
      getFigureLeftAngle(game_info);
      break;
    // case 4:
    //   getFigureRightAngle(game_info);
    //   break;
    case 5:
      getFigureSnakeLeft(game_info);
      break;
    case 6:
      getFigureLine(game_info);
      break;
    case 7:
      getFigureTriangle(game_info);
      break;
  }

  game_info->figure_next->y_figure = 0;
  game_info->figure_next->x_figure = FIGURE_CENTR_X;
}
/**
 * @brief Spawns the current figure to the game field.
 *
 * This function spawns the current figure to the game field by copying the
 * figure from the next drop to the current position and updating the game
 * state.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 */
void spawn_figure_to_game(GameInfoExtended_t *game_info) {
  copy_figure_next_to_current(
      game_info);  // Updates the game field with the current figure.

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_info->figure_current->figure[i][j] == BRICK) {
        game_info->next[i][j + FIGURE_CENTR_X] =
            game_info->figure_current->figure[i][j];
      }
    }
  }

  get_figure_next(game_info);  // Generates a new figure for the next drop.
}
/**
 * @brief Checks if the current figure collides with the game field.
 *
 * This function checks if the current figure collides with the game field.
 * It iterates through the figure and checks if any of its bricks collide with
 * the game field blocks.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 *
 * @return 1 if there is a collision, 0 otherwise.
 */
int is_collision(GameInfoExtended_t *game_info) {
  int collision = 0;

  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (game_info->figure_current->figure[i][j] == BRICK) {
        if (game_info->field[i + game_info->figure_current->y_figure + 1]
                            [j + game_info->figure_current->x_figure] ==
                BRICK ||
            i + game_info->figure_current->y_figure + 1 == GAME_FIELD_Y_END) {
          collision = 1;
        }
      }
    }
  }

  return collision;
}

int can_move_right(GameInfoExtended_t *game_info) {
  int can_move_left = 1;

  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (game_info->figure_current->figure[i][j] == BRICK) {
        if (game_info->field[i + game_info->figure_current->y_figure]
                            [j + game_info->figure_current->x_figure + 1] ==
                BRICK ||
            j + game_info->figure_current->x_figure + 1 == GAME_FIELD_X_END) {
          can_move_left = 0;
        }
      }
    }
  }

  return can_move_left;
}

int can_move_left(GameInfoExtended_t *game_info) {
  int can_move_left = 1;

  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (game_info->figure_current->figure[i][j] == BRICK) {
        if (game_info->field[i + game_info->figure_current->y_figure]
                            [j + game_info->figure_current->x_figure - 1] ==
                BRICK ||
            j + game_info->figure_current->x_figure == 0) {
          can_move_left = 0;
        }
      }
    }
  }

  return can_move_left;
}

int can_move_down(GameInfoExtended_t *game_info) {
  int can_move = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_info->figure_current->figure[i][j] == BRICK) {
        if (game_info->field[i + game_info->figure_current->y_figure + 1]
                            [j + game_info->figure_current->x_figure] !=
            EMPTY) {
          can_move = 0;
        }
      }
    }
  }

  return can_move;
}
/**
 * @brief Clears the current figure from the game field.
 *
 * This function clears the current figure from the game field by
 * copying the figure from the next drop to the current position and
 * updating the game state.
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 */
void clear_current_figure_from_game(GameInfoExtended_t *game_info) {
  int y_figure = game_info->figure_current->y_figure;
  int x_figure = game_info->figure_current->x_figure;

  for (int i_game = y_figure, i_figure = 0; i_game < 4 + y_figure;
       i_game++, i_figure++) {
    for (int j_game = x_figure, j_figure = 0; j_game < 4 + x_figure;
         j_game++, j_figure++) {
      if (game_info->figure_current->figure[i_figure][j_figure] == BRICK)
        game_info->next[i_game][j_game] = EMPTY;
    }
  }
}
/**
 * @brief Clears the current figure from the game field and adds the next
 * position figure to the game field.
 *
 * This function clears the current figure from the game field by copying the
 * figure from the next drop to the current position and updating the game
 * state. Then, it adds the next position figure to the game field.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 */
void add_next_pos_figure_to_game(GameInfoExtended_t *game_info) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int y_figure_pixel = i + game_info->figure_current->y_figure;
      int x_figure_pixel = j + game_info->figure_current->x_figure;
      if (game_info->figure_current->figure[i][j] == BRICK) {
        game_info->next[y_figure_pixel][x_figure_pixel] =
            game_info->figure_current->figure[i][j];
      }
    }
  }
}
/**
 * @brief Moves the current figure down in the game field.
 *
 * This function moves the current figure down in the game field by clearing the
 * current figure from its current position and updating the y-coordinate of the
 * figure's position.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 */
void move_pos_figure_down(GameInfoExtended_t *game_info) {
  clear_current_figure_from_game(game_info);
  game_info->figure_current->y_figure = game_info->figure_current->y_figure + 1;
}

void move_pos_figure_left(GameInfoExtended_t *game_info) {
  clear_current_figure_from_game(game_info);
  game_info->figure_current->x_figure = game_info->figure_current->x_figure - 1;
}

void move_pos_figure_right(GameInfoExtended_t *game_info) {
  clear_current_figure_from_game(game_info);
  game_info->figure_current->x_figure = game_info->figure_current->x_figure + 1;
}
/**
 * @brief Rotates the current figure by 90 degrees clockwise.
 *
 * This function rotates the current figure by 90 degrees clockwise and returns
 * the rotated figure as a 2D array.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 *
 * @return A 2D array representing the rotated figure.
 */
int **rotated_figure(GameInfoExtended_t *game_info) {
  int **temp_figure;
  temp_figure =
      alloc_temp_figure();  // Allocate memory for the temporary figure.

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // Perform the 90-degree clockwise rotation.
      temp_figure[j][4 - i - 1] = game_info->figure_current->figure[i][j];
    }
  }
  return temp_figure;  // Return the rotated figure.
}

/**
 * @brief Checks for intersection when rotating the current figure.
 *
 * This function checks for intersection when rotating the current figure by
 * evaluating whether the rotated figure intersects with the game field or
 * reaches its boundaries.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 * @param i The row index of the rotated figure.
 * @param j The column index of the rotated figure.
 * @param can_rotate The current state of rotation feasibility.
 *
 * @return 1 if the rotation is feasible, 0 if there is an intersection or
 * boundary reached.
 */
int check_intersection_when_rotate(GameInfoExtended_t *game_info, int i, int j,
                                   int can_rotate) {
  int y_pos_figure = i + game_info->figure_current
                             ->y_figure;  // Y-coordinate of the rotated figure.
  int x_pos_figure = j + game_info->figure_current
                             ->x_figure;  // X-coordinate of the rotated figure.

  // Check for intersection with existing bricks in the game field.
  if (game_info->field[i + y_pos_figure][j + x_pos_figure] == BRICK) {
    can_rotate = 0;  // Set rotation feasibility to false.
  } else if (x_pos_figure == GAME_FIELD_X_END || x_pos_figure == -1 ||
             y_pos_figure == GAME_FIELD_Y_END) {
    can_rotate = 0;  // Set rotation feasibility to false if the rotated figure
                     // reaches the game field boundaries.
  }

  return can_rotate;  // Return the updated state of rotation feasibility.
}
/**
 * @brief Checks if the current figure can be rotated without intersecting with
 * the game field or reaching its boundaries.
 *
 * This function checks if the current figure can be rotated without
 * intersecting with the game field or reaching its boundaries. It iterates
 * through the temporary rotated figure and checks for intersection or boundary
 * conditions using the check_intersection_when_rotate function.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 * @param temp_figure A pointer to the 2D array representing the rotated figure.
 * @param can_rotate The current state of rotation feasibility.
 *
 * @return 1 if the rotation is feasible, 0 if there is an intersection or
 * boundary reached.
 */
int can_rotate(GameInfoExtended_t *game_info, int **temp_figure,
               int can_rotate) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp_figure[i][j] == BRICK) {
        can_rotate =
            check_intersection_when_rotate(game_info, i, j, can_rotate);
      }
    }
  }

  return can_rotate;
}

/**
 * @brief Rotates the current figure by replacing it with the provided rotated
 * figure.
 *
 * This function rotates the current figure by replacing it with the provided
 * rotated figure. It clears the current figure from the game field and updates
 * it with the rotated figure.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 * @param temp_figure A pointer to the 2D array representing the rotated figure.
 */
void rotate_figure(GameInfoExtended_t *game_info, int **temp_figure) {
  clear_current_figure_from_game(
      game_info);  // Clear the current figure from the game field.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game_info->figure_current->figure[i][j] =
          temp_figure[i]
                     [j];  // Update the current figure with the rotated figure.
    }
  }
}

/**
 * @brief Copies the next figure to the current figure and resets its position.
 *
 * This function copies the next figure to the current figure and resets its
 * position to the initial center coordinates. It clears the current figure and
 * then copies the figure from the next drop to the current position. After the
 * copy operation, it resets the y and x coordinates of the current figure to
 * the initial center position.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 */
void copy_figure_next_to_current(GameInfoExtended_t *game_info) {
  clear_current_figure(
      game_info);  // Clear the current figure from the game field.

  // Copy the figure from the next drop to the current position.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game_info->figure_current->figure[i][j] =
          game_info->figure_next->figure[i][j];
    }
  }

  game_info->figure_current->y_figure =
      0;  // Reset the y-coordinate of the current figure.
  game_info->figure_current->x_figure =
      FIGURE_CENTR_X;  // Reset the x-coordinate of the current figure.
}
/**
 * @brief Checks if a new figure can be spawned in the game field without
 * collision.
 *
 * This function checks if a new figure can be spawned in the game field without
 * collision. It iterates through the cells of the next figure and checks if any
 * of its bricks collide with the existing bricks in the game field.
 *
 * @param game_info A pointer to the GameInfoExtended_t struct containing the
 * game state.
 *
 * @return 1 if the figure can be spawned without collision, 0 otherwise.
 */
int can_spawn_figure(GameInfoExtended_t *game_info) {
  int can_spawn = 1;  // Initialize the flag for figure spawn feasibility.

  int y_figure =
      game_info->figure_next->y_figure;  // Y-coordinate of the next figure.
  int x_figure =
      game_info->figure_next->x_figure;  // X-coordinate of the next figure.

  // Iterate through the cells of the next figure to check for collision with
  // existing bricks in the game field.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_info->figure_next->figure[i][j] == BRICK) {
        if (game_info->field[i + y_figure][j + x_figure] == BRICK) {
          can_spawn = 0;  // Set the flag to 0 if collision is detected.
        }
      }
    }
  }

  return can_spawn;  // Return the flag indicating whether the figure can be
                     // spawned without collision.
}