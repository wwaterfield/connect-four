#ifndef CON4
#include "con4lib.h"

#define LOSE -1000
#define WIN 1000
#define DEPTH 4
#define TOP_MOVES 3


#endif // CON4

typedef struct Top3
{
    int move1;
    int move2;
    int move3;
} Top3;


int checkscore(struct connect4* copy, char team);
int findscore (struct connect4* copy, int column, int row);
int test_depth(const struct connect4 *game);
struct connect4 createStruct(const struct connect4* game);
int moving(const struct connect4 *game, int secondsLeft);
