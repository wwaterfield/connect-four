#include <stdio.h>
#include <stdlib.h>


int move(const struct connect4 *game)
{
    int i;
    for(i=0;i<NUM_COLS;i++)
    {
        if(game->board[NUM_ROWS-1][i] == '_')
            return i;
    }
}
