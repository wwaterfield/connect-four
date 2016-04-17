#ifndef CON4
#include "con4lib.h"
#include <math.h>

#define LOSE -1000
#define WIN 1000
#define DEPTH 3

// Checks the possible directions
const int DX_SIZE = 7;
const int DX[] = {-1, 0, 1, -1, -1, 0, 1};
const int DY[] = {-1, -1, -1, 0, 1, 1, 1};

#endif // CON4

typedef struct BestScore {
	int score;
	int row;
	int column;
	char ourpiece;
} BScore;

BScore g9_initstruct(const struct connect4* game);
BScore g9_checkscore(struct connect4* copied, BScore BestScore, int k);
int g9_findscore (struct connect4* copied, BScore BestScore);
int g9_test_depth(const struct connect4 *game);
int g9_move(const struct connect4 *game, int secondsLeft);
