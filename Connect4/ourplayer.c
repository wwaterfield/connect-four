#include <stdio.h>
#include <stdlib.h>

#include "ourplayer.h"

int checkscore(struct connect4* copy, char team)
{
    //base case

    int tscore = -1000;
    int highscore = -1000;
    int yPos;
    tscore = findscore(copy, column, row);
    if(highscore <= tscore && row < NUM_ROWS)
        {
            yPos = column;
            highscore = tscore;
        }


    int column;
    for(column=0;column<7;column++)
    {
        //get the row for the column
        int row = get_row(copy, column);
        //if row isn't valid, move on
        if(not_valid(copy,column) == 0)
            continue;
        //if the score is higher, save that position

    }
    //here we're going to return the top 3 moves.
    return yPos;
}

int findscore (struct connect4* copy, int column, int row)
{
    int total = -1000;
    copy->board[row][column] = copy->whoseTurn;

    copy->board[row][column] = '_';
    return total;
}

struct connect4 createStruct(const struct connect4* game)
{
    int i,j;
    struct connect4 copy;
    copy.board[NUM_ROWS][NUM_COLS];
    // Get a copy of the  current board.
    for (i = 0; i < NUM_ROWS; i++)
    {
        for (j = 0; j < NUM_COLS; j++)
        {
            copy.board[i][j] = game->board[i][j];
        }
    }
    copy.whoseTurn = game->whoseTurn;
    return copy;
}

int test_depth(const struct connect4 *game)
{
    int i;
    int bestmove;
    struct connect4 copy = createStruct(game);

    //get the best move of the 7
    for(i=0;i<RUNS;i++)
        bestmove = checkscore(&copy, copy.whoseTurn);

    return bestmove;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    int bestMove;
    bestMove = test_depth(game);
    return bestMove;
}
