#include "../bricks_logic.h"

/**
 * @brief Sets the figure_next to a line shape.
 *
 * This function sets the figure_next to a line shape by setting the second row
 * of each of the four cells to BRICK.
 *
 * @param[in, out] game_info A pointer to the GameInfoExtended_t structure that
 * contains the game information.
 */
void getFigureLine(GameInfoExtended_t *game_info) {
  for (int i = 0; i < 4; i++) {
    game_info->figure_next->figure[i][1] = BRICK;
  }
}

/**
 * @brief Sets the figure_next to a box shape.
 *
 * This function sets the figure_next to a box shape by setting all the cells
 * within the box to BRICK. The box is defined as a 2x2 square in the 4x4 grid.
 *
 * @param[in, out] game_info A pointer to the GameInfoExtended_t structure that
 * contains the game information.
 */
void getFigureBox(GameInfoExtended_t *game_info) {
  /**
   * @brief Iterates over the 2x2 box within the 4x4 grid.
   *
   * This nested loop iterates over the 2x2 box within the 4x4 grid, setting
   * each cell to BRICK.
   *
   * @param[in] i The row index, starting from 1 (since 0 is the first row).
   * @param[in] j The column index, starting from 1 (since 0 is the first
   * column).
   */
  for (int i = 1; i < 3; i++) {    // Iterates over the rows within the box
    for (int j = 1; j < 3; j++) {  // Iterates over the columns within the box
      game_info->figure_next->figure[i][j] = BRICK;  // Sets the cell to BRICK
    }
  }
}

/**
 * @brief Sets the figure_next to a left angle shape.
 *
 * This function sets the figure_next to a left angle shape by setting the
 * top-left corner and the bottom-right corner to BRICK. The remaining cells are
 * left empty.
 *
 * @param[in, out] game_info A pointer to the GameInfoExtended_t structure that
 * contains the game information.
 */
void getFigureLeftAngle(GameInfoExtended_t *game_info) {
  /**
   * @brief Sets the top-left corner of the left angle shape.
   *
   * This nested function sets the top-left corner of the left angle shape to
   * BRICK.
   *
   * @param[in, out] game_info A pointer to the GameInfoExtended_t structure
   * that contains the game information.
   */
  game_info->figure_next->figure[1][1] = BRICK;

  /**
   * @brief Sets the bottom-right corner of the left angle shape.
   *
   * This nested function sets the bottom-right corner of the left angle shape
   * to BRICK.
   *
   * @param[in, out] game_info A pointer to the GameInfoExtended_t structure
   * that contains the game information.
   */
  for (int i = 1; i < 4; i++) {
    game_info->figure_next->figure[2][i] = BRICK;
  }
}

/**
 * @brief Sets the figure_next to a triangle shape.
 *
 * This function sets the figure_next to a triangle shape by setting the
 * top-middle cell and the bottom two cells to BRICK.
 *
 * @param[in, out] game_info A pointer to the GameInfoExtended_t structure that
 * contains the game information.
 */
void getFigureTriangle(GameInfoExtended_t *game_info) {
  /**
   * @brief Sets the top-middle cell of the triangle shape.
   *
   * This nested function sets the top-middle cell of the triangle shape to
   * BRICK.
   *
   * @param[in, out] game_info A pointer to the GameInfoExtended_t structure
   * that contains the game information.
   */
  game_info->figure_next->figure[1][2] = BRICK;

  /**
   * @brief Sets the bottom two cells of the triangle shape.
   *
   * This nested function sets the bottom two cells of the triangle shape to
   * BRICK.
   *
   * @param[in, out] game_info A pointer to the GameInfoExtended_t structure
   * that contains the game information.
   */
  for (int i = 1; i < 4; i++) {
    game_info->figure_next->figure[2][i] = BRICK;
  }
}

void getFigureSnakeRight(GameInfoExtended_t *game_info) {
  game_info->figure_next->figure[2][1] = BRICK;
  game_info->figure_next->figure[2][2] = BRICK;
  game_info->figure_next->figure[1][2] = BRICK;
  game_info->figure_next->figure[1][3] = BRICK;
}

void getFigureSnakeLeft(GameInfoExtended_t *game_info) {
  game_info->figure_next->figure[1][1] = BRICK;
  game_info->figure_next->figure[1][2] = BRICK;
  game_info->figure_next->figure[2][2] = BRICK;
  game_info->figure_next->figure[2][3] = BRICK;
}
