#include <tictac_support.h>
#include <stdio.h>
/**
	make_move: takes a board state and makes a legal
	(hopefully optimal) move

	args:
		int [][3] board: 3x3 array of ints representing the
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		 -1: o

	returns (int):
		the number of steps it took to choose the best move
		(current implementation returns 1 by default, 0 if no move made)
**/

//Helper function to check is board state is a winning condition
//Takes a game state (1, or 0 for player '-1') and returns true if that player has a win condition on the board
bool checkWin(int player, int board[][3]){
    bool hasWon = false;

    //Check which player's turn it is
    if (player == 0)
        player--;

    //check for 3 matching values in rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] + board[i][1] + board[i][2] == 3 * player)
            hasWon = true;

        //Check for columns
        if(board[0][i] + board[1][i] + board[2][i] == 3 * player)
            hasWon = true;

    }
    //Check diagonals
    if(board[0][0] + board[1][1] + board[2][2] == 3 * player)
        hasWon = true;

    if(board[0][2] + board[1][1] + board[2][0] == 3 * player)
        hasWon = true;

    //if(hasWon)
        //printf("%d Wins!\n", player);

    return hasWon;
}

//Check if board is full
//Takes a board and returns true if there are available moves left
bool movesLeft(int board[][3]) {
    for( int i = 0; i < 3; i++ )
        for( int j = 0; j < 3; j++ )
            if(board[i][j] == 0)
                return true;

    return false;
}

//Check for an immediate win
//takes player state and a board
//If there is a winning move, it will make that move and return true, returns false if no winning move
bool makeWinningMove(int player, int board[][3]){

    //Check which player's turn it is
    if (player == 0)
        player--;

    //check for winning move in rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == player && board[i][1] == player )
            if(board[i][2] == 0) {
                printf( "player [%d] made move: [%d,%d]\n", player, i, 2 );
                board[i][2] = player;
                return true;
            }
        if(board[i][1] == player && board[i][2] == player )
            if(board[i][0] == 0) {
                printf( "player [%d] made move: [%d,%d]\n", player, i, 0 );
                board[i][0] = player;
                return true;
            }
        if(board[i][0] == player && board[i][2] == player )
            if(board[i][1] == 0) {
                printf( "player [%d] made move: [%d,%d]\n", player, i, 1 );
                board[i][1] = player;
                return true;
            }

        //check for winning move in columns
        if (board[0][i] == player && board[1][i] == player)
            if (board[2][i] == 0) {
                printf("player [%d] made move: [%d,%d]\n", player, 2, i);
                board[2][i] = player;
                return true;
            }
        if (board[1][i] == player && board[2][i] == player)
            if (board[0][i] == 0) {
                printf("player [%d] made move: [%d,%d]\n", player, 0, i);
                board[0][i] = player;
                return true;
            }
        if (board[0][i] == player && board[2][i] == player)
            if (board[1][i] == 0) {
                printf("player [%d] made move: [%d,%d]\n", player, 1, i);
                board[1][i] = player;
                return true;
            }

    }

    //Check diagonals
    if(board[0][0] == player && board[1][1] == player)
        if(board[2][2] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 2, 2);
            board[2][2] = player;
            return true;
        }
    if(board[1][1] == player && board[2][2] == player)
        if(board[0][0] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 0, 0);
            board[0][0] = player;
            return true;
        }
    if(board[0][0] == player && board[2][2] == player)
        if(board[1][1] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 1, 1);
            board[1][1] = player;
            return true;
        }

    if(board[0][2] == player && board[1][1] == player)
        if(board[2][0] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 2, 0);
            board[2][0] = player;
            return true;
        }
    if(board[2][0] == player && board[1][1] == player)
        if(board[0][2] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 0, 2);
            board[0][2] = player;
            return true;
        }
    if(board[2][0] == player && board[0][2] == player)
        if(board[1][1] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 1, 1);
            board[1][1] = player;
            return true;
        }

    //no winning moves available
    return false;
}


int make_move( int board[][3] )
{

    // figure out what move it is
    int state = 0;
    for( int i = 0; i < 3; i++ )
        for( int j = 0; j < 3; j++ )
            state += board[i][j];

        //Make sure board state is a legal setup
        if(state != 1 && state != -1){
            printf("Problem with board state");
            return 0;
        }

        //Check if board is in a playable state
        //Checks if there is already a winner or board is full
        if(checkWin(1, board)){
            printf("Player 1 has already won");
            return 0;
        }
        else if(checkWin(-1, board)) {
            printf("Player -1 has already won");
            return 0;
        }
        else if(!movesLeft(board)) {
            printf("No moves left on this board\nDraw!");
            return 0;
        }

    //Start next player's move
    state = -state;
    if( state == 0 )
        state = 1;

    //If there is an immediate winning move, make that move and return 1
    if(makeWinningMove(state, board)) {
        printf("%d Wins!\n", state);
        return 1;
    }




    // default behavior: find any unoccupied square and make the move
    for( int i = 0; i < 3; i++ )
        for( int j = 0; j < 3; j++ )
            // find an empty square
            if( board[i][j] == 0 )
            {
                // that's the move
                printf( "player [%d] made move: [%d,%d]\n", state, i, j );
                board[i][j] = state;

                checkWin(state, board);

                return 1;
            }



    // no move was made (board was full)
    return 0;
}

