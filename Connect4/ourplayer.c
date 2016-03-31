#include <stdio.h>
#include <stdlib.h>

#include "con4lib.h"

#define LOSE -1000;
#define WIN 1000;
#define COL_SIZE 7;
#define RUNS 4;

int checkscore(const struct connect4* game)
{
    int i, j;

    int tscore = -1000;
    int highscore;
    int yPos;

    char boardCopy[NUM_ROWS][NUM_COLS];

    // Get a copy of the  current board.
    for (i = 0; i < NUM_ROWS; i++)
    {
        for (j = 0; j < NUM_COLS; j++)
        {
            boardCopy[i][j] = game->board[i][j];
        }
    }


    for(j=0;j<7;j++)
    {
        tscore = score(boardCopy, j, team, game->whoseTurn);
        if(total <= tscore)
        {
            yPos = j;
            highscore = tscore;
        }
    }
}

int score (char board[6][7], int column, char tpiece, char ourpiece)
{
    int total = -1000;
    board[get_row(&board, column)][column] = tpiece;
    int status = check_status(&board);
    //checks four cases: if we placed the piece and we win or not
    //the win case will trigger when we place a piece
    //the lose case will trigger when the hypothetical opponent places a piece
    if(status == X_WINS && ourpiece == tpiece)
        return WIN;
    else if(status == X_WINS && ourpiece != tpiece)
        return LOSE;
    else if(status == O_WINS && ourpiece == tpiece)
        return WIN;
    else if(status == O_WINS && ourpiece != tpiece)
        return LOSE;

    //if() here and see if we get 2 pieces! high-ish score
    //make sure that if we go in the middle we get more points
    //if() here and see if we get 3 pieces! higher score
    //if() here and see if we get 1 lonely piece.  Low score

    //we might split up scoring into the opponent's scoring feature and ours.  That way
    //we can go ahead and have 2 if statements per move...
    //either one works?

    return total;
}

int test_depth(const struct connect4 *game)
{
    int i;
    int bestmove;
    for(i=0;i<RUNS;i++)
    {
        bestmove = checkscore(game);
    }

    return bestmove;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    //here we have to make sure that if score == LOSE Then we MUST place a piece there. Same for win.
    int i = 0;

    int bestMove;

    bestMove = test_depth(game);

    return bestMove;
}
