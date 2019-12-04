// bug10_unit.c
// This program performs unit testing on the cardEffect() function for the
// Ambassador card per Bug #10
//
// Author: Robert Elsom
// Date: 12-2-2019

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

   printf("Begin testing the ambassador card within cardEffect():\n");

   // set up the game state for testing
   int seed = 5; // arbitrary seed for RNG
   G.whoseTurn = 0; //player 1 is the current player
   int player = G.whoseTurn;
   int bonus = 0;

   
   // set up test-specific conditions
   

   printf("\n\n -- Testing Bug #10 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player] = 3;

   G.hand[player][0] = ambassador;
   G.hand[player][1] = copper;
   G.hand[player][2] = copper;
   G.coins = 0;
   G.numActions = 2;

   cardEffect(ambassador, 2, 2, 0, &G, 0, &bonus);

   // show test result
   printf("Checking if Player 1 has lost 1 ambassador and 2 copper cards: ");
   custom_assert(G.handCount[player] == 0);


   printf("Testing completed.\n");

   return 0;
}