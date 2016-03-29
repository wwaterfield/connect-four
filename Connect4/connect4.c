// Arup Guha
// Originally written in 1999 for fun.

// Edited on 4/2/08 to provide scaffolding for the COP3502H Group Project

#include <stdlib.h>

#include "con4lib.h"
#include "arupsoldplayer.h"
#include "firstavailable.h"
#include "ourplayer.h"

int main() {

    struct connect4 game;

    int Xtime = INIT_TIME, Ytime = INIT_TIME;
    int status = NOT_OVER;
    int curmove, timespent;

    srand(time(0));

    // Set up the game.
    init_board(&game);
    print_board(&game);

    // Play till the game's over...
    while (status == NOT_OVER) {

        // Get player 1's move.
        if (game.whoseTurn == PLAYERONE) {

	        // Time and retrieve the current computer player's move.
	        timespent = time(0);
            curmove = arup_move(&game, Xtime);
	        timespent = time(0) - timespent;
	        printf("X, have chosen column %d\n", curmove);
	        Xtime -= timespent;

	        // Check if the move entered was invalid.
	        if (not_valid(&game, curmove)) {

                printf("Sorry, that was not a valid move!\n");
                printf("You have defaulted the game.\n");
                status = O_WINS;
            }

            // Or if too much time has been used.
            else if (Xtime < 0) {

                printf("Sorry, you ran out of time!\n");
                printf("You have defaulted the game.\n");
                status = O_WINS;
            }

            // Execute the move for player 1.
            else {
                game.board[get_row(&game,curmove)][curmove] = PLAYERONE;
                game.whoseTurn = PLAYERTWO;
            }
        }

        // Get player 2's move.
        else {

	        // Time and retrieve the current computer player's move.
	        timespent = time(0);
            curmove = moving(&game, Ytime);
	        timespent = time(0) - timespent;
	        printf("O, have chosen column %d\n", curmove);
	        Ytime -= timespent;

	        // Check if the move entered was invalid.
	        if (not_valid(&game, curmove)) {

                printf("Sorry, that was not a valid move!\n");
                printf("You have defaulted the game.\n");
                status = X_WINS;
            }

            // Or if too much time has been used.
            else if (Ytime < 0) {

                printf("Sorry, you ran out of time!\n");
                printf("You have defaulted the game.\n");
                status = X_WINS;
            }

            // Execute the move for player 2.
            else {
                game.board[get_row(&game,curmove)][curmove] = PLAYERTWO;
                game.whoseTurn = PLAYERONE;
            }
        }

        // Check if the status changed by a default rule.
        if (status == X_WINS || status == O_WINS)
            break;

        // Print the board so we can see it!
        print_board(&game);
        printf("Time left for player one: %d seconds\n", Xtime);
        printf("Time left for player two: %d seconds\n", Ytime);
        status = check_status(&game);

        // Wait for 2 seconds.
        timespent = time(0);
        while (time(0)-timespent < DISPLAY_WAIT_TIME);

    } // end while NOT_OVER loop

    // Print out a message for the end of the game.
    if (status == X_WINS)
        printf("Player 1, you win!!!\n");

    else if (status == O_WINS)
        printf("Player 2, you win!!!\n");

    else
        printf("The outcome is a tie!!!\n");

    return 0;
}
