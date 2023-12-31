#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "moves.hpp"

//Human Gameloop
/**
 * Game loop if user decides to play against another human.
 */
void play_human();

//AI Gameloop
/**
 * Prompts the user to select which letter they want to play as.
 * 
 * @return The user's chosen letter.
 */
char choose_letter();
/**
 * Takes in either 'X' or 'O' and returns the other character.
 * 
 * @param player Either an 'X' or an 'O' character.
 * 
 * @return The complementary letter.
 */
char complement(char player);
/**
 * Prompts the user for what diffuclty setting they would like
 * to select.
 * 
 * @return The user's chosen setting.
 */
int choose_mode();

/**
 * Game loop for if user decides to play against an AI.
 */
void play_bot();

#endif //GAMELOOP_H