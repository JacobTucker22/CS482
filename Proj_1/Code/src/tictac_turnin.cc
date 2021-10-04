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
//Takes a game state (1, or 0 for player '-1') and returns 10 * player
//Used for minimax heuristic
int checkWin(int player, int board[][3]) {
    int score = 0;

    //Check which player's turn
    if (player == 0)
        player--;

    //check for 3 matching values in rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] + board[i][1] + board[i][2] == 3 * player)
            return 10 * player;

        //Check for columns
        if (board[0][i] + board[1][i] + board[2][i] == 3 * player)
            return 10 * player;

    }
    //Check diagonals
    if (board[0][0] + board[1][1] + board[2][2] == 3 * player)
        return 10 * player;

    if (board[0][2] + board[1][1] + board[2][0] == 3 * player)
        return 10 * player;

    //if(hasWon)
    //printf("%d Wins!\n", player);

    return score;
}

//Check if board is full
//Takes a board and returns true if there are available moves left
bool movesLeft(int board[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0)
                return true;
        }
    }
    return false;
}

//Check for an immediate win
//takes player state and a board
//If there is a winning move, it will make that move and return true, returns false if no winning move
bool makeWinningMove(int player, int board[][3]) {

    //Check which player's turn it is
    if (player == 0)
        player--;

    //check for winning move in rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player)
            if (board[i][2] == 0) {
                printf("player [%d] made move: [%d,%d]\n", player, i, 2);
                board[i][2] = player;
                return true;
            }
        if (board[i][1] == player && board[i][2] == player)
            if (board[i][0] == 0) {
                printf("player [%d] made move: [%d,%d]\n", player, i, 0);
                board[i][0] = player;
                return true;
            }
        if (board[i][0] == player && board[i][2] == player)
            if (board[i][1] == 0) {
                printf("player [%d] made move: [%d,%d]\n", player, i, 1);
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
    if (board[0][0] == player && board[1][1] == player)
        if (board[2][2] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 2, 2);
            board[2][2] = player;
            return true;
        }
    if (board[1][1] == player && board[2][2] == player)
        if (board[0][0] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 0, 0);
            board[0][0] = player;
            return true;
        }
    if (board[0][0] == player && board[2][2] == player)
        if (board[1][1] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 1, 1);
            board[1][1] = player;
            return true;
        }

    if (board[0][2] == player && board[1][1] == player)
        if (board[2][0] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 2, 0);
            board[2][0] = player;
            return true;
        }
    if (board[2][0] == player && board[1][1] == player)
        if (board[0][2] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 0, 2);
            board[0][2] = player;
            return true;
        }
    if (board[2][0] == player && board[0][2] == player)
        if (board[1][1] == 0) {
            printf("player [%d] made move: [%d,%d]\n", player, 1, 1);
            board[1][1] = player;
            return true;
        }

    //no winning moves available
    return false;
}

//miniMaxMove implements the minimax search to determine the best move
//Takes: a 3x3 int array representing the game board, a bool showing if it is on mini or max,
//        an int representing which player's turn it is, an int by reference to cumulate the total score,
//          and an int showing how many turns each state is away from the initial
//Returns an int representing the minimax score of the game state passed into it.
int miniMaxMove(int board[][3], bool isMaximizer, int player, int &totalScore, int turns) {

    //return score values from win states. 10 for player making move wins and -10 if opposing player wins
    if (checkWin(player, board) == 10 * player)
        return 10;
    if (checkWin(-player, board) == 10 * -player)
        return -10;
    //terminate if no moves left
    if (!movesLeft(board)) {
        return 0;
    }

    //if doing a maximizing step, initialize score to very low number
    //for minimizer, initialize a very high number
    if (isMaximizer) {
        int score = -9999;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    //explore every remaining move
                    board[i][j] = player;
                    score = std::max(score, miniMaxMove(board, !isMaximizer, player, totalScore, turns + 1)) - turns;
                    totalScore += score;
                    board[i][j] = 0;
                }
            }
        }
        return score;
    } else {
        int score = 9999;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    //explore every remaining move
                    board[i][j] = -player;
                    int temp = miniMaxMove(board, !isMaximizer, player, totalScore, turns + 1) + turns;
                    score = std::min(score, miniMaxMove(board, !isMaximizer, player, totalScore, turns + 1) + turns);
                    totalScore += score;
                    board[i][j] = 0;
                }
            }
        }
        return score;
    }
}

//make move takes the board state, determines whose turn it is and makes use of minimax to make the move
//returns 1 if succesful move made, 0 if no moves were able to be made
int make_move(int board[][3]) {

    move nextMove;
    int bestMove = -9999;

    // figure out what move it is
    int state = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            state += board[i][j];

    //Make sure board state is a legal setup
    if (state > 1 || state < -1) {
        printf("Problem with board state");
        return 0;
    }

    //Check if board is in a playable state
    //Checks if there is already a winner or board is full
    if (checkWin(1, board) == 10) {
        printf("Player 1 has already won");
        return 0;
    } else if (checkWin(-1, board) == -10) {
        printf("Player -1 has already won");
        return 0;
    } else if (!movesLeft(board)) {
        printf("No moves left on this board\nDraw!");
        return 0;
    }

    //Start next player's move
    state = -state;
    if (state == 0)
        state = 1;

    //If there is an immediate winning move, make that move and return 1
    if (makeWinningMove(state, board)) {
        printf("Player %d Wins!\n", state);
        return 1;
    }

    //This board is used to hold the minimax values of each position on the board
    //initialized to -999 to make it obvious which ones had not been changed
    // i.e. they were not an available move
    int tempBoard[3][3] = {{-999, -999, -999},
                           {-999, -999, -999},
                           {-999, -999, -999}};

    // Find the optimal move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // find an empty square
            if (board[i][j] == 0) {
                // try that move
                board[i][j] = state;
                //get minimax value for that move
                int tempMove = 0;
                tempMove = miniMaxMove(board, false, state, tempMove, 0);
                tempBoard[i][j] = tempMove;
                //reset the move
                board[i][j] = 0;

                //If that move has better score than current move, update next move
                if (bestMove < tempMove) {
                    bestMove = tempMove;
                    nextMove.row = i;
                    nextMove.col = j;
                }
            }
        }
    }

    //Make the move
    board[nextMove.row][nextMove.col] = state;

    //Shows the minimax values calculated for each position
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d     ", tempBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //Show the board after move is made
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d     ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //print the move that was made
    printf("player [%d] made move: [%d,%d]\n", state, nextMove.row, nextMove.col);

    //Checks for win condition after move is made
    if(checkWin(state, board) == 10 * state){
        printf("Player %d Wins!", state);
    }
    else if(!movesLeft(board)) {
        printf("No moves left\nDraw!");
    }

    return 1;
}

