#include "../include/moves.hpp"

/*
 * Module containing all types of moves that can occur in a game of tic-tac-toe (Human/AI).
 *
 * Author: Michael Berman
 * Date: August 7th 2023
 */

//Hard difficulty
/**
 * Min-Max algorithm. Recursivly every possible move in the game and determines which move
 * an AI can make to have the most chances of winning.
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * @param depth How many layers deep the algorithm is in exploring every possible move.
 * @param is_maxing_player Is it the AI simulating its own turn or the players turn?
 * @param alpha Minimum score maximizing player is assured of.
 * @param beta Maximum score minimizing player is assured of.
 * 
 * @return The best possible score from a branch.
 */
int min_max(const std::unique_ptr<Board>& board, int depth, bool is_maxing_player, int alpha, int beta) {
    if (board->check_win(board->get_ai(), false)) { //if AI win
        return 10;
    }
    if(board->check_win(board->get_player(), false)) { //if human win
        return -10;
    }
    if (board->check_full(false)) { //if draw
        return 0;
    }
    if (is_maxing_player) { //if maxing player
        int best_score = INT_MIN; //score set to min integer
        //iterate through every cell
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) { 
                if(isdigit(board->get_cell(i,j))) { 
                    char backtrack = board->get_cell(i,j); 
                    board->move(i, j, board->get_ai()); //ai looks to the future- asks "what if I made this move?"
                    best_score = std::max(best_score, min_max(board, depth + 1, false, alpha, beta)); //is this better?
                    board->ai_undo(i, j, backtrack); //reset the board to regular

                    alpha = std::max(alpha, best_score); //check if this should be new alpha score
                    if (beta <= alpha) { 
                        break; //quit if min for maxing player is greater than max for mining player.
                    }
                }      
            }
        }
        return best_score;
    }
    else {
        int best_score = INT_MAX;
        //iterate through every move
        for (int i = 0; i < BOARD_SIZE; i++) { 
            for (int j = 0; j < BOARD_SIZE; j++) {
                if(isdigit(board->get_cell(i,j))) { 
                    char backtrack = board->get_cell(i,j); //set backup
                    board->move(i, j, board->get_player()); //ai looks to the future- asks "what if they made this move?"
                    best_score = std::min(best_score, min_max(board, depth + 1, true, alpha, beta)); //is this better?
                    board->ai_undo(i, j, backtrack); //reset the board to regular

                    beta = std::min(beta, best_score); //check if this should be new beta score
                    if (beta <= alpha) { //quit if min for maxing player is greater than max for mining player.
                        break; 
                    }
                }      
            }
        }
        return best_score; //return best score from this branch
    } 
}
/**
 * Makes the best possible move in tic-tac-toe by min-maxing the board.
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * 
 * @return If making the move was successful.
 */
bool hard_move(const std::unique_ptr<Board>& board) {
    int best_score = INT_MIN;
    int row = 0; //row for move
    int col = 0; //column for move
    for (int i = 0; i < BOARD_SIZE; ++i) { //iterate through every cell
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (isdigit(board->get_cell(i, j))) {
                char backtrack = board->get_cell(i, j); //backup
                board->move(i, j, board->get_ai()); //AI asks "what if I made this move?"

                int move_score = min_max(board, 0, false, INT_MIN, INT_MAX); //evaluate the move with min_max 
                board->ai_undo(i, j, backtrack); //undo the move
                if (move_score > best_score) { //if this is best move so far..
                    best_score = move_score; //set this to be the move to make
                    row = i;
                    col = j;
                }
            }
        }
    }
    return board->move(row, col, board->get_ai());
}

//Medium difficulty
/**
 * AI algorithm to win and block the human player from winning when possible.
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * @param turn The AI's letter.
 * 
 * @return Can the AI win or block the human player?
 */
bool medium_move(const std::unique_ptr<Board>& board, char turn) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            //check rows
            if (board->get_cell(i,j) == turn && board->get_cell(i,(j + 1) % BOARD_SIZE) == turn 
                                            && isdigit(board->get_cell(i,(j + 2) % BOARD_SIZE))) {
                return board->move(i, (j + 2) % BOARD_SIZE, board->get_ai());
            }
            //check columns
            if (board->get_cell(j,i) == turn && board->get_cell((j + 1) % BOARD_SIZE, i) == turn 
                                            && isdigit(board->get_cell((j + 2) % BOARD_SIZE, i))) {
                return board->move((j + 2) % BOARD_SIZE, i, board->get_ai());
            }
        }

        //check positive diagonal
        if (board->get_cell(i,i) == turn && board->get_cell((i + 1) % BOARD_SIZE, (i + 1) % BOARD_SIZE) == turn 
                                        && isdigit(board->get_cell((i + 2) % BOARD_SIZE, (i + 2) % BOARD_SIZE))) {
            return board->move((i + 2) % BOARD_SIZE, (i + 2) % BOARD_SIZE, board->get_ai());
        }
        //check negative diagonal
        if (board->get_cell(i,BOARD_SIZE - 1 - i == turn && board->get_cell((i + 1) % BOARD_SIZE, BOARD_SIZE - 1 - (i + 1)) == turn 
                                        && isdigit(board->get_cell((i + 2) % BOARD_SIZE, BOARD_SIZE - 1 - (i + 2))))) {
            return board->move((i + 2) % BOARD_SIZE, BOARD_SIZE - 1 - (i + 2), board->get_ai());
        }
    }
    return false; //nothing found
}

//Easy difficulty
/**
 * AI algorithm to make a completely random move. 
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * 
 * @note Must check board is not full before calling.
 */
void easy_move(const std::unique_ptr<Board>& board) {
    //set random seed once
    static bool srand_called = false;
    if (!srand_called) {
        //set seed
        srand(static_cast<unsigned>(time(NULL)));
        srand_called = true; //make sure seed wont be reset this game
    }

    while (true) {
        //keep generating indices until one is playable
        int row = rand() % 3;
        int col = rand() % 3;

        if (board->move(row, col, board->get_ai())) { //try to play random indices
            break;
        }
    }
}

//Player move
/**
 * Clears and resets the input stream/buffer till it encounter '\n'
 */
void clear_cin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
/**
 * Prompts player to make their move on the board
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * @param turn The Players's letter.
 */
void player_move(const std::unique_ptr<Board>& board, char turn) {
    int digit; //initialize variable to store user input
    board->print(); //print board

	while(true) {
        printf("\nWhere would you like to place your %c?\t", turn);
		if (std::cin >> digit && digit > 0 && digit < 10) {
				if (board->move(digit, turn)) {
                    clear_cin();
					return;
				}else { //move not valid
                    printf("Space already taken. Please try again.\n");
                }
		}else { //input not valid
			printf("Invalid input. Please try again\t");
		}
		clear_cin();
	}
}