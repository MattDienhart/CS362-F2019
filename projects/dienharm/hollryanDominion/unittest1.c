// unittest1.c
// This program performs unit testing on the baronCardEffect() function in 
// "dominion.c".
//
// Author: Matt Dienhart
// Date: 11-2-2019

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

   // declare arrays
   int estates[MAX_HAND];
   int coppers[MAX_HAND];
   for (int i= 0; i<MAX_HAND; i++) {
      estates[i] = estate;
      coppers[i] = copper;
   }

   printf("Begin testing baronCardEffect():\n");

   // set up the game state for testing
   memset(&G, 23, sizeof(struct gameState)); // set the game state to 23 for all parameters
   int seed = 5; // arbitrary seed for RNG
   int player = 0;
   
   // set up test-specific conditions
   
   // test #1: player chooses to discard an estate card and gain 4 coins
   printf(" -- Test #1 --\n");
   initializeGame(2, k, seed, &G);
   G.numBuys = 1;
   G.coins = 0;
   G.handCount[player] = 5;
   memcpy(G.hand[player], estates, sizeof(int) * G.handCount[player]);
   int choice = 1;

   baronCardEffect(choice, player, &G);

   // show test result
   printf("Checking if numBuys has increased by 1: ");
   custom_assert(G.numBuys == 2);
   printf("Checking if coin count has increased by 4: ");
   custom_assert(G.coins == 4);
   printf("Checking if hand count has decreased by 1: ");
   custom_assert(G.handCount[player] == 4);

   // test #2: player chooses to discard an estate card, but does not have one
   printf(" -- Test #2 --\n");
   initializeGame(2, k, seed, &G);
   G.numBuys = 1;
   G.coins = 0;
   G.handCount[player] = 5;
   memcpy(G.hand[player], coppers, sizeof(int) * G.handCount[player]);
   G.discardCount[player] = 0;
   G.supplyCount[estate] = 8;
   choice = 1;

   baronCardEffect(choice, player, &G);

   // show test result
   printf("Checking if numBuys has increased by 1: ");
   custom_assert(G.numBuys == 2);
   printf("Checking if player's discard count has increased by 1: ");
   custom_assert(G.discardCount[player] == 1);
   printf("Checking if gained card is an estate card: ");
   custom_assert(G.discard[player][0] == estate);
   printf("Checking if estate card supply has decreased by 1: ");
   custom_assert(G.supplyCount[estate] == 7);

   // test #3: player chooses to gain an estate card from supply
   printf(" -- Test #3 -- \n");
   initializeGame(2, k, seed, &G);
   G.numBuys = 1;
   G.coins = 0;
   G.handCount[player] = 5;
   memcpy(G.hand[player], estates, sizeof(int) * G.handCount[player]);
   G.supplyCount[estate] = 8;
   G.discardCount[player] = 0;
   choice = 0;

   baronCardEffect(choice, player, &G);

   // show test result
   printf("Checking if numBuys has increased by 1: ");
   custom_assert(G.numBuys == 2);
   printf("Checking if player's discard count has increased by 1: ");
   custom_assert(G.discardCount[player] == 1);
   printf("Checking if gained card is an estate card: ");
   custom_assert(G.discard[player][0] == estate);
   printf("Checking if estate card supply has decreased by 1: ");
   custom_assert(G.supplyCount[estate] == 7);

   // test #4: player chooses to gain an estate card but supply is empty
   printf(" -- Test #3 -- \n");
   initializeGame(2, k, seed, &G);
   G.numBuys = 1;
   G.coins = 0;
   G.handCount[player] = 5;
   memcpy(G.hand[player], estates, sizeof(int) * G.handCount[player]);
   G.supplyCount[estate] = 0;
   G.discardCount[player] = 0;
   choice = 0;

   baronCardEffect(choice, player, &G);

   // show test result
   printf("Checking if numBuys has stayed the same: ");
   custom_assert(G.numBuys == 1);
   printf("Checking if player's discard count has stayed the same: ");
   custom_assert(G.discardCount[player] == 0);
   printf("Checking if estate card supply has stayed at 0: ");
   custom_assert(G.supplyCount[estate] == 0);


   printf("Testing completed.\n");

   return 0;
}
