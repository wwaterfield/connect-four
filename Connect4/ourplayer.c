#include <stdio.h>
#include <stdlib.h>

#include "ourplayer.h"


int checkscore(struct connect4* copy, BScore BestScore, int k)
{
    int column, comparedscore;
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
        if(BestScore.score <= tscore)
        {
            BestScore.column = column;
            BestScore.score = tscore;
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
        else if(highscore > comparedscore)
            highscore = comparedscore;


        copy->board[row][column] = '_';

    }
    //here we're going to return the top 3 moves.
    return yPos;
}

int dxdyEval(struct connect4 *copy, int row, int column, int i, int k)
{

	char currentPos = copy->board[row + DX[i]][column + DY[i]];

	if (column > NUM_COLS || row > NUM_ROWS || column < 0 || row < 0)
		return pow(5, k-1);

	if (k == 1 && currentPos != copy->whoseTurn && currentPos != '_')
		return 120;

	if (currentPos == copy->whoseTurn)
		return dxdyEval(copy, row+DX[i], column+DY[i], i, k+1);

	return pow(5, k);

}

int findscore (struct connect4* copy, BScore BestScore)
{

    int status = check_status(&copy);
    int i;
    char currentPiece = copy->whoseTurn;
    BestScore->score;

    for (i = 0; i < DX_SIZE; i++)
    {
    	newRow = BestScore.row + DX[i];
    	newCol = BestScore.column + DY[i];

    	currentPos = copy->board[newRow][newCol];

    	BestScore.score  = dxdyEval(copy, newRow, newCol, i, 1);
    }


    if (currentPiece = 'X' && (status == X_WINS || status == O_WINS))
    	BestScore.score = 1000;
    if (currentPiece = 'O' && (status == O_WINS || status == X_WINS))
    	BestScore.score = 1000;

    if (BestScore->ourpiece == copy->whoseTurn)
    	return BestScore.score;
    else
    	return -(BestScore.score);

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
