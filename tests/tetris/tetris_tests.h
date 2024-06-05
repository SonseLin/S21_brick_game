#ifndef SRC_TESTS_TETRIS
#define SRC_TESTS_TETRIS

#include <check.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../brickgame/tetris/bricks_logic.h"
#include "../../brickgame/tetris/figure_samples/figure_samples.h"
#include "../../gui/sli/gui.h"

#endif  // SRC_TESTS_TETRIS

Suite *suite_getGameInfo(void);

void run_tests(void);
void run_testcase(Suite *testcase, int counter_testcase);

void get_usr_input_test();

void gameloopForTest();
Suite *suite_doloeb(void);