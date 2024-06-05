#include "../../../gui/sli/gui.h"
#include "../bricks_logic.h"

int alloc_game_info(GameInfoExtended_t *game_info) {
  int alloc_error = 0;

  alloc_error = allocate_memory_fields(game_info);
  if (!alloc_error) {
    alloc_error = allocate_memory_figure(game_info);
    if (alloc_error) {
      free_fields(game_info);
      alloc_error = 1;
    }
  } else {
    alloc_error = 1;
  }

  return alloc_error;
}

int allocate_memory_fields(GameInfoExtended_t *game_info) {
  int allocate_error = 0;

  game_info->next = (int **)malloc(GAME_FIELD_Y_ALLOC * sizeof(int *));
  game_info->field = (int **)malloc(GAME_FIELD_Y_ALLOC * sizeof(int *));
  if (game_info->next != NULL && game_info->field != NULL) {
    for (int i = 0; i < GAME_FIELD_Y_ALLOC; i++) {
      game_info->field[i] = (int *)malloc(GAME_FIELD_X_ALLOC * sizeof(int));
      game_info->next[i] = (int *)malloc(GAME_FIELD_X_ALLOC * sizeof(int));
      if (game_info->next[i] == NULL || game_info->field[i] == NULL) {
        allocate_error = 1;
        for (int j = 0; j <= i; j++) {
          if (game_info->field[j] != NULL) {
            free(game_info->field[j]);
          }
          if (game_info->next[j] != NULL) {
            free(game_info->next[j]);
          }
        }
        free(game_info->next);
        free(game_info->field);
        game_info->next = NULL;
        game_info->field = NULL;
        break;
      }
    }
  } else {
    allocate_error = 1;
  }

  return allocate_error;
}

void free_game_info(GameInfoExtended_t *game_info) {
  free_fields(game_info);
  free_figure(game_info);
  game_info = NULL;
}

void free_fields(GameInfoExtended_t *game_info) {
  if (game_info != NULL && game_info->field != NULL) {
    for (int i = 0; i < GAME_FIELD_Y_ALLOC; i++) {
      free(game_info->field[i]);
      free(game_info->next[i]);
    }
    free(game_info->field);
    free(game_info->next);
  }
}

int allocate_memory_figure(GameInfoExtended_t *game_info) {
  int error = 0;
  game_info->figure_current = malloc(sizeof(Figure_t));
  game_info->figure_next = malloc(sizeof(Figure_t));
  if (game_info->figure_current == NULL && game_info->next == NULL) {
    error = 1;
    return error;
  }

  game_info->figure_current->figure = malloc(4 * sizeof(int *));
  game_info->figure_next->figure = malloc(4 * sizeof(int *));
  if (game_info->figure_current->figure == NULL ||
      game_info->figure_next->figure == NULL) {
    error = 1;
    free(game_info->figure_current);
    if (game_info->figure_current->figure != NULL)
      free(game_info->figure_current->figure);
    if (game_info->figure_next->figure != NULL)
      free(game_info->figure_next->figure);
    return error;
  }

  for (int i = 0; i < 4; i++) {
    game_info->figure_current->figure[i] = malloc(4 * sizeof(int));
    game_info->figure_next->figure[i] = malloc(4 * sizeof(int));
    if (game_info->figure_current->figure[i] == NULL ||
        game_info->figure_next->figure[i] == NULL) {
      error = 1;
      for (int j = 0; j <= i; j++) {
        if (game_info->figure_current->figure[j] != NULL)
          free(game_info->figure_current->figure[j]);
        if (game_info->figure_next->figure[j] != NULL)
          free(game_info->figure_next->figure[j]);
      }
      free(game_info->figure_current->figure);
      free(game_info->figure_next->figure);
      free(game_info->figure_current);
      return error;
    }
  }

  return error;
}

void free_figure(GameInfoExtended_t *game_info) {
  if (game_info != NULL) {
    if (game_info->figure_current != NULL) {
      if (game_info->figure_current->figure != NULL) {
        for (int i = 0; i < 4; i++) {
          free(game_info->figure_current->figure[i]);
        }
        free(game_info->figure_current->figure);
      }
      free(game_info->figure_current);
    }
    if (game_info->figure_next != NULL) {
      if (game_info->figure_next->figure != NULL) {
        for (int i = 0; i < 4; i++) {
          free(game_info->figure_next->figure[i]);
        }
        free(game_info->figure_next->figure);
      }
      free(game_info->figure_next);
    }
  }
}

int **alloc_temp_figure() {
  int size = 4;
  int **figure = (int **)malloc(size * sizeof(int *));

  if (figure == NULL) return NULL;

  for (int i = 0; i < size; i++) {
    figure[i] = (int *)malloc(size * sizeof(int));

    if (figure[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(figure[j]);
      }
      free(figure);
      return NULL;
    }

    for (int j = 0; j < size; j++) {
      figure[i][j] = 0;
    }
  }

  return figure;
}

void free_temp_figure(int **figure, int size) {
  if (figure != NULL) {
    for (int i = 0; i < size; i++) {
      free(figure[i]);
    }
    free(figure);
  }
}
