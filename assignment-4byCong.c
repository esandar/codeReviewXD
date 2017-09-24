/*
 * assignment-4.c
 *
 *  Created on: Sep 20, 2017
 *      Author: Audrey
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// declare size of the board
const int row = 3;
const int col = 3;

void initBoard(char board[3][3]) {
	char *boardp = &(board[0][0]);
	for (int i = 0; i < row * col; ++i) {
		*(boardp++) = ' ';
	}
}

void displayBoard(char board[3][3]) {
	char *boardp = &(board[0][0]);
	for (int i = 0; i < row; ++i) {
		printf("-------\n");
		for (int j = 0; j < col; ++j) {
			printf("|%c", *(boardp++));
		}
		printf("|\n");
	}
	printf("-------");
}

void markTheBoard(char board[3][3], char mark, int position) {
	char *boardp = &(board[0][0]);
	char *markedPosp = boardp + position - 1;
	*markedPosp = mark;
}

bool hasWon(char board[3][3], char mark) {
	for (int r = 0; r < row; ++r) {
		for (int c = 0; c < col; ++c) {
			if (board[r][c] != mark) { //skip if current element is not mark
				continue;
			}
			if (r + 2 < row) {
				//current element has 2 elements within boundary right to it
				if (board[r+1][c] == mark && board[r+2][c] == mark) {
					//current element is same as the two elements right to it
					return true;
				}
			}
			if (c + 2 < col) {
				//current element has 2 elements within boundary below it
				if (board[r][c+1] == mark && board[r][c+2] == mark) {
					//current element is same as the two elements below it
					return true;
				}
			}
			if (r + 2 < row && c + 2 < col) {
				//current element has 2 elements within boundary diagonally
				if (board[r+1][c+1] == mark && board[r+2][c+2]) {
					//current element is same as the two elements diagonally
					return true;
				}
			}
			if (r - 2 >= 0 && c + 2 < col) {
				//current element has 2 elements within boundary anti-diagonally
				if (board[r-1][c+1] == mark && board[r-2][c+2]) {
					//current element is same as the two elements anti-diagonally
					return true;
				}
			}
		}
	}
	//if none of the above condition is true, player mark hasn't won
	return false;
}

bool isTie(char board[3][3]) {
	char *boardp = &(board[0][0]);
	for (int i = 0; i < row * col; ++i) {
		if (*boardp == ' ') {
			return false;
		}
		boardp++;
	}
	if (hasWon(board, 'X')) {
		return false;
	}
	if (hasWon(board, 'O')) {
		return false;
	}
	return true;
}

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
