#ifndef CON4
#include "con4lib.h"

#define LOSE -1000
#define WIN 1000
#define DEPTH 6
#endif // CON4



int checkscore(struct connect4* copy, int row, int column, int score, char ourpiece, int k);
int findscore (struct connect4* copy, int row, column, int score, char ourpiece);
int test_depth(const struct connect4 *game);
struct connect4 createStruct(const struct connect4* game);
int moving(const struct connect4 *game, int secondsLeft);
