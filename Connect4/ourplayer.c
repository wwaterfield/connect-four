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

int hasThreeInARow(const struct connect4 *game)
{
	int DX[] = {0, -1, 0, 1};
	int DY[] = {-1, 0, 1, 0};



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
