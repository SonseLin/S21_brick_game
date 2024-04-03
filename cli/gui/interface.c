#include "interface.h"

void shizophreniya() {
  start_color();
  short colors[7] = {COLOR_MAGENTA, COLOR_RED,  COLOR_GREEN, COLOR_BLUE,
                     COLOR_YELLOW,  COLOR_CYAN, COLOR_WHITE};
  for (int i = 0; i < 7; i++) {
    init_pair(i + 1, colors[i], i + 1);
  }
}

UserAction_t get_user_input() {
  UserAction_t action;
  switch (getch()) {
    case '\n':
      action = Start;
      break;
    case 'p':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Up;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case ' ':
      action = Action;
      break;
    default:
      action = -2;
      break;
  }

  return action;
}

void print_game(GameInfoExtended_t* gie) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      attron(COLOR_PAIR(7));
      for (int k = O_X_ALIGNMENT; k < O_X_ALIGNMENT + X_WIDTH; k++) {
        mvaddch(i + O_Y_ALIGNMENT, j * O_X_ALIGNMENT + k, ' ');
      }
      attroff(COLOR_PAIR(6));
    }
  }
}

void print_border() {
  for (int i = 0; i < O_Y_ALIGNMENT; i++) {
    for (int j = 0; j < WIDTH * 8; j++) {
      attron(COLOR_PAIR(2));
      mvaddch(i, j, ' ');
      mvaddch(HEIGHT + O_Y_ALIGNMENT, j, ' ');
      attron(COLOR_PAIR(6));
    }
  }
  for (int j = 0; j < O_X_ALIGNMENT; j++) {
    for (int i = O_Y_ALIGNMENT; i < HEIGHT + O_Y_ALIGNMENT * 2; i++) {
      attron(COLOR_PAIR(2));
      mvaddch(i, j, ' ');
      attron(COLOR_PAIR(6));
    }
  }
  for (int j = WIDTH * 8; j < WIDTH * 8 + O_X_ALIGNMENT; j++) {
    for (int i = 0; i < HEIGHT + O_Y_ALIGNMENT * 2; i++) {
      attron(COLOR_PAIR(2));
      mvaddch(i, j, ' ');
      attron(COLOR_PAIR(6));
    }
  }
}

// FINISH HIM
void print_current_figure(FigureInfo_t* fi) {
  for (int i = fi->y; fi->y + 4; i++) {
    for (int j = fi->x; fi->x + 4; j++) {
      attron(COLOR_PAIR(7));
      for (int k = O_X_ALIGNMENT; k < O_X_ALIGNMENT + X_WIDTH; k++) {
        mvaddch(i, j * O_X_ALIGNMENT + k, ' ');
      }
      attroff(COLOR_PAIR(6));
    }
  }
}

void print_next_figure(FigureInfo_t* fi) {
  for (int i = HEIGHT / 2 - 5; i < HEIGHT / 2 - 1; i++) {
    if (i == HEIGHT / 2 - 5) {
      char next_figure[11] = {'n', 'e', 'x', 't', ' ', 'f',
                              'i', 'g', 'u', 'r', 'e'};
      for (int k = 0; k < 11; k++) {
        mvaddch(i - 1, WIDTH * 4 + k + 3, next_figure[k]);
      }
    }
    for (int j = WIDTH * 4; j < WIDTH * 4 + 4; j++) {
      int fx = j - WIDTH * 4;
      int fy = i - HEIGHT / 2 - 5;
      attron(COLOR_PAIR(2));
      for (int k = O_X_ALIGNMENT; k < O_X_ALIGNMENT + X_WIDTH; k++) {
        mvaddch(i + O_Y_ALIGNMENT, j + O_X_ALIGNMENT + k, ' ');
      }
      attron(COLOR_PAIR(6));
    }
  }
}