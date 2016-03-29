#include <stdio.h>
#include <stdlib.h>

#include "con4lib.h"

#define LOSE -1000;
#define WIN 1000;
#define COL_SIZE 7;

typedef struct posInfo {
    int xPos;
    int yPos;
    int score;
} posInfo;

posInfo* checkscore(char board[6][7], char team)
{
    int us, i, j;
    posInfo BestMove;
    posInfo curMove;
    //this is just knowing what player we are???
    if(team == PLAYERONE)
        us = 1;
    else us = 0;
    //I have no way to decide what player otherwise

    int tscore = -1000;
    BestMove = makeNode(0, 0);
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            curMove = makeNode(i, j)
            curMove = score(board, curMove);

            if(BestMove.score <= tscore)
            {
                BestMove.xPos = i;
                BestMove.yPos = j;
                BestMove.score = tscore;
            }


        }
    }
}

int score (char board[6][7], char team, connect4 *game)
{
    int total;
    int boardStatus;

    boardStatus


    // If all four are in a rows


    return total;
}

int chk_status(char board[][NUM_COLS])
{
    return 0;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    //here we have to make sure that if score == LOSE Then we MUST place a piece there. Same for win.
    int i = 0;

    int bestMove;
    char boardCopy[NUM_ROWS][NUM_COLS];

    // Get a copy of the  current board.
    for (i = 0; i < NUM_ROWS; i++)
    {
        for (j = 0; j < NUM_COLS; j++)
        {
            boardCopy[i][j] = game->board[i][j];
        }
    }

    bestMove = checkscore(boardCopy[][7], team);

    return bestMove;
}
