/*
 * assignment-4.c
 *
 *  Created on: Sep 23, 2017
 *      Author: esandar
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Initialize the 3x3 board array to space characters
void initBoard(char board[3][3]) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			board[i][j] = ' ';
		}
	}
}

// your documentation block here
void markTheBoard(char board[3][3], char turn, int boardPos) {
	board[(boardPos - 1) / 3][(boardPos - 1) % 3] = turn;
}

// Display the board. Vertical bars and dashes for the grid line.
void displayBoard(char board[3][3]) {
	printf("-------------\n");
	for(int i = 0; i < 3; i++){
		printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
		printf("-------------\n");
	}
}

// Consider if any player wins
bool hasWon(const char board[3][3], char marker) {
	for(int i = 0; i < 3; i++) {
	if (((board[i][0] == marker) && (board[i][1] == marker)) && (board[i][2] == marker)) {return true;}
	if (((board[0][i] == marker) && (board[1][i] == marker)) && (board[2][i] == marker)) {return true;}
	}
	if (((board[0][0] == marker) && (board[1][1] == marker)) && (board[2][2] == marker)) {return true;}
	if (((board[0][2] == marker) && (board[1][1] == marker)) && (board[2][0] == marker)) {return true;}
	return false;
}

// Consider if the game is tied.
bool isTie(const char board[3][3]) {
	char *boardp = board;
	for(int i=0 ; i < 9; i++ ){
		if (*(boardp + i) == ' ') { return false;}
	}
	return true;
}

/**
 * Main program for an interactive game of tic-tac-toe.
 */
int main(void) {
	char board[3][3];
	char turn = 'X';

	// initialize the board
	initBoard(board);

    printf("To play a position use the following map to enter a position.\n");
    printf("-------------\n");
    for (int boardPos = 1; boardPos <= 9; boardPos += 3) {
    	printf("| %d | %d | %d |\n", boardPos, boardPos+1, boardPos+2);
            printf("-------------\n");
    }

    // play until there is a draw or a player has won
    while (!isTie(board) && !hasWon(board, 'X') && !hasWon(board, 'O')) {
        int boardPos = -1;
        bool validInput = false;

        // wait for valid input
        while(!validInput) {
            printf("Player %c, enter the position you want to play.\n", turn);
            int success = scanf("%d", &boardPos);
            if (success < 0 || boardPos < 0 || boardPos > 9 ||
                board[(boardPos-1) / 3][(boardPos-1) % 3] != ' ') {
                continue;
            }
            validInput = true;
        }

        // mark the position and display the updated board
        markTheBoard(board, turn, boardPos);

        // display the current board
        displayBoard(board);

        // other player's turn
        switch(turn) {
            case 'X':
                turn = 'O';
                break;
            case 'O':
                turn = 'X';
                break;
        }
    }

    // game over so report results
    if (isTie(board)) {
        printf("The game ends in a tie.\n");
    } else if (hasWon(board, 'X')) {
        printf("Player X has won.");
    } else {
        printf("Player O has won.");
    }

    return EXIT_SUCCESS;
}





