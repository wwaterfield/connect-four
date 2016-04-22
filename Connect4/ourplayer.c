#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ourplayer.h"

#define DEBUG 0


BScore g9_checkscore(struct connect4* copied, BScore BestScore, int k)
{
    //1. accidentally hard coded ternary operators
    //2. at the end of our move, check to see if we automatically lose
    //if we lose, just go there instead? see test_depth, check for opposite, and bam
    //3. I'm still not sure why it's glitching, but we can minmax tree it up
    //4. we're having issues with finding easy wins, and although 2. may work
    // looking for a long term option may be better

	// Declaring Variables.
    int column;
    int turnour = k % 2;

    // Initialize the BScore struct and update with new score and columnn.
    BScore finalsay = g9_initstruct(copied);
    finalsay.score = BestScore.score;
    finalsay.column = BestScore.column;

    /* Jasper, what is going on here? */
    //finalsay needs to be equal to the first instance of the minmaxtree
    //     0
    //    /a \b
    //   /\  /\
    // in this example, finalsay in a needs to be equal to the left branch, then the right branch will be
    // compared in k!= DEPTH
    //but I'm almost certain something's wrong here
    //it's comparing several numbers and looking for a least better move or something,
    //??? Check the debug statements and look for "This is the best column"
    //it's the end of the recursion and shows you the best move
    //for that particular branch. I can show you Monday
    //but if we can fix that first that would be cool

    if(!turnour)
        finalsay.score = -3000;
    else finalsay.score = 3000;

    for(column=0;column<7;column++)
    {
        // Get the row for the current column.
        int row = get_row(copied, column);

        // Continue to the next column if the row is not a valid move.
        if(not_valid(copied,column) != 0)
            continue;


        // Place piece, find score, if highscore then save it.
        copied->board[row][column] = copied->whoseTurn;
        BestScore.column = column;
        BestScore.row = row;

        int fakescore = g9_findscore(copied, BestScore);

        if(DEBUG)
            printf("k: %d projected score: %d BestScore before addition: %d\n", k, fakescore, BestScore.score);
        BestScore.score += fakescore;

        if(k == DEPTH)
        {
            if(DEBUG)
                printf("score: %d  vs BestScore: %d, turn: %c\n", finalsay.score, BestScore.score, (turnour == 0) ? 'O' : 'X');
            if(DEBUG)
                printf("column: %d  vs Comparecol: %d, turn: %c\n", finalsay.column, BestScore.column, (turnour == 0) ? 'O' : 'X');

            // If it is the other player's turn, assign finalSay the most negative score.
            if(finalsay.score < fakescore && turnour == 0)
            {
                finalsay.score = BestScore.score;
                finalsay.column = BestScore.column;
            }

            // If it is our player's turn, assign finalSay the greatest positive score.
            else if(finalsay.score > fakescore && turnour == 1)
            {
                finalsay.score = BestScore.score;
                finalsay.column = BestScore.column;
            }

            if(DEBUG)
                printf("final score now: %d best column: %d turn: %c\n\n", finalsay.score, finalsay.column, (turnour == 0) ? 'O' : 'X');
        }

        // Recursively evaluate each possible game position for the defined depth (k).
        if(k != DEPTH)
        {
        	// Alternates between players with each level of depth.
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';
            BScore temp = g9_checkscore(copied, BestScore, k+1);
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';

            //our turn

           if(DEBUG)
                printf("\n\n\ntempscore: %d vs finalscore: %d turn: %c \n", temp.score, finalsay.score, (turnour == 0) ? 'O' : 'X');
            if(DEBUG)
                printf("column: %d vs comparedColumn: %d\n", column, finalsay.column);
            if(turnour == 0)
            {
                if(finalsay.score < temp.score)
                {
                    finalsay.score = temp.score;
                    finalsay.column = column;
                }

            }

           // If it is our player's turn, find the most postive score.
            else if(finalsay.score > temp.score)
            {
                finalsay.score = temp.score;
                finalsay.column = column;
            }
        }

        if(DEBUG)
                printf("k: %d finalscore now: %d vs Column: %d\n", k, finalsay.score, finalsay.column);


        // Reset the game board back to its original position
        // in order to test it again.
        copied->board[row][column] = '_';
         BestScore.score += fakescore;
    }

    if(DEBUG)
        printf("k: %d This is the best column to move: %d with score %d for: %c\n\n", k, finalsay.column, finalsay.score, (turnour == 0) ? 'O' : 'X');
    //finalsay.score += fakescore;
    return finalsay;
}

int dxdyEval(struct connect4 *copied, int row, int column, int i, int k)
{
    int odd = (i == 1 || i == 5) ? 3 : 0;
    if(copied->board[row][column] != copied->whoseTurn)
    {
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
                if(fakescore != 0) fakescore -= 30;

                else fakescore -= 20;
            }

            else if(copied->board[temprow][tempcol] != '_')
                fakescore -= 15;

            if(fakescore == 0)
            	return 300;
            return fakescore + 55+odd*8;
        }
    }

    // Don't add points if a position is out of bounds.
    if ((column >= NUM_COLS || row >= NUM_ROWS || column < 0 || row < 0) && k == 1)
		return 0;
    /* Hmmm...? */
    else if ((column >= NUM_COLS || row >= NUM_ROWS || column < 0 || row < 0))
		k -= 1;

	char currentPos = copied->board[row][column];

    // Not straight down.


    // If adjacent pieces are next to yours
	if (k == 1 && currentPos != copied->whoseTurn && currentPos != '_')
    {
        /*if(copied->board[row+DX[i]][column+DY[i]] != copied->whoseTurn)
        {
            if(copied->board[row+DX[i]*2][column+DY[i]*2] != copied->whoseTurn)
                return 1000;
            else return 150;
        }*/

        return /*dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) +*/ 4 + odd;
    }

    /*
    if (k == 2 && currentPos != copied->whoseTurn && currentPos != '_')
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) + 30 + odd;
    if (k == 3 && currentPos != copied->whoseTurn && currentPos != '_')
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) + 400 + odd;*/

    // If your piece is next to the place pieced, return a power of 7
	else if (currentPos == copied->whoseTurn)
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) + odd;

    // If you have a blank spot, keep going to see if there's a potential row
    else if (currentPos == '_') return dxdyEval(copied, row+DX[i], column+DY[i], i, k);

    // If you hit a dead end after moving in a direction for a few,
	// turn around and count the real score.
    else if (currentPos != copied->whoseTurn && currentPos != '_' && i < 4)
    {
    	if(DEBUG) printf("********DX THINGY: %d\n", DX_SIZE-1 -i);
        return dxdyEval(copied, row+DX[i], column+DY[i], DX_SIZE - 1 - i, 0);
    }

	return pow(7, k-1) + odd;

}

int g9_findscore (struct connect4* copied, BScore BestScore)
{
	// Declaring variables.
    int temp = 0;
    int status = check_status(copied);
    int i;
    char currentPiece = copied->whoseTurn;

    // Use DX and DY arrays to evaluate the pieces surround the possible position.
    for (i = 0; i < DX_SIZE; i++)
    {
    	int newRow = BestScore.row + DX[i];
    	int newCol = BestScore.column + DY[i];
        temp += dxdyEval(copied, newRow, newCol, i, 1);

        if(copied->board[newRow][newCol] == copied->board[BestScore.row-DX[i]][BestScore.column-DY[i]] &&
                copied->board[newRow][newCol] == copied->whoseTurn)
            temp+=3;
    }

    // Ensure extra points for the middle position.
    if(BestScore.column == 3)
        temp += 6;

    // If the middle is not available, columns close to the middle are preferred.
    else if(BestScore.column == 2 || BestScore.column == 4)
        temp += 2;

    // Take immediate action if a move results in either a win or a loss.
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

    // If it is our player's turn, return a positive score.
    if (BestScore.ourpiece == copied->whoseTurn) return temp;

    // If it is the other player's turn, return a negative score.
    else return -(temp);

}


// Initializes the struct used for keeping track of essential information.
BScore g9_initstruct(const struct connect4* game)
{
    BScore BestScore;
    BestScore.row = 1;
    BestScore.column = 3;
    BestScore.score = 0;
    BestScore.ourpiece = game->whoseTurn;
    return BestScore;
}

// Helper function used in evaluating possible game outcomes.
int g9_test_depth(const struct connect4 *game)
{
    int bestmove;
    struct connect4* copied = copy(game);

    BScore node = g9_initstruct(game);

    bestmove = g9_checkscore(copied, node, 0).column;
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


// After evaluating the best move, return the column to place the piece.
int g9_moving(const struct connect4 *game, int secondsLeft)
{
    int bestMove;
    bestMove = g9_test_depth(game);
    return bestMove;
}
