// unittest4.c
// This program performs unit testing on the tributeCardEffect() function in 
// "dominion.c".
//
// Author: Matt Dienhart
// Date: 11-2-2019

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// note: turn DEBUG mode on in dominion.h

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
                 remodel, tribute, village, mine, great_hall };

   // declare the game state
   struct gameState G;

   // declare arrays
   int coppers[MAX_HAND];
   int minions[MAX_HAND];
   int estates[MAX_HAND];
   for (int i= 0; i<MAX_HAND; i++) {
      coppers[i] = copper;
      minions[i] = minion;
      estates[i] = estate;
   }

   printf("Begin testing tributeCardEffect():\n");

   // set up the game state for testing
   memset(&G, 23, sizeof(struct gameState)); // set the game state to 23 for all parameters
   int seed = 5; // arbitrary seed for RNG
   const int player1 = 0;
   const int player2 = 1;
   const int player3 = 2;
   const int player4 = 3;
   
   // set up test-specific conditions
   
   // test #1: player to the left is player 2, 2 copper cards are revealed
   printf(" -- Test #1 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player2] = 20;
   memcpy(G.deck[player2], coppers, sizeof(int) * G.deckCount[player2]);
   G.discardCount[player2] = 0;

   tributeCardEffect(player1, &G);

   // show test result
   printf("Checking if numActions has stayed the same: ");
   custom_assert(G.numActions == 1);
   printf("Checking if coin count has increased by 2: ");
   custom_assert(G.coins == 2);
   printf("Checking if player 1's hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if player 2's discard pile has increased by 2: ");
   custom_assert(G.discardCount[player2] == 2);
   printf("Checking if player 2 discarded a copper card: ");
   custom_assert(G.discard[player2][0] == copper);
   printf("Checking if player 2 discarded another copper card: ");
   custom_assert(G.discard[player2][1] == copper);

   // test #2: player to the left is player 1, 2 minion cards are revealed
   printf(" -- Test #2 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player2] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player1] = 20;
   memcpy(G.deck[player1], minions, sizeof(int) * G.deckCount[player1]);
   G.discardCount[player1] = 0;

   tributeCardEffect(player2, &G);

   // show test results
   printf("Checking if numActions has increased by 2: ");
   custom_assert(G.numActions == 3);
   printf("Checking if coin count has stayed the same: ");
   custom_assert(G.coins == 0);
   printf("Checking if player 2's hand count has stayed the same: ");
   custom_assert(G.handCount[player2] == 5);
   printf("Checking if player 1's discard pile has increased by 2: ");
   custom_assert(G.discardCount[player2] == 2);
   printf("Checking if player 1 discarded a minion card: ");
   custom_assert(G.discard[player1][0] == minion);
   printf("Checking if player 1 discarded another minion card: ");
   custom_assert(G.discard[player1][1] == minion);

   // test #3: player to the left is player 1, 2 estate cards are revealed
   printf(" -- Test #3 --\n");
   initializeGame(4, k, seed, &G);
   G.handCount[player4] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player1] = 20;
   memcpy(G.deck[player1], estates, sizeof(int) * G.deckCount[player1]);
   G.discardCount[player1] = 0;

   tributeCardEffect(player4, &G);

   // show test results
   printf("Checking if numActions has stayed the same: ");
   custom_assert(G.numActions == 1);
   printf("Checking if coin count has stayed the same: ");
   custom_assert(G.coins == 0);
   printf("Checking if player 4's hand count has increased by 2: ");
   custom_assert(G.handCount[player4] == 5);
   printf("Checking if player 1's discard pile has increased by 2: ");
   custom_assert(G.discardCount[player2] == 2);
   printf("Checking if player 1 discarded a minion card: ");
   custom_assert(G.discard[player1][0] == estate);
   printf("Checking if player 1 discarded another minion card: ");
   custom_assert(G.discard[player1][1] == estate);

   // test #4: player to the left is player 3, 1 estate card and 1 copper card are revealed
   printf(" -- Test #4 --\n");
   initializeGame(4, k, seed, &G);
   G.handCount[player2] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player3] = 20;
   memcpy(G.deck[player3], estates, sizeof(int) * (G.deckCount[player3] - 1));
   G.deck[player3][19] = copper;
   G.discardCount[player3] = 0;

   tributeCardEffect(player2, &G);

   // show test results
   printf("Checking if numActions has stayed the same: ");
   custom_assert(G.numActions == 1);
   printf("Checking if coin count has increased by 2: ");
   custom_assert(G.coins == 2);
   printf("Checking if player 2's hand count has increased by 2: ");
   custom_assert(G.handCount[player2] == 7);
   printf("Checking if player 3's discard pile has increased by 2: ");
   custom_assert(G.discardCount[player3] == 2);
   printf("Checking if player 3 discarded a copper card: ");
   custom_assert(G.discard[player3][0] == copper);
   printf("Checking if player 3 discarded an estate card: ");
   custom_assert(G.discard[player3][1] == estate);

   // test #5: player to the left is player 4, 1 copper card and 1 silver card are revealed
   printf(" -- Test #5 --\n");
   initializeGame(4, k, seed, &G);
   G.handCount[player3] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player4] = 20;
   memcpy(G.deck[player4], coppers, sizeof(int) * (G.deckCount[player4] - 1));
   G.deck[player4][19] = silver;
   G.discardCount[player4] = 0;

   tributeCardEffect(player3, &G);

   // show test results
   printf("Checking if numActions has stayed the same: ");
   custom_assert(G.numActions == 1);
   printf("Checking if coin count has increased by 4: ");
   custom_assert(G.coins == 4);
   printf("Checking if player 3's hand count has stayed the same: ");
   custom_assert(G.handCount[player3] == 5);
   printf("Checking if player 4's discard pile has increased by 2: ");
   custom_assert(G.discardCount[player4] == 2);
   printf("Checking if player 4 discarded a silver card: ");
   custom_assert(G.discard[player4][0] == silver);
   printf("Checking if player 4 discarded a copper card: ");
   custom_assert(G.discard[player4][1] == copper);

   // test #6: player to the left is player 2, 1 minion card in deck and 1 duchy card in discard
   printf(" -- Test #6 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player2] = 1;
   G.deck[player2][0] = minion;
   G.discardCount[player2] = 1;
   G.discard[player2][0] = duchy;

   tributeCardEffect(player1, &G);

   // show test results
   printf("Checking if numActions has increased by 2: ");
   custom_assert(G.numActions == 3);
   printf("Checking if coin count has stayed the same: ");
   custom_assert(G.coins == 0);
   printf("Checking if player 1's hand count has increased by 2: ");
   custom_assert(G.handCount[player1] == 7);
   printf("Checking if player 2's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player2] == 2);
   printf("Checking if player 2 discarded a minion card: ");
   custom_assert(G.discard[player2][0] == minion);
   printf("Checking if player 2 discarded a duchy card: ");
   custom_assert(G.discard[player2][1] == duchy);

   // test #7: player to the left is player 2, 1 silver card in the deck only
   printf(" -- Test #7 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player2] = 1;
   G.deck[player2][0] = silver;
   G.discardCount[player2] = 0;

   tributeCardEffect(player1, &G);

   // show test results
   printf("Checking if numActions has stayed the same: ");
   custom_assert(G.numActions == 1);
   printf("Checking if coin count has increased by 2: ");
   custom_assert(G.coins == 2);
   printf("Checking if player 1's hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if player 2's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player2] == 1);
   printf("Checking if player 2 discarded a silver card: ");
   custom_assert(G.discard[player2][0] == silver);

   // test #8: player to the left is player 2, 1 ambassador card in the discard pile only
   printf(" -- Test #8 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player2] = 0;
   G.discardCount[player2] = 1;
   G.discard[player2][0] = ambassador;

   tributeCardEffect(player1, &G);

   // show test results
   printf("Checking if numActions has increased by 2: ");
   custom_assert(G.numActions == 3);
   printf("Checking if coin count has stayed the same: ");
   custom_assert(G.coins == 0);
   printf("Checking if player 1's hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if player 2's discard pile has stayed the same: ");
   custom_assert(G.discardCount[player2] == 1);
   printf("Checking if player 2 discarded an ambassador card: ");
   custom_assert(G.discard[player2][0] == ambassador);

   // test #9: player to the left is player 2, has no cards at all, player 1 gains no benefit
   printf(" -- Test #9 --\n");
   G.handCount[player1] = 5;
   G.coins = 0;
   G.numActions = 1;
   G.deckCount[player2] = 0;
   G.discardCount[player2] = 0;

   tributeCardEffect(player1, &G);
  
   // show test results
   printf("Checking if numActions has stayed the same: ");
   custom_assert(G.numActions == 1);
   printf("Checking if coin count has stayed the same: ");
   custom_assert(G.coins == 0);
   printf("Checking if player 1's hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if player 2's discard pile has stayed the same: ");
   custom_assert(G.discardCount[player2] == 0);

   printf("Testing completed.\n");

   return 0;
}
