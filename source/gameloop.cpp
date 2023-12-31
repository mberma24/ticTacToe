#include "../include/gameloop.hpp"
#include <iostream>

/*
 * Moduling containg both types of gameloops that can be played in tic-tac-toe (Human/AI).
 *	
 * Author: Michael Berman
 * Date: August 7th 2023
 */

//Human Gameloop
/**
 * Game loop for if user decides to play against another human.
 */
void play_human() {
    int count = 0;
	char turn;

	std::unique_ptr<Board> board(new Board('X', 'O'));

	while (true) {
		if (count % 2 == 0) {
			turn = 'X';
		}else {
			turn = 'O';
		}

		player_move(board, turn);

		
		if 	(board->check_win(turn, true) || board->check_full(true)) {
			board->print();
			return;
		}
		count++;
	}
}

//AI Gameloop
/**
 * Prompts the user to select which letter they want to play as.
 * 
 * @return The user's chosen letter.
 */
char choose_letter() {
    char player;
    while (true) {
		printf("Please select 'X' or 'O':\t");
		if (std::cin >> player && (toupper(player) == 'X' || toupper(player) == 'O')) {
			clear_cin();
            player = toupper(player);

			return player;
		}
		else {
			printf("Invalid input. Please try again\t");
            clear_cin();
		}

	}
}
/**
 * Takes in either 'X' or 'O' and returns the other character.
 * 
 * @param player Either an 'X' or an 'O' character.
 * 
 * @return The complementary letter.
 */
char complement(char player) {
    if (player == 'X') {
        return 'O';
    }
    return 'X';
}
/**
 * Prompts the user for what diffuclty setting they would like
 * to select.
 * 
 * @return The user's chosen setting.
 */
int choose_mode() {
    int mode;
    while (true) {
		printf("Please select difficulty (1-3)  \n");
		if (std::cin >> mode && (mode > 0 && mode < 4)) {
			clear_cin();
            return mode;
		}
		else {
			printf("Invalid input. Please try again\t");
			clear_cin();
		}
	}
}
/**
 * Game loop for if user decides to play against an AI.
 */
void play_bot() {
	//initialize variables
    int count = 0; //turn count
    int turn; //whose turn is it? ('X' or 'O')
    
    char player = choose_letter(); //as user to choose letter
    char ai = complement(player); //get ai letter
	int mode = choose_mode(); //choose difficulty
	
    std::unique_ptr<Board> board(new Board(player, ai)); //create tic-tac-toe board
	
	while (true) {
        //select turn
		if (count % 2 == 0) { //if turn count is even
			turn = 'X'; 
		}else { //if odd
			turn = 'O';
		}
        //player's turn
		if (turn == player) {
			player_move(board, board->get_player()); //prompt player's move
		}
        //ai turn
        else { 
			switch(mode) {
				case 1: //easy diffuclty
					easy_move(board); //prompt random ai move
				    break;
				case 2: //medium difficulty
                    if (!medium_move(board, ai)) { //prompt ai to win if it can
                        if (!medium_move(board, player)) { //prompt ai to block human win if it can
                            easy_move(board); //prompt random ai move
                        }
                    }
				    break;
				case 3: //hard difficulty (impossible)
                    hard_move(board); //make best possible move
				break;
				default: //should not get here
                    printf("ERROR: ???");
				    break;
			}
		}
        //check for win 
		if 	(board->check_win(turn, true) || board->check_full(true)) {
			board->print(); //display final board
			return;
		}
		count++; //increment turn count
	}
}