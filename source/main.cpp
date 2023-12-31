#include "../include/gameloop.hpp"

/**
 * Execute this to play tic-tac-toe! Can be played against a human player
 * or against an AI with 3 difficulty settings.
 */

/**
 * Prompts the user if they would want to play against a human, 
 * AI, or if they would like to quit the program.
 * 
 * @param fire_game Is this the user's first game played?
 * 
 * @return The user's choice.
 */
char ask_mode(int first_game) {
	char choice;
	printf("[0] Quit \n[1] Computer \n"
	       "[2] Human\n");
	if (first_game) {
	    printf("Please select a mode:\t");
	}else {
		printf("Would you like to play again?\t");
	}

	while (true) {
		if (std::cin >> choice) {
			clear_cin();
			return choice;
		}
		else {
			printf("Invalid input. Please try again\t");
            clear_cin();
		}
	}
}

/**
 * Entry point of the program
 * 
 * @return Termination status.
 */
int main() {
    char choice;
	bool first_game = true;
	while (true) {
		choice = ask_mode(first_game = 1);
		switch (choice) {
			case '0':
                return 0;
			case '1':
			    play_bot();
				first_game = false;
 				break;
			case '2':
				play_human();
				first_game = false;
				break;
			default:
				printf("Invalid input. Please try again\n");
				break;
		}
	}
	return 0;
}