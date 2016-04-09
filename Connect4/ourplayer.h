#ifndef CON4
#include "con4lib.h"
#include <math.>

#define LOSE -1000
#define WIN 1000
<<<<<<< HEAD
#define DEPTH 6
=======
#define DEPTH 4
#define TOP_MOVES 3

// Checks the five possible directions
const int DX_SIZE = 7;
const int DX[] = {-1, 0, 1, 1, 1, 0, -1};
const int DY[] = {-1, -1, -1, 0, 1, 1, 1};

>>>>>>> 45dc9f2ba0eaf47b7fa5f623cf66f04be5627664
#endif // CON4


typedef struct BestScore {
	int score;
	int position;
};

int checkscore(struct connect4* copy, int row, int column, int score, char ourpiece, int k);
int findscore (struct connect4* copy, int row, column, int score, char ourpiece);
int test_depth(const struct connect4 *game);
struct connect4 createStruct(const struct connect4* game);
int moving(const struct connect4 *game, int secondsLeft);
