// bug3_unit.c
// This program performs unit testing on the cardEffect() function for the
// Remodel card per Bug #3.
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

   printf("Begin testing the remodel card within cardEffect():\n");

   // set up the game state for testing
   int seed = 5; // arbitrary seed for RNG
   G.whoseTurn = 0; //player 1 is the current player
   int player = G.whoseTurn;
   int bonus = 0;
   
   // set up test-specific conditions
   
   // player attempts to trash an estate card and gain a province card
   printf(" -- Testing Bug #3 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player] = 2;
   G.hand[player][0] = remodel;
   G.hand[player][1] = estate;
   G.supplyCount[province] = 2;
   G.discardCount[player] = 0;

   cardEffect(remodel, estate, province, 0, &G, 0, &bonus);

   // show test result
   printf("Checking if Player 1's hand size has stayed the same: ");
   custom_assert(G.handCount[player] == 2);
   printf("Checking if Player 1 still has the Estate card: ");
   custom_assert(G.handCount[player] > 0 && G.hand[player][G.handCount[player]-1] == estate);
   printf("Checking if there is no change to the supply of Province cards: ");
   custom_assert(G.supplyCount[province] == 2);
   printf("Checking if Player 1's discard pile is still empty: ");
   custom_assert(G.discardCount[player] == 0);

   printf("Testing completed.\n");

   return 0;
}
