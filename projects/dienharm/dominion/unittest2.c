// unittest2.c
// This program performs unit testing on the minionCardEffect() function in 
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
   for (int i= 0; i<MAX_HAND; i++) {
      coppers[i] = copper;
   }

   printf("Begin testing minionCardEffect():\n");

   // set up the game state for testing
   memset(&G, 23, sizeof(struct gameState)); // set the game state to 23 for all parameters
   int seed = 5; // arbitrary seed for RNG
   const int player1 = 0;
   const int player2 = 1;
   const int player3 = 2;
   const int player4 = 3;
   
   // set up test-specific conditions
   
   // test #1: player chooses to gain 2 coins
   printf(" -- Test #1 --\n");
   initializeGame(4, k, seed, &G);
   G.numActions = 0;
   G.coins = 0;
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = minion;
   G.discardCount[player1] = 0;
   int choice1 = 1;
   int choice2 = 0;
   int handPos = 4; // selected card is the last card in the player's hand

   minionCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if numActions has increased by 1: ");
   custom_assert(G.numActions == 1);
   printf("Checking if coin count has increased by 2: ");
   custom_assert(G.coins == 2);
   printf("Checking if hand count has decreased by 1: ");
   custom_assert(G.handCount[player1] == 4);
   printf("Checking if discard pile has increased by 1: ");
   custom_assert(G.discardCount[player1] == 1);
   printf("Checking if discarded card was a minion card: ");
   custom_assert(G.discard[player1][0] == minion);

   // test #2: player chooses to discard their hand, draw 4 cards, and other players do the same
   printf(" -- Test #2 --\n");
   initializeGame(4, k, seed, &G);
   G.numActions = 0;
   G.coins = 0;
   G.handCount[player1] = 5;
   G.handCount[player2] = 4;
   G.handCount[player3] = 5;
   G.handCount[player4] = 0;
   G.discardCount[player1] = 0;
   G.discardCount[player2] = 0;
   G.discardCount[player3] = 0;
   G.discardCount[player4] = 0;
   choice1 = 0;
   choice2 = 1;
   handPos = 4; // selected card is the last card in the player's hand

   minionCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if numActions has increased by 1: ");
   custom_assert(G.numActions == 1);
   printf("Checking if player 1's discard count has increased by 5: ");
   custom_assert(G.discardCount[player1] == 5);
   printf("Checking if player 1's hand size is now 4: ");
   custom_assert(G.handCount[player1] == 4);
   printf("Checking if player 2's discard count is still 0: ");
   custom_assert(G.discardCount[player2] == 0);
   printf("Checking if player 2's hand size is still 4: ");
   custom_assert(G.handCount[player2] == 4);
   printf("Checking if player 3's discard count has increased by 5: ");
   custom_assert(G.discardCount[player3] == 5);
   printf("Checking if player 3's hand size is now 4: ");
   custom_assert(G.handCount[player3] == 4);
   printf("Checking if player 4's discard count is still 0: ");
   custom_assert(G.discardCount[player4] == 0);
   printf("Checking if player 4's hand size is still 0: ");
   custom_assert(G.handCount[player4] == 0);

   // test #3: player's choice is invalid, nothing should happen
   printf(" -- Test #3 -- \n");
   initializeGame(2, k, seed, &G);
   G.numActions = 0;
   G.coins = 0;
   G.handCount[player1] = 5;
   G.handCount[player2] = 7;
   G.discardCount[player1] = 0;
   G.discardCount[player2] = 0;
   choice1 = 0;
   choice2 = 0;
   handPos = 4; // selected card is the last card in the player's hand

   minionCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if numActions has stayed the same: ");
   custom_assert(G.numActions == 0);
   printf("Checking if player 1's discard count has stayed the same: ");
   custom_assert(G.discardCount[player1] == 0);
   printf("Checking if player 1's hand size is still 5: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if player 2's discard count is still 0: ");
   custom_assert(G.discardCount[player2] == 0);
   printf("Checking if player 2's hand size is still 7: ");
   custom_assert(G.handCount[player2] == 7);
 

   printf("Testing completed.\n");

   return 0;
}
