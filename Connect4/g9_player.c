#include <stdio.h>
#include <stdlib.h>
#include "g9_player.h"

BScore g9_checkscore(struct connect4* copied, BScore BestScore, int k)
{

	// Declaring Variables.
    int column;
    int turnour = k % 2;

    // Initialize the BScore struct and update with new score and columnn.
    BScore finalsay = g9_initstruct(copied);
    finalsay.score = BestScore.score;
    finalsay.column = BestScore.column;

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
        BestScore.score += fakescore;

        if(k == DEPTH)
        {
            // If it is the other player's turn, assign finalSay the most negative score.
            if(finalsay.score < BestScore.score && turnour == 0)
            {
                finalsay.score = BestScore.score;
                finalsay.column = BestScore.column;
            }

            // If it is our player's turn, assign finalSay the greatest positive score.
            else if(finalsay.score > BestScore.score && turnour == 1)
            {
                finalsay.score = BestScore.score;
                finalsay.column = BestScore.column;
            }

        }

        // Recursively evaluate each possible game position for the defined depth (k).
        if(k != DEPTH)
        {
        	// Alternates between players with each level of depth.
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';
            BScore temp = g9_checkscore(copied, BestScore, k+1);
            copied->whoseTurn = (copied->whoseTurn == 'X') ? 'O' : 'X';

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

        // Reset the game board back to its original position
        // in order to test it again.
        copied->board[row][column] = '_';
        BestScore.score -= fakescore;
    }

     return finalsay;
}

int dxdyEval(struct connect4 *copied, int row, int column, int i, int k)
{
    if(copied->board[row][column] != copied->whoseTurn)
    {
        if(k==3)
        {
        	// Initializing needed variables.
            int fakescore = 0, temprow = row, tempcol = column;

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
            	return 200;
            return fakescore + 60;
        }
    }

    // Don't add points if a position is out of bounds.
    if ((column >= NUM_COLS || row >= NUM_ROWS || column < 0 || row < 0) && k == 1)
		return 0;
    else if ((column >= NUM_COLS || row >= NUM_ROWS || column < 0 || row < 0))
		k -= 1;

	char currentPos = copied->board[row][column];

    // Not straight down.
	int odd = (i == 1 || i == 5) ? 6 : 0;

    // If adjacent pieces are next to yours
	if (k == 1 && currentPos != copied->whoseTurn && currentPos != '_')
    {
        /*if(copied->board[row+DX[i]][column+DY[i]] != copied->whoseTurn)
        {
            if(copied->board[row+DX[i]*2][column+DY[i]*2] != copied->whoseTurn)
                return 1000;
            else return 150;
        }*/

        return /*dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) +*/ 2 + odd;
    }

    // If your piece is next to the place pieced, return a power of 7
	else if (currentPos == copied->whoseTurn)
		return dxdyEval(copied, row+DX[i], column+DY[i], i, k+1) + odd;

    // If you have a blank spot, keep going to see if there's a potential row
    else if (currentPos == '_') return dxdyEval(copied, row+DX[i], column+DY[i], i, k);

    // If you hit a dead end after moving in a direction for a few,
	// turn around and count the real score.
    else if (currentPos != copied->whoseTurn && currentPos != '_' && i < 3)
    {
        return dxdyEval(copied, row+DX[i], column+DY[i], DX_SIZE - 1 - i, 0);
    }

	return pow(7, k-1);

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
        int ou = dxdyEval(copied, newRow, newCol, i, 1);

        if(copied->board[newRow][newCol] == copied->board[BestScore.row-DX[i]][BestScore.column-DY[i]] &&
                copied->board[newRow][newCol] == copied->whoseTurn)
            temp+=3;
    	 temp += ou;

    }

    // Ensure extra points for the middle position.
    if(BestScore.column == 3)
        temp += 7;

    // If the middle is not available, columns close to the middle are preferred.
    else if(BestScore.column == 2 || BestScore.column == 4)
        temp += 4;

    // Take immediate action if a move results in either a win or a loss.
    if (currentPiece == 'X' && (status == X_WINS))
    	temp = 1000;
    if (currentPiece == 'O' && (status == O_WINS))
    	temp = 1000;
    if (currentPiece == 'X' && (status == O_WINS))
    	temp = -1000;
    if (currentPiece == 'O' && (status == X_WINS))
    	temp = -1000;

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
    int bestmove, column;
    struct connect4* copied = copy(game);

    BScore node = g9_initstruct(game);

    bestmove = g9_checkscore(copied, node, 0).column;

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

    // Overide for easy wins/losses.
    for (column = 0; column < NUM_COLS; column++) {

    	char currentPiece, temp;
    	int row = get_row(copied, column);
    	temp = copied->board[row][column];

    	// Temporarily place the opposite piece
    	currentPiece = (game->whoseTurn == 'X') ? 'O' : 'X';
    	copied->board[row][column] = currentPiece;

    	// If a move will result in an immediate loss for our player, override bestmove.
    	int status = check_status(copied);
		if (currentPiece == 'X' && (status == X_WINS))
			bestmove = column;
		if (currentPiece == 'O' && (status == O_WINS))
			bestmove = column;

		// Reset board position.
		copied->board[row][column] = temp;
    }

    return bestmove;
}


// After evaluating the best move, return the column to place the piece.
int g9_move(const struct connect4 *game, int secondsLeft)
{
    int bestMove;
    bestMove = g9_test_depth(game);
    return bestMove;
}
