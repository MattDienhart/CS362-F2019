// bug1_unit.c
// This program performs unit testing on the cardEffect() function for the
// Mine card per Bug #1.
//
// Author: Matt Dienhart
// Date: 11-29-2019

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function behaves like "assert()", but does not cause the program
// to exit if the condition is false. Instead, it prints a message to 
// indicate the result of the comparison.
void custom_assert(int condition) {
   if (condition) {
      printf("PASSED\n");
   } else {
      printf("FAILED\n");
   }

   return;
}

int main() {
   // set up card array
   int k[10] = { adventurer, council_room, feast, gardens, baron,
                 remodel, smithy, village, mine, great_hall };

   // declare the game state
   struct gameState G;

   printf("Begin testing the mine card within cardEffect():\n");

   // set up the game state for testing
   int seed = 5; // arbitrary seed for RNG
   G.whoseTurn = 0; //player 1 is the current player
   int player = G.whoseTurn;
   int bonus = 0;
   
   // set up test-specific conditions
   
   // player attempts to trash a copper card and gain a silver card
   printf(" -- Testing Bug #1 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player] = 2;
   G.hand[player][0] = mine;
   G.hand[player][1] = copper;
   G.supplyCount[silver] = 1;
   G.discardCount[player] = 0;
   G.playedCardCount = 0;

   cardEffect(mine, copper, silver, 0, &G, 0, &bonus);

   // show test result
   printf("Checking if Player 1's hand size has decreased by 1: ");
   custom_assert(G.handCount[player] == 1);
   printf("Checking if Player 1's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player] == 1);
   printf("Checking if Player 1's discard pile now contains the Mine card: ");
   custom_assert(G.discard[player][0] == mine);
   printf("Checking if the played cards pile is still empty: ");
   custom_assert(G.playedCardCount == 0);

   printf("Testing completed.\n");

   return 0;
}
