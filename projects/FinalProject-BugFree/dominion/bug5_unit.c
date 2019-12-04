/*
Ryan Holland
CS362
Team Raptor

																										 ___._
																									 .'  <0>'-.._
																									/  /.--.____")
																								 |   \   __.-'~
																								 |  :  -'/
																								/:.  :.-'
__________                                     | : '. |
'--.____  '--------.______       _.----.-----./      :/
				'--.__            `'----/       '-.      __ :/
							'-.___           :           \   .'  )/
										'---._           _.-'   ] /  _/
												 '-._      _/     _/ / _/
														 \_ .-'____.-'__< |  \___
															 <_______.\    \_\_---.7
															|   /'=r_.-'     _\\ =/
													.--'   /            ._/'>
												.'   _.-'
	                     / .--'
											/,/
											|/`)
											'c=,
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Set up land counts in the deck and the discardCount so that they will tally differently.

Keep in mind we are iterating through the number of cards in discardCount both times. If deck > discard, it underreports. If deck < discard, it segfaults.

Let's test it with deck > discard:
*/
int main()
{
	printf("------Testing Bug 5------\n");
// set up a generic game
	int player = 0;
	struct gameState* state = newGame();
	int* cards = kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
	int initialized = initializeGame(2, cards, 55, state);
	if (initialized != 0) {
		printf("problem initializing game!");
	}

	// set up deck & discard sizes
	state->discardCount[player] = 2;
	state->deckCount[player] = 3;

	// set up land counts
	state->discard[player][0] = province;
	state->discard[player][1] = province;
	state->deck[player][0] = estate;
	state->deck[player][1] = estate;
	state->deck[player][2] = estate;
	/*
	The discard pile should give us 2*6 = 12 score.
	The deck pile should give us 3*1 = 3 score.
	Correct score == 15. The problem is, we are iterating one time too few through the deck. We don't see its third estate, so we will have only 14 score.
	*/

	// call the bugged function
	int score = scoreFor(player, state);

	// check results
	printf("EXPECTED: score == 15\n");
	printf("ACTUAL: score == %d\n", score);
	if (score != 15) {
		printf("score was incorrect\n");
	}

}