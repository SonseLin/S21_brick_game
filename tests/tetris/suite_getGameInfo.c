#include "tetris_tests.h"

START_TEST(test_based) {
  GameInfoExtended_t *game_info = malloc(sizeof(GameInfoExtended_t));

  int error = init_game_info(game_info);
  ck_assert_int_eq(error, 0);

  updateCurrentState();

  free_game_info(game_info);
  free_api_game_info();
}
END_TEST

Suite *suite_getGameInfo(void) {
  Suite *s = suite_create("suite_moves");
  TCase *tc = tcase_create("case_moves");

  tcase_add_test(tc, test_based);

  suite_add_tcase(s, tc);

  return s;
}