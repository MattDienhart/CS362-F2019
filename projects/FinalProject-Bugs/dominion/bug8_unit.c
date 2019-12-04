/*
Ryan Holland
CS362
Team Raptor
*/

/*
We set up the player's hand with 4 cards: One baron, an estate for baron to discard, and 2 copper. We call playCard() and play the baron. Baron should discard the estate and give us 2 coins. Combined with the 2 copper, we should then be able to buy a feast, which costs 4, so we try it.
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	printf("------Testing Bug 8------\n");
	//////// set up a generic game //////////
	int player = 0;
	struct gameState* state = newGame();
	int* cards = kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
	int initialized = initializeGame(2, cards, 55, state);
	if (initialized != 0) {
		printf("problem initializing game!");
	}

	///////// set specific variables //////////
	state->coins = 0;
	state->hand[player][0] = baron;
	state->hand[player][1] = estate;
	state->handCount[player] = 2;

	////////// print before-test variable states ////////
	printf("PRE-TEST state->coins:\n");
	printf("EXPECTED: 0\n");
	printf("ACTUAL:  %d\n", state->coins);

	////////// call function to test ///////////
	int test = playCard(0, 1, 0, 0, state);
	if (test != 0) {
		printf("playCard failed!\n");
	}
	////////// check for expected result ////////
	printf("POST-TEST state->coins:\n");
	printf("EXPECTED: 4\n");
	printf("ACTUAL:  %d\n", state->coins);
	/*
	printf("POST-TEST coin_bonus:\n");
	printf("EXPECTED: 4\n");
	printf("ACTUAL:  %d\n", coin_bonus);
	
	// try to buy a "feast" card, which costs 4
	if (buyCard(feast, state) != 0) {
		// not able to buy the card
		printf("not able to buy 4-coin card\n");

	}
	*/

	return 0;
}

