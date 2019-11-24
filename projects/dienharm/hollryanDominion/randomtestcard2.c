// randomtestcard2.c
// This program performs random testing on the minionCardEffect() function in 
// "dominion.c".
//
// Author: Matt Dienhart
// Date: 11-16-2019

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
   int playerID;
   int j;
   int chosenCard;

   // game state variables
   struct gameState G;
   int k[10];
   int seed;
   int numPlayers;
   int player;
   int choice1;
   int choice2;
   int handPos;

   // variables for saving preconditions
   int minionCardInHand;
   int initActions;
   int initHandCount[MAX_PLAYERS];
   int initCoinCount;
   int initDeckCount[MAX_PLAYERS];
   int initDiscardCount[MAX_PLAYERS];

   printf("Starting random tests of the minionCardEffect() function:\n");

   while(state != 3) {
      tcCount ++;
      minionCardInHand = 0;
      handPos = 0;

      //memset(&G, 23, sizeof(struct gameState));

      // initialize random game state

      // populate the k array with random cards, making sure there are no duplicate elements
      for (i=0; i<10; i++) {
         chosenCard = 0;
         while (chosenCard == 0) {
            k[i] = rand() % 27; // choose a random card from the CARD enum
            chosenCard = 1;
            for (j=0; j<i; j++) {
               if (k[i] == k[j]) { // if the chosen card was already chosen earlier, try again
                  chosenCard = 0;
               }
            }
         }
      }

      numPlayers = 2 + (rand() % (MAX_PLAYERS - 1)); // choose a random number of players from 2 to MAX_PLAYERS
      player = rand() % numPlayers; // randomly choose the current player

      seed = 1 + (rand() % 10); // choose a random seed value from 1 to 10

      initializeGame(numPlayers, k, seed, &G); // initializes the game state

      choice1 = -10 + (rand() % 21); // "choice1" is a random integer from -10 to 10
      choice2 = -10 + (rand() % 21); // "choice2" is a random integer from -10 to 10
      G.numActions = -10 + (rand() % 21); // "numActions" is a random integer from -10 to 10
      G.coins = -10 + (rand() % 21); // "coins" is a random integer from -10 to 10
      G.whoseTurn = player;

      // set up each player with a randomized hand of cards
      for (playerID=0; playerID<numPlayers; playerID++) {
         G.handCount[playerID] = rand() % (MAX_HAND + 1); // random hand size 0 to MAX_HAND
         for (i=0; i<G.handCount[playerID]; i++) {
            G.hand[playerID][i] = rand() % 27; // get random card
            if (playerID == player && G.hand[playerID][i] == minion) {
               handPos = i; // set the hand position to the current player's minion card
               minionCardInHand = 1; // current player has a minion card
            }
         }
      }

      // set up each player with a randomized deck
      for (playerID=0; playerID<numPlayers; playerID++) {
         G.deckCount[playerID] = rand() % (MAX_DECK + 1); // random deck size 0 to MAX_DECK
         for (i=0; i<G.deckCount[playerID]; i++) {
            G.deck[playerID][i] = rand() % 27; // get random card
         }
      }

      // set up each player with a randomized discard pile
      for (playerID=0; playerID<numPlayers; playerID++) {
         G.discardCount[playerID] = rand() % (MAX_HAND + 1); // random discard size 0 to MAX_HAND
         for (i=0; i<G.discardCount[playerID]; i++) {
            G.discard[playerID][i] = rand() % 27; // get random card
         }
      }

      // save preconditions for later comparisons
      initActions = G.numActions;
      for (playerID=0; playerID<numPlayers; playerID++) {
         initHandCount[playerID] = G.handCount[playerID];
         initDeckCount[playerID] = G.deckCount[playerID];
         initDiscardCount[playerID] = G.discardCount[playerID];
      }
      initCoinCount = G.coins;

      /* Check input conditions to see if a new state will be visited.
       * We have four states that we want to make sure to visit at least
       * once each during the random testing. Once all states have been visited,
       * the loop will exit. */

      // print info for this loop iteration
      printf("Iteration %d: choice1 = %d, choice2 = %d, minionCardInHand = %d, state = %d\n", 
             tcCount, choice1, choice2, minionCardInHand, state);
      printf("Current player: %d, number of players: %d\n", player+1, numPlayers);

      // call test function
      minionCardEffect(choice1, choice2, player, &G, handPos);
 
      // state #1: player chooses to discard the minion card and gain 2 coins, it is valid
      if (choice1 != 0 && choice2 == 0 && minionCardInHand == 1) {
         // assertions to verify function behavior
         printf("Checking if numActions has increased by 1: ");
         custom_assert(G.numActions == (initActions + 1));
         printf("Checking if coin count has increased by 2: ");
         custom_assert(G.coins == (initCoinCount + 2));
         printf("Checking if hand count has decreased by 1: ");
         custom_assert(G.handCount[player] == (initHandCount[player] - 1));
         printf("Checking if current player's discard pile has increased by 1: ");
         custom_assert(G.discardCount[player] == (initDiscardCount[player] + 1));
         printf("Checking if discarded card was a minion card: ");
         custom_assert(G.discard[player][0] == minion);
 
         // if this is the first time this condition has occurred, advance the state
         if (state == 0) { state = 1; }
      }
      
      // state #2: player chooses to discard their hand, draw 4 cards, and others do the same
      else if (choice1 == 0 && choice2 != 0 && minionCardInHand == 1) {
         // assertions to verify function behavior
         printf("Checking if numActions has increased by 1: ");
         custom_assert(G.numActions == (initActions + 1));

         // check each player's hand size and discard size
         for (playerID=0; playerID<numPlayers; playerID++) {
            // determine how to do hand size assert based on how many cards the player has
            if (playerID == player) {
               if (initHandCount[playerID] >= 4 || (initHandCount[playerID]+
                   initDeckCount[playerID]+initDiscardCount[playerID]) >= 4) { 
                  printf("Checking if player %d's hand size is now 4: ", playerID+1);
                  custom_assert(G.handCount[playerID] == 4);
                  printf("Checking if player %d's old hand has been discarded: ", playerID+1);
                  if (initDeckCount[playerID] >= 4) {
                     custom_assert(G.discardCount[playerID] == 
                                   (initDiscardCount[playerID] + initHandCount[playerID]));
                  } else if ((initDeckCount[playerID] + initDiscardCount[playerID]) >= 4) {
                     custom_assert(G.discardCount[playerID] == initHandCount[playerID]);
                  } else {
                     custom_assert(G.discardCount[playerID] == 
                                   (initHandCount[playerID] - 
                                    (initDeckCount[playerID]+initDiscardCount[playerID])));
                  }
               } else {
                  printf("Checking if player %d has drawn new cards until running out: ", playerID+1);
                  custom_assert((G.handCount[playerID] == (initHandCount[playerID] +
                                initDeckCount[playerID] + initDiscardCount[playerID])) &&
                                (G.deckCount[playerID] == 0) && (G.discardCount[playerID] == 0));
               }
            } else {
               if (initHandCount[playerID] >=5) {
                  printf("Checking if player %d's hand size is now 4: ", playerID+1);
                  custom_assert(G.handCount[playerID] == 4);
                  printf("Checking if player %d's old hand has been discarded: ", playerID+1);
                  if (initDeckCount[playerID] >= 4) {
                     custom_assert(G.discardCount[playerID] == 
                                   (initDiscardCount[playerID] + initHandCount[playerID]));
                  } else if ((initDeckCount[playerID] + initDiscardCount[playerID]) >= 4) {
                     custom_assert(G.discardCount[playerID] == initHandCount[playerID]);
                  } else {
                     custom_assert(G.discardCount[playerID] == 
                                   (initHandCount[playerID] - 
                                    (initDeckCount[playerID]+initDiscardCount[playerID])));
                  }
               } else {
                  printf("Checking if player %d's hand size has stayed the same: ", playerID+1);
                  custom_assert(G.handCount[playerID] == initHandCount[playerID]);
                  printf("Checking if player %d's discard count has stayed the same: ", playerID+1);
                  custom_assert(G.discardCount[playerID] == initDiscardCount[playerID]);
               }
            }
         }  
         
         // if this is the first time this condition has occurred, advance the state
         if (state == 1) { state = 2; }
      }

      // state #3: player makes an invalid choice, nothing happens
      else if ((choice1 == 0 && choice2 == 0) || (choice1 != 0 && choice2 != 0) || 
           minionCardInHand == 0) {
         // assertions to verify function behavior
         printf("Checking if numActions has stayed the same: ");
         custom_assert(G.numActions == initActions);
         printf("Checking if coin count has stayed the same: ");
         custom_assert(G.coins == initCoinCount);

         // check each player's hand and discard pile
         for (playerID=0; playerID<numPlayers; playerID++) {
            printf("Checking if player %d's hand count has stayed the same: ", playerID+1);
            custom_assert(G.handCount[playerID] == initHandCount[playerID]);
            printf("Checking if player %d's discard count has stayed the same: ", playerID+1);
            custom_assert(G.discardCount[playerID] == initDiscardCount[playerID]);
         }

         // if this is the first time this condition has occurred, advance the state
         if (state == 2) { state = 3; }
      }

      // loop until all states have been visited at least once

   }

   printf("Testing complete!\n");

   return;
}

int main() {
   // seed the random number generator
   srand(time(NULL));

   // keep track of how long it takes to run the tests
   clock_t timer;
   double total_time;
   timer = clock(); // start the timer

   // start the random tests
   runtest();

   // determine the timer value and print it
   timer = clock() - timer;
   total_time = ((double)timer)/CLOCKS_PER_SEC; // time in seconds
   printf("The tests took a total of %f seconds.\n", total_time);

   return 0;
}
