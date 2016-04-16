#include <stdio.h>
#include <stdlib.h>

#include "ourplayer.h"
#define DEBUG 1

BScore checkscore(struct connect4* copied, BScore BestScore, int k)
{
    int column;
    int turnour = k % 2;

    BScore finalsay = initstruct(copied);
    finalsay.score = BestScore.score;
    finalsay.column = BestScore.column;
    if(!turnour)
        finalsay.score = -3000;
    else finalsay.score = 3000;

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

        if(DEBUG)
            printf("projected score: %d BestScore before addition: %d\n", fakescore, BestScore.score);
        BestScore.score += fakescore;

        if(k == DEPTH)
        {
            if(DEBUG)
                printf("score: %d  vs BestScore: %d, turn: %c\n", finalsay.score, BestScore.score, (turnour == 0) ? 'O' : 'X');
            if(DEBUG)
                printf("column: %d  vs Comparecol: %d, turn: %c\n", finalsay.column, BestScore.column, (turnour == 0) ? 'O' : 'X');
            if(finalsay.score < BestScore.score && turnour == 0)
            {
                finalsay.score = BestScore.score;
                finalsay.column = BestScore.column;
            }

            else if(finalsay.score > BestScore.score && turnour == 1)
            {
                finalsay.score = BestScore.score;
                finalsay.column = BestScore.column;
            }

            if(DEBUG)
                printf("final score now: %d best column: %d turn: %c\n\n", finalsay.score, finalsay.column, (turnour == 0) ? 'O' : 'X');
        }

        //RECURSION
        if(k != DEPTH)
        {
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';
            BScore temp = checkscore(copied, BestScore, k+1);
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';

            //our turn

           if(DEBUG)
                printf("\n\n\ntempscore: %d vs finalscore: %d place: %d turn: %c \n", temp.score, finalsay.score, finalsay.column, (turnour == 0) ? 'O' : 'X');
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

    if(DEBUG)
        printf("k This is the best column to move: %d with score %d for: %c\n\n", finalsay.column, finalsay.score, (turnour == 0) ? 'O' : 'X');
    return finalsay;
}

int dxdyEval(struct connect4 *copied, int row, int column, int i, int k)
{
    if(copied->board[row][column] != copied->whoseTurn)
        if(k==3)
        {
            int fakescore = 0;
            int temprow = row;
            int tempcol = column;
            if ((tempcol >= NUM_COLS || temprow >= NUM_ROWS || tempcol < 0 || temprow < 0) && k == 1)
            fakescore -= 20;
            else if(copied->board[temprow][tempcol] != '_')
            fakescore -= 15;

            temprow = row - DX[i]*4;
            tempcol = column - DY[i]*4;
            if ((tempcol >= NUM_COLS || temprow >= NUM_ROWS || tempcol < 0 || row < 0) && k == 1)
            {
                if(fakescore != 0)
                    fakescore -= 30;
                else fakescore -= 20;
            }
            else if(copied->board[temprow][tempcol] != '_')
                fakescore -= 15;
            if(fakescore == 0)
            return 200;
            return fakescore + 60;
        }


    if ((column >= NUM_COLS || row >= NUM_ROWS || column < 0 || row < 0) && k == 1)
		return 0;
    else if ((column >= NUM_COLS || row >= NUM_ROWS || column < 0 || row < 0))
		k -= 1;

	char currentPos = copied->board[row][column];

    //not straight down
	int odd = (i == 1 || i == 5) ? 6 : 0;

    //if adjacent pieces are next to yours
	if (k == 1 && currentPos != copied->whoseTurn && currentPos != '_')
		return /*dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) +*/ 2 + odd;
    /*
    if (k == 2 && currentPos != copied->whoseTurn && currentPos != '_')
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) + 30 + odd;
    if (k == 3 && currentPos != copied->whoseTurn && currentPos != '_')
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) + 400 + odd;*/

    //if your piece is next to the place pieced, return a power of 4
	else if (currentPos == copied->whoseTurn)
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) + odd;
    //if you have a blank spot, keep going to see if there's a potential row
    else if (currentPos == '_') return dxdyEval(copied, row+DX[i], column+DY[i], i, k);
    //if you hit a dead end after moving in a direction for a few, turn around and count the real score
    else if (currentPos != copied->whoseTurn && currentPos != '_' && i < 3)
        return dxdyEval(copied, row+DX[i], column+DY[i], DX_SIZE - 1 - i, 0);

	return pow(7, k-1);

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

        if(copied->board[newRow][newCol] == copied->board[BestScore.row-DX[i]][BestScore.column-DY[i]] &&
                copied->board[newRow][newCol] == copied->whoseTurn)
            temp+=3;
    	 temp += ou;

    }

    if(BestScore.column == 3)
        temp += 7;


    else if(BestScore.column == 2 || BestScore.column == 4)
        temp += 4;


    if (currentPiece == 'X' && (status == X_WINS))
    	temp = 1000;
    if (currentPiece == 'O' && (status == O_WINS))
    	temp = 1000;
    if (currentPiece == 'X' && (status == O_WINS))
    	temp = -1000;
    if (currentPiece == 'O' && (status == X_WINS))
    	temp = -1000;

    if(DEBUG)
        print_board(copied);
    if(DEBUG)
        printf("temp scored a : for this: %d\n", temp);

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
    if(DEBUG)
        printf("end of iteration.\n\n\n");
    if(not_valid(game, bestmove))
    {
        int i;
        for(i=0;i<NUM_COLS;i++)
            if(!not_valid(game, i))
            {
                bestmove = i;
                break;
            }
    }
    return bestmove;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    int bestMove;
    bestMove = test_depth(game);
    return bestMove;
}
