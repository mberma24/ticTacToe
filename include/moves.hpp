#ifndef MOVES_H
#define MOVES_H

#include "board.hpp"
#include <iostream>

/*
 * Module containing all types of moves that can occur in a game of tic-tac-toe (Human/AI).
 *
 * Author: Michael Berman
 * Date: August 7th 2023
 */

//Hard difficulty (impossible)
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
int min_max(const std::unique_ptr<Board>& board, int depth, int is_maxing_player, int alpha, int beta); 
/**
 * Makes the best possible move in tic-tac-toe by min-maxing the board.
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * 
 * @return If making the move was successful.
 */
bool hard_move(const std::unique_ptr<Board>& board); 

//Medium difficulty
/**
 * AI algorithm to win and block the human player from winning when possible.
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * @param turn The AI's letter.
 * 
 * @return Can the AI win or block the human player?
 */
bool medium_move(const std::unique_ptr<Board>& board, char turn); 

//Easy difficulty
/**
 * AI algorithm to make a completely random move. 
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * 
 * @note Must check board is not full before calling.
 */
void easy_move(const std::unique_ptr<Board>& board);

//Player move
/**
 * Clears and resets the input stream/buffer till it encounter '\n'
 */
void clear_cin();
/**
 * Prompts player to make their move on the board
 * 
 * @param board Pointer to the board objected used by the gameloop.
 * @param turn The Players's letter.
 */
void player_move(const std::unique_ptr<Board>& board, char turn);

#endif //MOVES_H