#include "../bricks_logic.h"

/**
 * @brief Updates the current state of the game.
 *
 * This function retrieves the current game state from the API and returns it.
 *
 * @return The current game state.
 */
GameInfo_t updateCurrentState() {
  GameInfo_t *api_game_info = getGameInfo();
  return *api_game_info;
}

/**
 * @brief Retrieves the current game state from the API.
 *
 * This function initializes the game state if it has not been initialized yet,
 * and then returns a pointer to the current game state.
 *
 * @return A pointer to the current game state.
 */
GameInfo_t *getGameInfo() {
  static GameInfo_t api; /**< @brief Static variable to store the game state. */
  static int is_inited = 0; /**< @brief Static variable to track if the game
                               state has been initialized. */

  if (!is_inited) { /** @brief Check if the game state has been initialized. */
    alloc_api_game_info(
        &api); /** @brief Allocates memory for the game state. */
    init_api_game_info(
        &api); /**< @brief Initializes the game state with default values. */
    is_inited = 1; /**< @brief Set the initialization flag to true. */
  }

  return &api; /**< @brief Returns a pointer to the current game state. */
}

/**
 * @brief Copies the extended game info to the API game info.
 *
 * This function copies the extended game info to the API game info.
 *
 * @param[in] game_info The extended game info to copy.
 */
void copy_game_info_extended_to_api(GameInfoExtended_t *game_info) {
  GameInfo_t *api_game_info = getGameInfo();

  for (int i = 0; i < GAME_FIELD_Y_END; i++) {
    for (int j = 0; j < GAME_FIELD_X_END; j++) {
      api_game_info->next[i][j] = game_info->next[i][j];
    }
  }

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      api_game_info->field[i][j] = game_info->figure_next->figure[i][j];

  api_game_info->high_score = game_info->high_score;
  api_game_info->level = game_info->level;
  api_game_info->pause = game_info->pause;
  api_game_info->score = game_info->score;
  api_game_info->speed = game_info->speed / 10;
}

/**
 * @brief Allocates memory for the API game info.
 *
 * This function allocates memory for the API game info, including the field and
 * next arrays.
 *
 * @param[in] api A pointer to the API game info structure.
 *
 * @return 0 if successful, 1 if memory allocation fails.
 */

int alloc_api_game_info(GameInfo_t *api) {
  api->field = malloc(GAME_FIELD_Y_END * sizeof(int *));
  api->next = malloc(GAME_FIELD_Y_END * sizeof(int *));
  if (api->field == NULL || api->next == NULL) {
    free(api->field);
    free(api->next);
    return 1;
  }

  for (int i = 0; i < GAME_FIELD_Y_END; i++) {
    api->field[i] = malloc(GAME_FIELD_X_END * sizeof(int));
    api->next[i] = malloc(GAME_FIELD_X_END * sizeof(int));
    if (api->field[i] == NULL || api->next[i] == NULL) {
      for (int j = 0; j <= i; j++) {
        free(api->field[j]);
        free(api->next[j]);
      }
      free(api->field);
      free(api->next);
      return 1;
    }
  }

  return 0;
}
/**
 * @brief Frees the memory allocated for the API game info.
 *
 * This function frees the memory allocated for the API game info, including the
 * field and next arrays.
 *
 * @note This function should be called when the API game info is no longer
 * needed to prevent memory leaks.
 */
void free_api_game_info() {
  GameInfo_t *api_game_info = getGameInfo();

  int is_null = 0;
  if (api_game_info == NULL) is_null = 1;

  if (!is_null) {
    if (api_game_info->field != NULL) {
      for (int i = 0; i < GAME_FIELD_Y_END; i++) {
        if (api_game_info->field[i] != NULL) {
          free(api_game_info->field[i]);
        }
      }
      free(api_game_info->field);
      api_game_info->field = NULL;
    }

    if (api_game_info->next != NULL) {
      for (int i = 0; i < GAME_FIELD_Y_END; i++) {
        if (api_game_info->next[i] != NULL) {
          free(api_game_info->next[i]);
        }
      }
      free(api_game_info->next);
      api_game_info->next = NULL;
    }
  }
}
/**
 * @brief Initializes the API game info with default values.
 *
 * This function initializes the API game info with default values.
 *
 * @param[in] api A pointer to the API game info structure.
 */
void init_api_game_info(GameInfo_t *api) {
  for (int i = 0; i < GAME_FIELD_Y_END; i++) {
    for (int j = 0; j < GAME_FIELD_X_END; j++) {
      api->field[i][j] = EMPTY;
      api->next[i][j] = EMPTY;
    }
  }

  api->high_score = 0;
  api->level = 0;
  api->pause = 0;
  api->score = 0;
  api->speed = 0;
}
/**
 * @brief Retrieves the current automaton state from the API.
 *
 * This function initializes the automaton state if it has not been initialized
 * yet, and then returns a pointer to the current automaton state.
 *
 * @return A pointer to the current automaton state.
 */
Automaton_t *getAutomaton() {
  static Automaton_t automaton;
  static int is_inited = 0;

  if (is_inited == 0) {
    automaton = Start_automaton;
    is_inited = 1;
  }
  return &automaton;
}