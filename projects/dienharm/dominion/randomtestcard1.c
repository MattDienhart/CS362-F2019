// randomtestcard1.c
// This program performs random testing on the baronCardEffect() function in 
// "dominion.c".
//
// Author: Matt Dienhart
// Date: 11-14-2019

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void runtest() {
   int tcCount = 0; // the tcCount variable keeps track of loop iterations
   int state = 0;  // the state variable is used to track coverage progress
   int i;

   // game state variables
   struct gameState G;
   int k[10];
   int seed;
   int player;
   int choice;

   // variables for saving preconditions
   int estateCardInHand;
   int estateCardInSupply;
   int initBuys;
   int initHandCount;
   int initCoinCount;
   int initDiscardCount;
   int initEstateSupplyCount;

   printf("Starting random tests of the baronCardEffect() function:\n");

   while(state != 5) {
      tcCount ++;
      estateCardInHand = 0;
      estateCardInSupply = 0;

      // initialize random game state
      for (i=0; i<10; i++) {
         k[i] = rand() % 27; // choose a random card from the CARD enum
      }
      player = rand() % MAX_PLAYERS; // randomly choose the current player
      seed = 1 + (rand() % 10); // choose a random seed value from 1 to 10

      initializeGame(MAX_PLAYERS, k, seed, &G); // initializes the game state

      choice = -10 + (rand() % 21); // "choice" is a random integer from -10 to 10
      G.numBuys = -10 + (rand() % 21); // "numBuys" is a random integer from -10 to 10
      G.coins = -10 + (rand() % 21); // "coins" is a random integer from -10 to 10

      G.handCount[player] = -10 + (rand() % (MAX_HAND + 11)); // random hand size -10 to MAX_HAND
      for (i=0; i<G.handCount[player]; i++) {
         G.hand[player][i] = rand() % 27; // get random card
      }

      G.discardCount[player] = -10 + (rand() % (MAX_HAND + 11));
      for (i=0; i<G.discardCount[player]; i++) {
         G.discard[player][i] = rand() % 27; // get random card
      }

      G.supplyCount[estate] = -10 + (rand() % 101); // random amount of estate cards in supply 

      // save preconditions for later comparisons
      initBuys = G.numBuys;
      initHandCount = G.handCount[player];
      initCoinCount = G.coins;
      initDiscardCount = G.discardCount[player];
      initEstateSupplyCount = G.supplyCount[estate];

      /* Check input conditions to see if a new state will be visited.
       * We have four states that we want to make sure to visit at least
       * once each during the random testing. Once all states have been visited,
       * the loop will exit. */

      // check if the player has an estate card in their hand
      for (i=0; i<G.handCount[player]; i++) {
         if (G.hand[player][i] == estate) {
            estateCardInHand = 1;
            break;
         }
      }

      // check if the supply has any estate cards in it
      if (G.supplyCount[estate] > 0) {
         estateCardInSupply = 1;
      }

      // print info for this loop iteration
      printf("Iteration %d: choice = %d, estateCardInHand = %d, estateCardInSupply = %d, state = %d\n", 
             tcCount, choice, estateCardInHand, estateCardInSupply, state);

      // call test function
      baronCardEffect(choice, player, &G);
 
      // state #1: player chooses to discard an estate card, and it is valid
      if (choice > 0 && estateCardInHand == 1) {
         // assertions to verify function behavior
         printf("Checking if numBuys has increased by 1: ");
         custom_assert(G.numBuys == (initBuys + 1));
         printf("Checking if coin count has increased by 4: ");
         custom_assert(G.coins == (initCoinCount + 4));
         printf("Checking if hand count has decreased by 1: ");
         custom_assert(G.handCount[player] == (initHandCount - 1));
 
         // if this is the first time this condition has occurred, advance the state
         if (state == 0) { state = 1; }
      }
      
      // state #2: player chooses to gain an estate card from supply, and it is valid
      if (choice <= 0 && estateCardInSupply == 1) {
         // assertions to verify function behavior
         printf("Checking if numBuys has increased by 1: ");
         custom_assert(G.numBuys == (initBuys + 1));
         printf("Checking if player's discard count has increased by 1: ");
         custom_assert(G.discardCount[player] == (initDiscardCount + 1));
         printf("Checking if gained card is an estate card: ");
         custom_assert(G.discard[player][0] == estate);
         printf("Checking if estate card supply has decreased by 1: ");
         custom_assert(G.supplyCount[estate] == (initEstateSupplyCount - 1));

         // if this is hte first time this condition has occurred, advance the state
         if (state == 1) { state = 2; }
      }

      // state #3: player chooses to discard an estate card, but does not have one
      if (choice > 0 && estateCardInHand == 0) {
         // assertions to verify function behavior
         printf("Checking if numBuys has stayed the same: ");
         custom_assert(G.numBuys == initBuys);
         printf("Checking if coin count has stayed the same: ");
         custom_assert(G.coins == initCoinCount);
         printf("Checking if hand count has stayed the same: ");
         custom_assert(G.handCount[player] == initHandCount);

         // if this is the first time this condition has occurred, advance the state
         if (state == 2) { state = 3; }
      }

      // state #4: player chooses to gain an estate card from supply, but there is only one left
      if (choice <= 0 && estateCardInSupply == 1 && G.supplyCount[estate] == 1) {
         // assertions to verify function behavior
         printf("Checking if numBuys has increased by 1: ");
         custom_assert(G.numBuys == (initBuys + 1));
         printf("Checking if player's discard count has increased by 1: ");
         custom_assert(G.discardCount[player] == (initDiscardCount + 1));
         printf("Checking if gained card is an estate card: ");
         custom_assert(G.discard[player][0] == estate);
         printf("Checking if estate card supply is now 0: ");
         custom_assert(G.supplyCount[estate] == 0);

         // if this is the first time this condition has occurred, advance the state
         if (state == 3) { state = 4; }
      }

      // state #5: player chooses to gain an estate card from supply, but there are none left
      if (choice <= 0 && estateCardInSupply == 0) {
         // assertions to verify function behavior
         printf("Checking if numBuys has stayed the same: ");
         custom_assert(G.numBuys == initBuys);
         printf("Checking if player's discard count has stayed the same: ");
         custom_assert(G.discardCount[player] == initDiscardCount);
         printf("Checking if estate card supply has stayed the same: ");
         custom_assert(G.supplyCount[estate] == initEstateSupplyCount);

         // if this is the first time this condition has occurred, advance the state
         if (state == 4) { state = 5; }
      }

      // loop until all states have been visited at least once

   }

   printf("Test complete!\n");

   return;
}

int main() {
   // seed the random number generator
   srand(time(NULL));

   // start the random tests
   runtest();

   return 0;
}
