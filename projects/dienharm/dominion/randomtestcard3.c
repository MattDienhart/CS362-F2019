// randomtestcard3.c
// This program performs random testing on the tributeCardEffect() function in 
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
   int nextPlayer;
   int fewCards;

   // variables for saving preconditions
   int initActions;
   int initHandCount[MAX_PLAYERS];
   int initCoinCount;
   int initDeckCount[MAX_PLAYERS];
   int initDiscardCount[MAX_PLAYERS];
   int revealedCardA;
   int revealedCardB;

   printf("Starting random tests of the tributeCardEffect() function:\n");

   while(state != 10) {
      tcCount ++;

      // initialize random game state
      
      // populate the k array with unique, randomly chosen cards
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
      printf("Current player: %d, number of players: %d\n", player+1, numPlayers);
      seed = 1 + (rand() % 10); // choose a random seed value from 1 to 10

      initializeGame(numPlayers, k, seed, &G); // initializes the game state

      if (player == numPlayers - 1) {
         nextPlayer = 0;
      } else {
         nextPlayer = player + 1;
      }

      G.numActions = -10 + (rand() % 21); // "numActions" is a random integer from -10 to 10
      G.coins = -10 + (rand() % 21); // "coins" is a random integer from -10 to 10
      G.whoseTurn = player;

      /* The fewCards variable is used to partition the test space. When randomly selected,
       * the fewCards variable will significantly increase the probability of small deck
       * sizes and small discard pile sizes. */
      fewCards = rand() % 2; // 1 = ON, 0 = OFF

      // set up each player with a randomized hand of cards
      for (playerID=0; playerID<numPlayers; playerID++) {
         if (fewCards) {
            G.handCount[playerID] = rand() % 3; // random hand size 0 to 2
         } else {
            G.handCount[playerID] = (rand() % (MAX_HAND + 1)); // random hand size 0 to MAX_HAND
         }
         for (i=0; i<G.handCount[playerID]; i++) {
            G.hand[playerID][i] = rand() % 27; // get random card
         }
      }

      // set up each player with a randomized deck
      for (playerID=0; playerID<numPlayers; playerID++) {
         if (fewCards) {
            G.deckCount[playerID] = rand() % 3; // random deck size 0 to 2
         } else {
            G.deckCount[playerID] = 1 + (rand() % MAX_DECK); // random deck size 1 to MAX_DECK
         }
         for (i=0; i<G.deckCount[playerID]; i++) {
            G.deck[playerID][i] = rand() % 27; // get random card
         }
      }

      // set up each player with a randomized discard pile
      for (playerID=0; playerID<numPlayers; playerID++) {
         if (fewCards) {
            G.discardCount[playerID] = rand() % 3; // random discard size 0 to 2
         } else {
            G.discardCount[playerID] = rand() % (MAX_HAND + 1); // random discard size 0 to MAX_HAND
         }
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

      // determine which cards will be revealed
      if (G.deckCount[nextPlayer] >= 2) {
         revealedCardA = G.deck[nextPlayer][G.deckCount[nextPlayer]-1];
         revealedCardB = G.deck[nextPlayer][G.deckCount[nextPlayer]-2];
      } else if (G.deckCount[nextPlayer] == 1 && G.discardCount[nextPlayer] == 1) {
         revealedCardA = G.deck[nextPlayer][G.deckCount[nextPlayer]-1];
         revealedCardB = G.discard[nextPlayer][G.discardCount[nextPlayer]-1];
      } else if (G.deckCount[nextPlayer] == 0 && G.discardCount[nextPlayer] == 2) {
         revealedCardA = G.discard[nextPlayer][G.discardCount[nextPlayer]-1];
         revealedCardB = G.discard[nextPlayer][G.discardCount[nextPlayer]-2];
      } else if (G.deckCount[nextPlayer] == 0 && G.discardCount[nextPlayer] == 1) {
         revealedCardA = G.discard[nextPlayer][G.discardCount[nextPlayer]-1];
         revealedCardB = -1;
      } else if (G.deckCount[nextPlayer] == 1 && G.discardCount[nextPlayer] == 0) {
         revealedCardA = G.deck[nextPlayer][G.deckCount[nextPlayer]-1];
         revealedCardB = -1; 
      } else {
         revealedCardA = -1; // no card to reveal, or card will come from shuffled discard pile
         revealedCardB = -1; // no card to reveal, or card will come from shuffled discard pile
      }

      /* Check input conditions to see if a new state will be visited.
       * We have four states that we want to make sure to visit at least
       * once each during the random testing. Once all states have been visited,
       * the loop will exit. */

      // print info for this loop iteration
      printf("Iteration %d: first revealed card = %d, second revealed card = %d, state = %d\n", 
             tcCount, revealedCardA, revealedCardB, state);
      printf("Current player: %d, next player: %d, total players: %d\n", player, nextPlayer,
             numPlayers);
      printf("Next player's deck size: %d\n", initDeckCount[nextPlayer]);

      // call test function
      tributeCardEffect(player, &G);
 
      // state #1: 2 of the same treasure card are revealed from the deck
      if (initDeckCount[nextPlayer] >= 2 && revealedCardA == revealedCardB &&
          (revealedCardA > 3 && revealedCardA <= 6)) {
         // assertions to verify function behavior
         printf("Checking if numActions has stayed the same: ");
         custom_assert(G.numActions == initActions);
         printf("Checking if coin count has increased by 2: ");
         custom_assert(G.coins == (initCoinCount + 2));
         printf("Checking if current player's hand count has stayed the same: ");
         custom_assert(G.handCount[player] == initHandCount[player]);
         printf("Checking if next player's discard pile has increased by 2: ");
         custom_assert(G.discardCount[nextPlayer] == (initDiscardCount[nextPlayer] + 2));
 
         // if this is the first time this condition has occurred, advance the state
         if (state == 0) { state = 1; }
      }
      
      // state #2: player to the left is player 1, 2 of the same action card are revealed
      if (initDeckCount[nextPlayer] >= 2 && revealedCardA == revealedCardB &&
               (revealedCardA > 6 && revealedCardB <= 26) && nextPlayer == 0) {
         // assertions to verify function behavior
         printf("Checking if numActions has increased by 2: ");
         custom_assert(G.numActions == (initActions + 2));
         printf("Checking if coin count has stayed the same: ");
         custom_assert(G.coins == initCoinCount);
         printf("Checking if current player's hand count has stayed the same: ");
         custom_assert(G.handCount[player] == initHandCount[player]);
         printf("Checking if next player's discard pile has increased by 2: ");
         custom_assert(G.discardCount[nextPlayer] == (initDiscardCount[nextPlayer] + 2));

         // if this is the first time this condition has occurred, advance the state
         if (state == 1) { state = 2; }
      }

      // state #3: 2 of the same victory card are revealed from the deck
      if (initDeckCount[nextPlayer] >= 2 && revealedCardA == revealedCardB &&
               (revealedCardA > 0 && revealedCardA <= 3)) {
         // assertions to verify function behavior
         printf("Checking if numActions has stayed the same: ");
         custom_assert(G.numActions == initActions);
         printf("Checking if coin count has stayed the same: ");
         custom_assert(G.coins == initCoinCount);
         printf("Checking if current player's hand count has increased by 2: ");
         custom_assert(G.handCount[player] == (initHandCount[player] + 2));
         printf("Checking if next player's discard pile has increased by 2: ");
         custom_assert(G.discardCount[nextPlayer] == (initDiscardCount[nextPlayer] + 2));
 
         // if this is the first time this condition has occurred, advance the state
         if (state == 2) { state = 3; }
      }

      // state #4: 1 victory card and 1 treasure card are revealed from the deck
      if (initDeckCount[nextPlayer] >= 2 &&
               (revealedCardA > 0 && revealedCardA <= 3) &&
               (revealedCardB > 3 && revealedCardB <= 6)) {
         // assertions to verify function behavior
         printf("Checking if numActions has stayed the same: ");
         custom_assert(G.numActions == initActions);
         printf("Checking if coin count has increased by 2: ");
         custom_assert(G.coins == (initCoinCount + 2));
         printf("Checking if current player's hand count has increased by 2: ");
         custom_assert(G.handCount[player] == (initHandCount[player] + 2));
         printf("Checking if next player's discard pile has increased by 2: ");
         custom_assert(G.discardCount[nextPlayer] == (initDiscardCount[nextPlayer] + 2));

         // if this is the first time this condition has occurred, advance the state
         if (state == 3) { state = 4; }
      }

      // state #5: 2 different treasure cards are revealed from the deck
      if (initDeckCount[nextPlayer] >= 2 && revealedCardA != revealedCardB &&
               (revealedCardA > 3 && revealedCardA <= 6) &&
               (revealedCardB > 3 && revealedCardB <= 6)) {
         // assertions to verify function behavior
         printf("Checking if numActions has stayed the same: ");
         custom_assert(G.numActions == initActions);
         printf("Checking if coin count has increased by 4: ");
         custom_assert(G.coins == (initCoinCount + 4));
         printf("Checking if current player's hand count has stayed the same: ");
         custom_assert(G.handCount[player] == initHandCount[player]);
         printf("Checking if next player's discard pile has increased by 2: ");
         custom_assert(G.discardCount[nextPlayer] == (initDiscardCount[nextPlayer] + 2));
 
         // if this is the first time this condition has occurred, advance the state
         if (state == 4) { state = 5; }
      }

      // state #6: 1 action card is revealed from the deck and 1 victory card is revealed from
      // the discard pile
      if (initDeckCount[nextPlayer] == 1 && initDiscardCount[nextPlayer] == 1 &&
               (revealedCardA > 6 && revealedCardA <= 26) &&
               (revealedCardB > 0 && revealedCardB <= 3)) {
         // assertions to verify function behavior
         printf("Checking if numActions has increased by 2: ");
         custom_assert(G.numActions == (initActions + 2));
         printf("Checking if coin count has stayed the same: ");
         custom_assert(G.coins == initCoinCount);
         printf("Checking if current player's hand count has increased by 2: ");
         custom_assert(G.handCount[player] == (initHandCount[player] + 2));
         printf("Checking if next player's discard pile has increased by 2: ");
         custom_assert(G.discardCount[nextPlayer] == (initDiscardCount[nextPlayer] + 2));

         // if this is the first time this condition has occurred, advance the state
         if (state == 5) { state = 6; }
      }

      // state #7: 1 treasure card is revealed from the deck, there are no other cards
      if (initDeckCount[nextPlayer] == 1 && initDiscardCount[nextPlayer] == 0 &&
               (revealedCardA > 3 && revealedCardA <= 6)) {
         // assertions to verify function behavior
         printf("Checking if numActions has stayed the same: ");
         custom_assert(G.numActions == initActions);
         printf("Checking if coin count has increased by 2: ");
         custom_assert(G.coins == (initCoinCount + 2));
         printf("Checking if current player's hand count has stayed the same: ");
         custom_assert(G.handCount[player] == initHandCount[player]);
         printf("Checking if next player's discard pile has increased by 1: ");
         custom_assert(G.discardCount[nextPlayer] == (initDiscardCount[nextPlayer] + 1));
 
         // if this is the first time this condition has occurred, advance the state
         if (state == 6) { state = 7; }
      }

      // state #8: 1 action card is revealed from the discard pile, there are no other cards
      if (initDeckCount[nextPlayer] == 0 && initDiscardCount[nextPlayer] == 1 &&
               (revealedCardA > 6 && revealedCardA <= 26)) {
         // assertions to verify function behavior
         printf("Checking if numActions has increased by 2: ");
         custom_assert(G.numActions == (initActions + 2));
         printf("Checking if coin count has stayed the same: ");
         custom_assert(G.coins == initCoinCount);
         printf("Checking if current player's hand count has stayed the same: ");
         custom_assert(G.handCount[player] == initHandCount[player]);
         printf("Checking if next player's discard pile has stayed at 1: ");
         custom_assert(G.discardCount[nextPlayer] == 1);

         // if this is the first time this condition has occurred, advance the state
         if (state == 7) { state = 8; }
      }

      // state #9: player to the left has no cards at all, current player gets no benefit
      if (initDeckCount[nextPlayer] == 0 && initDiscardCount[nextPlayer] == 0) {
         // assertions to verify function behavior
         printf("Checking if numActions has stayed the same: ");
         custom_assert(G.numActions == initActions);
         printf("Checking if coin count has stayed the same: ");
         custom_assert(G.coins == initCoinCount);
         printf("Checking if current player's hand count has stayed the same: ");
         custom_assert(G.handCount[player] == initHandCount[player]);
         printf("Checking if next player's discard pile has stayed the same: ");
         custom_assert(G.discardCount[nextPlayer] == initDiscardCount[nextPlayer]);

         // if this is the first time this condition has occurred, advance the state
         if (state == 8) { state = 9; }
      }

      // state #10: 2 of the same action card are revealed from the discard pile
      if (initDeckCount[nextPlayer] == 0 && initDiscardCount[nextPlayer] == 2 &&
               (revealedCardA > 6 && revealedCardA <= 26) && revealedCardA == revealedCardB) {
         // assertions to verify function behavior
         printf("Checking if numActions has increased by 2: ");
         custom_assert(G.numActions == (initActions + 2));
         printf("Checking if coin count has stayed the same: ");
         custom_assert(G.coins == initCoinCount);
         printf("Checking if current player's hand count has stayed the same: ");
         custom_assert(G.handCount[player] == initHandCount[player]);
         printf("Checking if next player's discard pile has stayed at 2: ");
         custom_assert(G.discardCount[nextPlayer] == 2);

         // if this is the first time this condition has occurred, advance the state
         if (state == 9) { state = 10; }
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
