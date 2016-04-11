#include <stdio.h>
#include <stdlib.h>

#include "ourplayer.h"


BScore checkscore(struct connect4* copied, BScore BestScore, int k)
{
    int column;
    int turnour = k % 2;
    BScore finalsay = initstruct(copied);
    finalsay.score = BestScore.score;
    finalsay.column = BestScore.column;

    for(column=0;column<7;column++)
    {
        //get the row for the column
        int row = get_row(copied, column);
        //if row isn't valid, move on
        if(not_valid(copied,column) != 0)
            continue;
        //place piece, find score, if highscore then save it
        copied->board[row][column] = copied->whoseTurn;
        BestScore.column = column;
        BestScore.row = row;

        int fakescore = findscore(copied, BestScore);
        if(fakescore == 1000 || fakescore == -1000)
        {
            finalsay.column = column;
            finalsay.score = fakescore;
            return finalsay;
        }
        BestScore.score += fakescore;

        if(k == DEPTH)
        {
            if(finalsay.score < BestScore.score && turnour == 0)
                finalsay.score = BestScore.score;
            else if(finalsay.score > BestScore.score && turnour == 1)
                finalsay.score = BestScore.score;
        }

        //RECURSION
        if(k != DEPTH)
        {
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';
            BScore temp = checkscore(copied, BestScore, k+1);
            //if(temp.score == 1000 || temp.score == -1000) return temp;
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';

            //our turn
            if(turnour == 0)
            {
                if(finalsay.score < temp.score)
                {
                    finalsay.score = temp.score;
                    finalsay.column = column;
                }

            }
            else if(finalsay.score > temp.score)
            {
                finalsay.score = temp.score;
                finalsay.column = column;
            }
        }
        copied->board[row][column] = '_';
        BestScore.score -= fakescore;
    }
    return finalsay;
}

int dxdyEval(struct connect4 *copied, int row, int column, int i, int k)
{

    if ((column >= NUM_COLS || row >= NUM_ROWS || column < 0 || row < 0) && k == 1)
		return 0;
	char currentPos = copied->board[row][column];

    //not straight down
	int odd = (i == 1 || i == 5) ? 6 : 0;

    //if adjacent pieces are next to yours
	if (k == 1 && currentPos != copied->whoseTurn && currentPos != '_')
		return 2+odd;
    //if your piece is next to the place pieced, return a power of 4
	else if (currentPos == copied->whoseTurn)
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) + odd;
    //if you have a blank spot, keep going to see if there's a potential row
    else if (currentPos == '_') return dxdyEval(copied, row+DX[i], column+DY[i], i, k);
    //if you hit a dead end after moving in a direction for a few, turn around and count the real score
    else if (currentPos != copied->whoseTurn && currentPos != '_' && i < 3)
        return dxdyEval(copied, row+DX[i], column+DY[i], DX_SIZE - 1 - i, 0);
	return pow(10, k-1);

}

int findscore (struct connect4* copied, BScore BestScore)
{
    int temp = 0;
    int status = check_status(copied);
    int i;
    char currentPiece = copied->whoseTurn;

    for (i = 0; i < DX_SIZE; i++)
    {
    	int newRow = BestScore.row + DX[i];
    	int newCol = BestScore.column + DY[i];
        int ou = dxdyEval(copied, newRow, newCol, i, 1);
    	 temp += ou;
		//printf("**Adding: %d**\n", temp);
    }

    if(BestScore.column == 3)
        temp += 7;


    else if(BestScore.column == 2 || BestScore.column == 4)
        temp += 4;

    if (currentPiece == 'X' && (status == X_WINS || status == O_WINS))
    	temp = 1000;
    if (currentPiece == 'O' && (status == O_WINS || status == X_WINS))
    	temp = 1000;

    if (BestScore.ourpiece == copied->whoseTurn)
    	return temp;
    else
    	return -(temp);

}

BScore initstruct(const struct connect4* game)
{
    BScore BestScore;
    BestScore.row = 1;
    BestScore.column = 3;
    BestScore.score = 0;
    BestScore.ourpiece = game->whoseTurn;
    return BestScore;
}

int test_depth(const struct connect4 *game)
{
    int bestmove;
    struct connect4* copied = copy(game);

    //get the best move of the 7
    //check for integer best move?
    BScore node = initstruct(game);

     bestmove = checkscore(copied, node, 0).column;

    return bestmove;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    int bestMove;
    bestMove = test_depth(game);
    return bestMove;
}
