#include <stdio.h>
#include <stdlib.h>

#include "ourplayer.h"


BScore checkscore(struct connect4* copied, BScore BestScore, int k)
{
    int column;
    int turnour = k % 2;
    BScore finalsay = initstruct(copied);

    for(column=0;column<7;column++)
    {
        //get the row for the column
        int row = get_row(copied, column);
        //if row isn't valid, move on
        if(not_valid(copied,column) != 0)
            continue;
        //place piece, find score, if highscore then save it
        copied->board[row][column] = copied->whoseTurn;

        int fakescore = findscore(copied, BestScore);
        BestScore.score = fakescore;
        BestScore.column = column;
        if(column==0)
                finalsay = BestScore;

        if(k == DEPTH)
        {
            printf("score: %d  vs BestScore: %d, turn: %c\n", finalsay.score, BestScore.score, (turn == 0) ? 'O' : 'X');
            if(finalsay.score < BestScore.score && turnour == 0)
                finalsay.score = BestScore.score;
            else if(finalsay.score > BestScore.score && turnour == 1)
                finalsay.score = BestScore.score;
            printf("final score now: %d\n", finalsay.score);
        }

        //RECURSION
        if(k != DEPTH)
        {
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';
            BScore temp = checkscore(copied, BestScore, k+1);
            printf("score2.0: %d finalscore: %d\n", temp.score, finalsay.score);
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';

            //our turn
           printf("tempscore: %d vs finalscore: %d turn: %c \n", temp.score, finalsay.score, (turn == 0) ? 'O' : 'X'));
            if(turnour == 0)
            {
                if(finalsay.score < temp.score)
                {
                	printf("Made it 1st if\n");
                    finalsay.score = temp.score;
                    finalsay.column = column;
                }

            }
            else if(finalsay.score > temp.score)
            {
            	printf("Made it here as well to the else if\n");
                finalsay.score = temp.score;
                finalsay.column = column;
            }
        }

        printf("Actual BestScore: %d\n", BestScore.score);
        copied->board[row][column] = '_';
        BestScore.score -= fakescore;
    }
    return finalsay;
}

int dxdyEval(struct connect4 *copied, int row, int column, int i, int k)
{

	char currentPos = copied->board[row + DX[i]][column + DY[i]];

	if (column > NUM_COLS || row > NUM_ROWS || column < 0 || row < 0)
		return 0;

	int odd = (i % 2 == 0) ? 1 : 2;

	if (k == 1 && currentPos != copied->whoseTurn && currentPos != '_')
		return 5;

	if (currentPos == copied->whoseTurn)
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) * odd;

	return pow(7, k-1);

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
    	int temp = dxdyEval(copied, newRow, newCol, i, 1);
		printf("**Adding: %d**\n", temp);
    	BestScore.score  += temp;
    }

    if(BestScore.column == 3)
        BestScore.score += 30;
    else if(BestScore.column == 2 || BestScore.column == 4) BestScore.score += 12;

    if (currentPiece == 'X' && (status == X_WINS || status == O_WINS))
    	BestScore.score = 1000;
    if (currentPiece == 'O' && (status == O_WINS || status == X_WINS))
    	BestScore.score = 1000;



    print_board(copied);

    if (BestScore.ourpiece == copied->whoseTurn)
    	return BestScore.score;
    else
    	return -(BestScore.score);

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
