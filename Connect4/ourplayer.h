#ifndef CON4
#include "con4lib.h"
#endif // CON4

int checkscore(const struct connect4* game);
int score (char board[6][7], int column, char team);
int test_depth(const struct connect4 *game);
int moving(const struct connect4 *game, int secondsLeft);
