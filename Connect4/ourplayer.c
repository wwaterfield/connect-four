#include <stdio.h>
#include <stdlib.h>

#include "ourplayer.h"

int checkscore(struct connect4* copy, int row, int column, int score, char ourpiece, int k)
{
    int yPos, column;
    int highscore, comparedscore;
    int turnour = k % 2;

    for(column=0;column<7;column++)
    {
        //get the row for the column
        int row = get_row(copy, column);
        //if row isn't valid, move on
        if(not_valid(copy,column) == 0)
            continue;
        //place piece, find score, if highscore then save it
        copy->board[row][column] = copy->whoseTurn;
        tscore = findscore(copy, row, column);
        if(highscore <= tscore)
        {
            yPos = column;
            highscore = tscore;
        }
        if(k != DEPTH)
            checkscore(copy, k+1, column, row);
        int comparedscore = findscore(copy);
        //our turn
        if(turnour)
        {
            if(highscore < comparedscore)
                highscore = comparedscore;
        }
        else if(highscre > comparedscore)
            highscore = comparedscore;


        copy->board[row][column] = '_';

    }
    //here we're going to return the top 3 moves.
    return yPos;
}

int findscore (struct connect4* copy, int column, int row, int score, char ourpiece)
{
    int total = -1000;
    return total;
}


int test_depth(const struct connect4 *game)
{
    int i;
    int bestmove;
    struct connect4 copy = copy(game);

    //get the best move of the 7
    //check for integer best move?
        bestmove = checkscore(&copy, 0);

    return bestmove;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    int bestMove;
    bestMove = test_depth(game);
    return bestMove;
}
