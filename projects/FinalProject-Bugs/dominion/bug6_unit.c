/*
Ryan Holland
CS362
Team Raptor
*/

/* This is a unit test to determine whether the Feast cardEffect is accidentally overwriting the state->coins variable. */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	printf("------Testing Bug 6-----\n");

	// set up a generic game
	struct gameState* state = newGame();
	int* cards = kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
	int initialized = initializeGame(2, cards, 55, state);
	if (initialized != 0) {
		printf("problem initializing game!");
	}

	// put a coin in our pocket to see if it is removed by the Feast card.
	state->coins = 1;

	// call function to test.
	// It will succeed, but it will wipe our coins in the process.
	// 
	int bonus = 2;
	cardEffect(feast, gardens, 0, 0, state, 0, &bonus);

	// check results
	printf("EXPECTED: coins = 1\n");
	printf("ACTUAL: coins == %d\n", state->coins);
	if (state->coins != 1) {
		printf("error, result not as expected.\n");
	}

	return 0;
}
