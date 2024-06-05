#include "../../brickgame/tetris/bricks_logic.h"
#include "gui.h"

/**
 * @brief Frontend function responsible for displaying the game interface based
 * on the current state of the game.
 *
 * This function retrieves the current automaton state and game information, and
 * then displays the appropriate interface based on the state of the game.
 */
void frontend() {
  Automaton_t *automaton =
      getAutomaton();  // Pointer to the current automaton state
  GameInfo_t api_game_info =
      updateCurrentState();  // Game information retrieved from the API

  if (*automaton == Start_automaton)
    print_menu();  // Display the game menu
  else if (api_game_info.pause == 1)
    print_pause();  // Display the pause screen
  else if (*automaton == Moving || *automaton == Shifting ||
           *automaton == Collided)
    print_game(api_game_info);  // Display the game interface with the provided
                                // game information
  else if (*automaton == GameOver)
    print_close_game(api_game_info);  // Display the game over screen with the
                                      // provided game information
}