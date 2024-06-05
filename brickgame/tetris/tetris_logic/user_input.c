#include "../bricks_logic.h"

/**
 * @brief Get the user action based on the input key.
 *
 * This function reads the input key from the user and maps it to a
 * corresponding action.
 *
 * @return The user action based on the input key:
 *         - Start if the input key is KEY_ENTERR (KEY_ENTER FROM ncurses.h
 * doesn't work)
 *         - Pause if the input key is KEY_PAUSE ('P' on keyboard)
 *         - Terminate if the input key is KEY_ESC
 *         - Left if the input key is KEY_LEFT
 *         - Right if the input key is KEY_RIGHT
 *         - Up if the input key is KEY_UP
 *         - Down if the input key is KEY_DOWN
 *         - Action if the input key is KEY_SPACE
 *         - Skip if the input key does not match any predefined key
 */
int get_user_action() {
  int input_key = getch();

  switch (input_key) {
    case KEY_ENTERR:
      return Start;
    case KEY_PAUSE:
      return Pause;
    case KEY_ESC:
      return Terminate;
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case KEY_UP:
      return Up;
    case KEY_DOWN:
      return Down;
    case KEY_SPACE:
      return Action;
    default:
      return Skip;
  }
}