#ifndef BOARD_H
#define BOARD_H

/*
 * Board Class
 * Represents a tic-tac-toe game board, with two players.
 * 
 * Author: Michael Berman
 * August 7th, 2023
 */

const int BOARD_SIZE = 3;

class Board {
    private:
        char player; //player's letter
        char ai; //ai's letter
        char moves[BOARD_SIZE][BOARD_SIZE + 1]; //array of game moves

    public:
        /**
         * Creates an empty tic-tac-toe board with two players (second player does 
         * not necessarily have to be an ai).
         */
        Board(char player, char ai);

        /**
         * Outputs the contents of the board to the terminal.
         */
        void print();

        /**
         * Makes a (player) move on the board.
         * 
         * @param digit The players movement choice.
         * @param turn The player's letter.
         * 
         * @return If move is successful.
         */
        bool move(int digit, char turn);
        /**
         * Makes a (AI) move on the board.
         * 
         * @param row Row cooridinate for the move.
         * @param column Column coordinate for the move.
         * @param turn The AI's letter.
         * 
         * @return If move is successful.
         */
        bool move(int row, int column, char turn);
        /**
         * Undo a move (used for AI to see moves ahead).
         * 
         * @param row Row cooridinate for the undo.
         * @param column Column coordinate for the undo.
         * @param turn The AI's letter.
         */
        void ai_undo(int row, int column, char turn);

        /**
         * Checks if game has been won.
         * 
         * @param turn Player who's letter is checked for a win.
         * @param real Is this simulating or checking for real?
         * 
         * @return Game status.
         */
        bool check_win(char turn, bool real);
        /**
         * Checks if game has been tied.
         * 
         * @param real Is this simulating or checking for real?
         * @return Game status.
         */
        bool check_full(bool real);

        /**
         * View a cell on the game board.
         * 
         * @param row The cell'srow coordinate.
         * @param col The cell's column coordinate.
         * 
         * @return The contents of the cell.
         */
        char get_cell(int row, int col);
        /**
         * View what letter the AI is playing as.
         * 
         * @return The AI's letter.
         */
        char get_ai();
        /**
         * View what letter the Player has choosen.
         * 
         * @return The Players's letter.
         */
        char get_player(); 
    };

#endif  // BOARD_H