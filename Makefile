cc = gcc
CFLAGS = -lcurses
BACK_DIR = brick_game/tetris/
FRONT_DIR = cli/gui/
BACK_SRC = $(wildcard $(BACK_DIR)*.c)
FRONT_SRC = $(wildcard $(FRONT_DIR)*.c)

all:
	$(cc) $(CFLAGS) $(BACK_SRC) $(FRONT_SRC) -o tetris