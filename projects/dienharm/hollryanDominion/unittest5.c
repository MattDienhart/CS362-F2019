// unittest5.c
// This program performs unit testing on the mineCardEffect() function in 
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
                 remodel, minion, village, mine, great_hall };

   // declare the game state
   struct gameState G;

   // declare arrays
   int coppers[MAX_HAND];
   int silvers[MAX_HAND];
   int minions[MAX_HAND];
   for (int i= 0; i<MAX_HAND; i++) {
      coppers[i] = copper;
      silvers[i] = silver;
      minions[i] = minion;
   }

   printf("Begin testing mineCardEffect():\n");

   // set up the game state for testing
   memset(&G, 23, sizeof(struct gameState)); // set the game state to 23 for all parameters
   int seed = 5; // arbitrary seed for RNG
   const int player1 = 0;
   
   // set up test-specific conditions
   
   // test #1: player trashes a copper to gain a silver
   printf(" -- Test #1 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = mine;
   G.discardCount[player1] = 0;
   G.supplyCount[silver] = 8;
   int choice1 = 0; // hand position of card to be trashed
   int choice2 = 5; // ID of card to be gained from supply
   int handPos = 4; // hand position of the mine card itself

   mineCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if hand count has decreased by 2: ");
   custom_assert(G.handCount[player1] == 3);
   printf("Checking if discard pile has increased by 1: ");
   custom_assert(G.discardCount[player1] == 1);
   printf("Checking if new card in discard pile is a silver card: ");
   custom_assert(G.discard[player1][0] == silver);
   printf("Checking if supply count for silver has decreased by 1: ");
   custom_assert(G.supplyCount[silver] == 7);

   // test #2: player trashes a silver to gain a gold
   printf(" -- Test #2 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], silvers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = mine;
   G.discardCount[player1] = 0;
   G.supplyCount[gold] = 8;
   choice1 = 0; // hand position of card to be trashed
   choice2 = 6; // ID of card to be gained from supply
   handPos = 4; // hand position of the mine card itself

   mineCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if hand count has decreased by 2: ");
   custom_assert(G.handCount[player1] == 3);
   printf("Checking if discard pile has increased by 1: ");
   custom_assert(G.discardCount[player1] == 1);
   printf("Checking if new card in discard pile is a gold card: ");
   custom_assert(G.discard[player1][0] == gold);
   printf("Checking if supply count for gold has decreased by 1: ");
   custom_assert(G.supplyCount[gold] == 7);

   // test #3: player trashes a silver to gain a silver
   printf(" -- Test #3 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], silvers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = mine;
   G.discardCount[player1] = 0;
   G.supplyCount[silver] = 8;
   choice1 = 0; // hand position of card to be trashed
   choice2 = 5; // ID of card to be gained from supply
   handPos = 4; // hand position of the mine card itself

   mineCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if hand count has decreased by 2: ");
   custom_assert(G.handCount[player1] == 3);
   printf("Checking if discard pile has increased by 1: ");
   custom_assert(G.discardCount[player1] == 1);
   printf("Checking if new card in discard pile is a silver card: ");
   custom_assert(G.discard[player1][0] == silver);
   printf("Checking if supply count for silver has decreased by 1: ");
   custom_assert(G.supplyCount[silver] == 7);

   // test #4: player tries to trash a non-treasure card and nothing happens
   printf(" -- Test #4 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], minions, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = mine;
   G.discardCount[player1] = 0;
   G.supplyCount[silver] = 8;
   choice1 = 0; // hand position of card to be trashed
   choice2 = 5; // ID of card to be gained from supply
   handPos = 4; // hand position of the mine card itself

   mineCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if hand count has decreased by 2: ");
   custom_assert(G.handCount[player1] == 3);
   printf("Checking if discard pile has increased by 1: ");
   custom_assert(G.discardCount[player1] == 1);
   printf("Checking if new card in discard pile is a silver card: ");
   custom_assert(G.discard[player1][0] == silver);
   printf("Checking if supply count for silver has decreased by 1: ");
   custom_assert(G.supplyCount[silver] == 7);

   // test #5: player tries to trash a treasure card they don't have and nothing happens
   printf(" -- Test #5 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = mine;
   G.discardCount[player1] = 0;
   G.supplyCount[silver] = 8;
   choice1 = 9; // hand position of card to be trashed (note: bogus input, outside of hand)
   choice2 = 5; // ID of card to be gained from supply
   handPos = 4; // hand position of the mine card itself

   mineCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if discard pile has stayed the same: ");
   custom_assert(G.discardCount[player1] == 0);
   printf("Checking if supply count for silver has stayed the same: ");
   custom_assert(G.supplyCount[silver] == 8);

   // test #6: player tries to trash a copper and gain a gold and nothing happens
   printf(" -- Test #6 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = mine;
   G.discardCount[player1] = 0;
   G.supplyCount[gold] = 8;
   choice1 = 0; // hand position of card to be trashed
   choice2 = 6; // ID of card to be gained from supply
   handPos = 4; // hand position of the mine card itself

   mineCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if discard pile has stayed the same: ");
   custom_assert(G.discardCount[player1] == 0);
   printf("Checking if supply count for gold has stayed the same: ");
   custom_assert(G.supplyCount[gold] == 8);

   // test #7: player tries to trash a copper and gain a non-treasure card and nothing happens
   printf(" -- Test #7 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = mine;
   G.discardCount[player1] = 0;
   G.supplyCount[estate] = 8;
   choice1 = 0; // hand position of card to be trashed
   choice2 = 1; // ID of card to be gained from supply
   handPos = 4; // hand position of the mine card itself

   mineCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if discard pile has stayed the same: ");
   custom_assert(G.discardCount[player1] == 0);
   printf("Checking if supply count for estate has stayed the same: ");
   custom_assert(G.supplyCount[estate] == 8);

   printf("Testing completed.\n");

   return 0;
}
