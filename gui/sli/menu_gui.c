#include "gui.h"

/*
  Function: print_menu

  Purpose: Display the game menu on the screen

  Parameters: None

  Returns: void
*/
void print_menu() {
  WINDOW *menu_win = newwin(GAME_WALL_Y_END, GAME_WALL_X_END * 2, 0,
                            0);  // Create a new window for the menu
  box(menu_win, 0, 0);           // Draw a box around the window
  refresh();                     // Refresh the standard screen
  wrefresh(menu_win);            // Refresh the menu window

  move(GAME_WALL_Y_END - 15,
       GAME_WALL_Y_END - 5);  // Move the cursor to the specified position
  printw("BRICKSGAME");       // Print the game title

  move(GAME_WALL_Y_END - 10,
       GAME_WALL_Y_END - 15);  // Move the cursor to the specified position
  printw("Press 'Enter' for start Tetris");  // Print the instruction for
                                             // starting Tetris

  move(GAME_WALL_Y_END - 3,
       GAME_WALL_Y_END - 15);  // Move the cursor to the specified position
  printw("Press 'Esc' for close the game");  // Print the instruction for
                                             // closing the game

  refresh();           // Refresh the standard screen
  wrefresh(menu_win);  // Refresh the menu window
}