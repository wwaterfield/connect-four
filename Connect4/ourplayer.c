#include <stdio.h>
#include <stdlib.h>

#include "con4lib.h"

#define LOSE -1000;
#define WIN 1000;
#define COL_SIZE 7;

int checkscore(char board[6][7], char team)
{
    int us, i, j;

    //this is just knowing what player we are???
    if(team == PLAYERONE)
        us = 1;
    else us = 0;
    //I have no way to decide what player otherwise
    int tscore = -1000;
    int highscore;
    int yPos;
    for(j=0;j<7;j++)
    {
        tscore = score(board, j);

        if(total <= tscore)
        {
            yPos = j;
            highscore = tscore;
        }


        }
    }
}

int score (char board[6][7], posInfo temp)
{
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

    posInfo scoreInfo;
    char boardCopy[NUM_ROWS][NUM_COLS];

    // Get a copy of the  current board.
    for (i = 0; i < NUM_ROWS; i++)
    {
        for (j = 0; j < NUM_COLS; j++)
        {
            boardCopy[i][j] = game->board[i][j];
        }
    }

    scoreInfo = checkscore(boardCopy[][7], team);

    move = scoreInfo.yPos;
    return move;
}

posInfo makeNode(int xPos, int yPos)
{
    posInfo temp;
    temp.xPos = xPos;
    temp.yPos = yPos;
    return temp;
}
