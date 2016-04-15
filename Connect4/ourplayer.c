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
    if(k==0)
        finalsay.score = -1000;

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
                finalsay.score = BestScore.score;
            else if(finalsay.score > BestScore.score && turnour == 1)
                finalsay.score = BestScore.score;
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
                	if(DEBUG)
                        printf("Made it 1st if\n");
                    finalsay.score = temp.score;
                    finalsay.column = column;
                }

            }
            else if(finalsay.score > temp.score)
            {
            	if(DEBUG)
                    printf("Made it here as well to the else if\n");
                finalsay.score = temp.score;
                finalsay.column = column;
            }
        }
        copied->board[row][column] = '_';
        BestScore.score -= fakescore;
    }

    if(DEBUG)
        printf("This is the best column to move: %d with score %d for: %c\n\n", finalsay.column, finalsay.score, (turnour == 0) ? 'O' : 'X');
    return finalsay;
}

//we may very well need to check four in every direction and see what happens.
//to be determined :/
//  X . _ . _ .
//  . _ O _ . .
//  X _!O!O O _
//  . _ O X . .
//in this example !O! is the main point to consider
//we want to make sure, in all directions, what is happening
//and perhaps then we'll return a value and tada!
//it may be a smarter player than what we're already doing

//wyatt, we may have to re-create our dxdyeval all over again

int check(struct connect4* copied, int array[7])
{
    //connected 1 is our piece
    //connected -1 means their piece previously
    int i, connected = 0, score = 0;
    for(i=0;i<7;i++)
    {

        if(array[i] == -2)
            continue;
        else if(array[i] == -1)
        {
            if(connected >= 0)
                connected = -1;
            else if(connected < 0)
                connected--;

            score += pow(2-connected*2, -connected);
        }
        else if(array[i] == 0)
            score+=1;
        else
        {
            if(connected <= 0)
                connected = 1;
            else if(connected > 0)
                connected++;

            score += pow(3, connected);
        }

        if(DEBUG)
            printf("score: %d\n  connected: %d\n", score, connected);
    }
    return score;
}

int dxdyEval(struct connect4 *copied, int row, int column, int i)
{
    int array[7] = {0, 0, 0, 1, 0, 0, 0};

    int j;
    for(j=0;j<2;j++)
    {
        row += DX[i];
        column += DY[i];
    }

    for(j=0;j<7;j++)
    {
        if ((column >= NUM_COLS || row >= NUM_ROWS || column < 0 || row < 0))
            array[j] = -2;
        else if(copied->board[column][row] == '_') array[j] = 0;
        else if(copied->board[column][row] == copied->whoseTurn) array[j] = 1;
        else array[j] = -1;
        row -= DX[i];
        column -= DY[i];
        if(DEBUG)
            printf(" %d ", array[j]);
    }

        //run through every if statement here regarding what happens to every piece
        int score =check(copied, array);

        return score;
}

int findscore (struct connect4* copied, BScore BestScore)
{
    int temp = 0;
    int status = check_status(copied);
    int i;
    char currentPiece = copied->whoseTurn;

    for (i = 0; i < DX_SIZE-3; i++)
    {
    	int newRow = BestScore.row + DX[i];
    	int newCol = BestScore.column + DY[i];
    	if(DEBUG)
            printf("row: %d col: %d  ", BestScore.row, BestScore.column);
        int ou = dxdyEval(copied, newRow, newCol, i);
        if(DEBUG)
            printf("**Adding %d at DX: %d DY: %d**\n",ou, DX[i], DY[i]);
    	 temp += ou;
    }

    if(BestScore.column == 3)
    {
        temp += 7;
        if(DEBUG)
            printf("**Adding 7 because row 3**\n");
    }


    else if(BestScore.column == 2 || BestScore.column == 4)
    {
        if(DEBUG)
            printf("**Adding 4 because row 2 || 4\n");
        temp += 4;
    }

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

    return bestmove;
}

int moving(const struct connect4 *game, int secondsLeft)
{
    int bestMove;
    bestMove = test_depth(game);
    return bestMove;
}
