#include <stdio.h>
#include <stdlib.h>

#include "con4lib.h"
#define LOSE -1000;
#define WIN 1000;

typedef struct posInfo {
    int xPos;
    int yPos;
    int score;
} posInfo;

int score (char board[6][7], char team)
{
    int us;
    if(team == PLAYERONE)
        us = 1;
    else us = 0;

    total = 0;

    return 0;
}

int chk_status(char board[][NUM_COLS])
{
    return 0;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    int i;

    char boardCopy[NUM_ROWS][NUM_COLS];

    // Get a copy of the  current board.
    for (i = 0; i < NUM_ROWS; i++)
    {
        for (j = 0; j < NUM_COLS; j++)
        {
            boardCopy[i][j] = game->board[i][j];
        }
    }
    return i;
}

posInfo makeInfoNode(int xPos, int yPos, int score)
{

}

