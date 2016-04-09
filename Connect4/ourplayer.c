#include <stdio.h>
#include <stdlib.h>

#include "ourplayer.h"

<<<<<<< HEAD
int checkscore(struct connect4* copy, int row, int column, int score, char ourpiece, int k)
=======

int checkscore(struct connect4* copy, char team)
>>>>>>> 45dc9f2ba0eaf47b7fa5f623cf66f04be5627664
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

<<<<<<< HEAD
int findscore (struct connect4* copy, int column, int row, int score, char ourpiece)
{
    int total = -1000;
    return total;
=======
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

int findscore (struct connect4* copy, int row, int column int score, char ourpiece)
{

    int status = check_status(&copy);
    int i;
    char currentPiece = copy->whoseTurn;

    for (i = 0; i < DX_SIZE; i++)
    {
    	newRow = row + DX[i];
    	newCol = column + DY[i];

    	currentPos = copy->board[newRow][newCol];

    	score  = dxdyEval(copy, newRow, newCol, i, 1);
    }


    if (currentPiece = 'X' && (status == X_WINS || status == O_WINS))
    	score = 1000;
    if (currentPiece = 'O' && (status == O_WINS || status == X_WINS))
    	score = 1000;

    if (ourPiece == copy->whoseTurn)
    	return total;
    else
    	return = -total;
>>>>>>> 45dc9f2ba0eaf47b7fa5f623cf66f04be5627664
}


int hasThreeInARow(const struct connect4 *game)
{
	int DX[] = {0, -1, 0, 1};
	int DY[] = {-1, 0, 1, 0};



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
