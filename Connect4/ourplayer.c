#include <stdio.h>
#include <stdlib.h>

#include "con4lib.h"
#define LOSE -1000;
#define WIN 1000;


int score (char board[6][7], char team)
{
    int us, i, j;
    //this is just knowing what player we are???
    if(team == PLAYERONE)
        us = 1;
    else us = 0;
    //end player

    total = 0;

    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {

        }
    }

    return 0;
}

int chk_status(char board[][NUM_COLS])
{
    return 0;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    //here we have to make sure that if score == LOSE Then we MUST place a piece there. Same for win.
    int i = 0;
    for(i=0;i<NUM_COLS;i++)
    {
        if(game->board[NUM_ROWS-1][i] == '_')
            return i;
    }

    return i;
}
