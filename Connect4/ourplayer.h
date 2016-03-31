#ifndef CON4
#include "con4lib.h"
#endif // CON4

#define LOSE -1000;
#define WIN 1000;
#define COL_SIZE 7;
#define RUNS 4;

int checkscore(struct connect4* copy, char team);
int findscore (struct connect4* copy, int column, char ourpiece);
int test_depth(const struct connect4 *game);
int moving(const struct connect4 *game, int secondsLeft);
