#include <stdio.h>
#include <stdlib.h>

#include "ourplayer.h"


int checkscore(struct connect4* copied, BScore BestScore, int k)
{
    int column, comparedscore, tscore;
    int turnour = k % 2;

    for(column=0;column<7;column++)
    {
        //get the row for the column
        int row = get_row(copied, column);
        //if row isn't valid, move on
        if(not_valid(copied,column) != 0)
            continue;
        //place piece, find score, if highscore then save it
        copied->board[row][column] = copied->whoseTurn;
        tscore = findscore(copied, BestScore);
        printf("score: %d", tscore);
        if(BestScore.score <= tscore)
        {
            BestScore.column = column;
            BestScore.score = tscore;
        }
        if(k != DEPTH)
        {
            if(turnour)
                copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';
            checkscore(copied, BestScore, k+1);
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';
        }
        int comparedscore = findscore(copied, BestScore);
        //our turn
        if(turnour)
        {
            if(BestScore.score < comparedscore)
                BestScore.score = comparedscore;
        }
        else if(BestScore.score > comparedscore)
            BestScore.score = comparedscore;

        printf(" BestScore: %d\n", BestScore.score);
        copied->board[row][column] = '_';

    }
    return BestScore.column;
}

int dxdyEval(struct connect4 *copied, int row, int column, int i, int k)
{

	char currentPos = copied->board[row + DX[i]][column + DY[i]];

	if (column > NUM_COLS || row > NUM_ROWS || column < 0 || row < 0)
		return pow(5, k-1);

	if (k == 1 && currentPos != copied->whoseTurn && currentPos != '_')
		return 120;

	if (currentPos == copied->whoseTurn)
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1);

	return pow(5, k);

}

int findscore (struct connect4* copied, BScore BestScore)
{

    int status = check_status(copied);
    int i;
    char currentPiece = copied->whoseTurn;

    for (i = 0; i < DX_SIZE; i++)
    {
    	int newRow = BestScore.row + DX[i];
    	int newCol = BestScore.column + DY[i];

    	int currentPos = copied->board[newRow][newCol];

    	BestScore.score  = dxdyEval(copied, newRow, newCol, i, 1);
    }


    if (currentPiece == 'X' && (status == X_WINS || status == O_WINS))
    	BestScore.score = 1000;
    if (currentPiece == 'O' && (status == O_WINS || status == X_WINS))
    	BestScore.score = 1000;



    print_board(copied);

    if (BestScore.ourpiece == copied->whoseTurn)
    	return BestScore.score;
    else
    	return (BestScore.score);

}

int test_depth(const struct connect4 *game)
{
    int bestmove;
    struct connect4* copied = copy(game);

    //get the best move of the 7
    //check for integer best move?
    BScore BestScore;
    BestScore.row = 0;
    BestScore.column = 0;
    BestScore.score = 0;
    BestScore.ourpiece = game->whoseTurn;

        bestmove = checkscore(copied, BestScore, 0);

    return bestmove;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    int bestMove;
    bestMove = test_depth(game);
    return bestMove;
}
