#include "../include/board.hpp"
#include <iostream>

/*
 * Board Class
 * Represents a tic-tac-toe game board, with two players.
 * 
 * Author: Michael Berman
 * August 7th, 2023
 */

/**
 * Creates an empty tic-tac-toe board with two players (second player does 
 * not necessarily have to be an ai).
 */
Board::Board(char player, char ai) : player(player), ai(ai) {
    char count = '1';
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE+1; j++) {
            if (j < BOARD_SIZE) {
                moves[i][j] = count;
                count++;
            }
            else {
                moves[i][j] = '\0';
            }
        }
    }
}

/**
 * Outputs the contents of the board to the terminal.
 */
void Board::print() {
    printf (" %c | %c | %c\n"
            "-----------\n"
            " %c | %c | %c\n"
            "-----------\n"
            " %c | %c | %c\n",
    moves[0][0],moves[0][1],moves[0][2],
    moves[1][0],moves[1][1],moves[1][2],
    moves[2][0],moves[2][1],moves[2][2]);
}

/**
 * Makes a (player) move on the board.
 * 
 * @param digit The players movement choice.
 * @param turn The player's letter.
 * 
 * @return If move is successful.
 */
bool Board::move(int digit, char turn) {
    if (isdigit(moves[(digit - 1) / BOARD_SIZE][(digit - 1) % BOARD_SIZE])) { //if move is possible
        moves[(digit - 1) / BOARD_SIZE][(digit - 1) % BOARD_SIZE] = turn; //do move
        return true;
    }
    else {
        return false;
    }
}
/**
 * Makes a (AI) move on the board.
 * 
 * @param row Row cooridinate for the move.
 * @param column Column coordinate for the move.
 * @param turn The AI's letter.
 * 
 * @return If move is successful.
 */
bool Board::move(int row, int column, char turn) {
    if (isdigit(moves[row][column])) { //if move is possible
        moves[row][column] = turn; //do move
        return true;
    }
    return false;
}
/**
 * Undo a move (used for AI to see moves ahead).
 * 
 * @param row Row cooridinate for the undo.
 * @param column Column coordinate for the undo.
 * @param turn The AI's letter.
 */
void Board::ai_undo(int row, int column, char turn) {
    moves[row][column] = turn; //sets move coordinate to turn without checks
}

/**
 * Checks if game has been won.
 * 
 * @param turn Player who's letter is checked for a win.
 * @param real Is this simulating or checking for real?
 * 
 * @return Game status.
 */
bool Board::check_win(char turn, bool real) {
    for (int i = 0; i < BOARD_SIZE; i++) { //interate through the board
        if((moves[i][0] == moves[i][1] && moves[i][1] == moves[i][2] && moves[i][2] == turn) ||
            (moves[0][i] == moves[1][i] && moves[1][i] == moves[2][i] && moves[2][i] == turn)) { //check rows and columns
            if (real) {
                printf("Player '%c' has won the game!\n", turn);
            }
            return true;
        }
    }
    if ((moves[0][0] == moves[1][1] && moves[1][1] == moves[2][2] && moves[2][2] == turn) ||
        (moves[0][2] == moves[1][1] && moves[1][1] == moves[2][0] && moves[2][0] == turn)) { //check diagonals
            if (real) {
                printf("Player '%c' has won the game!\n", turn);
            }
            return true;
    }
    return false;
}
/**
 * Checks if game has been tied.
 * 
 *  @param real Is this simulating or checking for real?
 * 
 * @return Game status.
 */
bool Board::check_full(bool real) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (isdigit(moves[i][j])) {
                return 0; //cell is empty
            }
        }
    }
    if (real) {
        printf("The game has been drawn!\n");
    }
    return 1; // all cells full
}

/**
 * View a cell on the game board.
 * 
 * @param row The cell'srow coordinate.
 * @param col The cell's column coordinate.
 * 
 * @return The contents of the cell.
 */
char Board::get_cell(int row, int col) {
    return moves[row][col];
}
/**
 * View what letter the AI is playing as.
 * 
 * @return The AI's letter.
 */
char Board::get_ai() {
    return ai;
}
/**
 * View what letter the Player has choosen.
 * 
 * @return The Players's letter.
 */
char Board::get_player() {
    return player;
}
