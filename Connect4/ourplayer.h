#ifndef CON4
#include "con4lib.h"
#include <math.h>

#define LOSE -1000
#define WIN 1000
#define DEPTH 6

// Checks the five possible directions
const int DX_SIZE = 7;
const int DX[] = {-1, 0, 1, 1, 1, 0, -1};
const int DY[] = {-1, -1, -1, 0, 1, 1, 1};

#endif // CON4

typedef struct BestScore {
	int score;
	int row;
	int column;
	char ourpiece;
} BScore;

int checkscore(struct connect4* copy, BScore BestScore, int k);
int findscore (struct connect4* copy, BScore BestScore);
int test_depth(const struct connect4 *game);
struct connect4 createStruct(const struct connect4* game);
int moving(const struct connect4 *game, int secondsLeft);
