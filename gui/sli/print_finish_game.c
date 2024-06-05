#include "gui.h"
#include "string.h"

/**
 * Prints the given text to the center of the screen at the specified y
 * position.
 *
 * @param text The text to be printed to the center of the screen.
 * @param y_pos The y position at which the text will be printed.
 */
void print_text_to_centr(char *text, int y_pos) {
  int text_length = strlen(text);  // Calculate the length of the text
  int start_x = (GAME_WALL_Y_END * 2 + 5 - text_length) /
                2;  // Calculate the starting x position for centering
  mvprintw(y_pos, start_x, "%s",
           text);  // Print the text at the calculated position
}

/**
 * Prints the close game message with the player's score and instructions to
 * close the game.
 *
 * @param game_info The structure containing game information including the
 * player's score.
 */
void print_close_game(GameInfo_t game_info) {
  WINDOW *fail_win =
      newwin(GAME_WALL_Y_END, GAME_WALL_X_END * 2 + 5, 0,
             0);  // Create a new window for displaying the close game message
  box(fail_win, 0, 0);  // Draw a box around the window
  refresh();            // Refresh the standard screen

  char text[30];
  sprintf(text, "Your score %d",
          game_info.score);  // Format the player's score into a text message
  print_text_to_centr(
      text, 10);  // Print the player's score to the center of the screen

  print_text_to_centr(
      "Press 'Enter' key for close the game",
      15);  // Print instructions to close the game to the center of the screen

  wrefresh(fail_win);  // Refresh the close game window
  refresh();           // Refresh the standard screen
}