// unittest3.c
// This program performs unit testing on the ambassadorCardEffect() function in 
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
                 remodel, ambassador, village, mine, great_hall };

   // declare the game state
   struct gameState G;

   // declare arrays
   int coppers[MAX_HAND];
   int silvers[MAX_HAND];
   for (int i= 0; i<MAX_HAND; i++) {
      silvers[i] = silver;
      coppers[i] = copper;
   }

   printf("Begin testing ambassadorCardEffect():\n");

   // set up the game state for testing
   memset(&G, 23, sizeof(struct gameState)); // set the game state to 23 for all parameters
   int seed = 5; // arbitrary seed for RNG
   const int player1 = 0;
   const int player2 = 1;
   const int player3 = 2;
   const int player4 = 3;
   
   // set up test-specific conditions
   
   // test #1: player chooses to discard 2 coppper cards, other players gain 1 copper card each
   printf(" -- Test #1 --\n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = ambassador;
   G.discardCount[player1] = 0;
   G.discardCount[player2] = 0;
   G.supplyCount[copper] = 4;
   int choice1 = 0; // selected card is the first card in the player's hand, a copper card
   int choice2 = 2; // discard 2 copper
   int handPos = 4; // last card is the ambassador card

   ambassadorCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if player 1's hand count has decreased by 3: ");
   custom_assert(G.handCount[player1] == 2);
   printf("Checking if player 1's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player1] == 1);
   printf("Checking if player 1's discard pile now contains the Ambassador card: ");
   custom_assert(G.discard[player1][0] == ambassador);
   printf("Checking if supply of copper cards has increased by 1 (2 returned and 1 taken): ");
   custom_assert(G.supplyCount[copper] == 5);
   printf("Checking if player 2's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player2] == 1);
   printf("Checking if player 2's discard pile now has a copper card: ");
   custom_assert(G.discard[player2][0] == copper);

   // test #2: player chooses to discard 1 copper card, the other players gain 1 copper card each
   printf(" -- Test #2 --\n");
   initializeGame(4, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = ambassador;
   G.discardCount[player1] = 0;
   G.discardCount[player2] = 2;
   G.discardCount[player3] = 0;
   G.discardCount[player4] = 4;
   G.supplyCount[copper] = 10;
   choice1 = 1; // selected card is the second card in the player's hand, a copper card
   choice2 = 1; // discard 1 copper
   handPos = 4; // last card is the ambassador card

   ambassadorCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if player 1's hand count has decreased by 2: ");
   custom_assert(G.handCount[player1] == 3);
   printf("Checking if player 1's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player1] == 1);
   printf("Checking if supply of copper cards has decreased by 2 (1 returned and 3 taken): ");
   custom_assert(G.supplyCount[copper] == 8);
   printf("Checking if player 2's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player2] == 3);
   printf("Checking if player 2's discard pile now has a copper card: ");
   custom_assert(G.discard[player2][2] == copper);
   printf("Checking if player 3's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player3] == 1);
   printf("Checking if player 3's discard pile now has a copper card: ");
   custom_assert(G.discard[player3][0] == copper);
   printf("Checking if player 4's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player4] == 5);
   printf("Checking if player 4's discard pile now has a copper card: ");
   custom_assert(G.discard[player4][4] == copper);

   // test #3: player chooses to discard 2 copper cards but only has 1, nothing happens
   printf(" -- Test #3 -- \n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], silvers, sizeof(int) * (G.handCount[player1] - 2));
   G.hand[player1][3] = copper;
   G.hand[player1][4] = ambassador;
   G.discardCount[player1] = 0;
   G.discardCount[player2] = 0;
   G.supplyCount[copper] = 4;
   choice1 = 3; // selected card is the fourth card in the player's hand, a copper card
   choice2 = 2; // discard 2 coppers
   handPos = 4; // last card is the ambassador card

   ambassadorCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if player 1's hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if player 1's discard pile has stayed the same: ");
   custom_assert(G.discardCount[player1] == 0);
   printf("Checking if supply of copper cards has stayed the same: ");
   custom_assert(G.supplyCount[copper] == 4);
   printf("Checking if player 2's discard pile has stayed the same: ");
   custom_assert(G.discardCount[player2] == 0);

   // test #4: player chooses to discard the ambassador card itself, nothing happens
   printf(" -- Test #4 -- \n");
   initializeGame(2, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = ambassador;
   G.discardCount[player1] = 0;
   G.discardCount[player2] = 0;
   G.supplyCount[copper] = 4;
   choice1 = 4; // selected card is the ambassador card itself
   choice2 = 1; // discard 1 ambaassador
   handPos = 4; // selected card is the fourth card in the player's hand, a copper card

   ambassadorCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if player 1's hand count has stayed the same: ");
   custom_assert(G.handCount[player1] == 5);
   printf("Checking if player 1's discard pile has stayed the same: ");
   custom_assert(G.discardCount[player1] == 0);
   printf("Checking if supply of copper cards has stayed the same: ");
   custom_assert(G.supplyCount[copper] == 4);
   printf("Checking if player 2's discard pile has stayed the same: ");
   custom_assert(G.discardCount[player2] == 0);

   // test #5: player chooses to discard 1 card, but the supply does not have enough copper
   // cards for all other players to draw 1
   printf(" -- Test #5 --\n");
   initializeGame(4, k, seed, &G);
   G.handCount[player1] = 5;
   memcpy(G.hand[player1], coppers, sizeof(int) * (G.handCount[player1] - 1));
   G.hand[player1][4] = ambassador;
   G.discardCount[player1] = 0;
   G.discardCount[player2] = 2;
   G.discardCount[player3] = 0;
   G.discardCount[player4] = 4;
   G.supplyCount[copper] = 1;
   choice1 = 1; // selected card is the second card in the player's hand, a copper card
   choice2 = 1; // discard 1 copper
   handPos = 4; // last card is the ambassador card

   ambassadorCardEffect(choice1, choice2, player1, &G, handPos);

   // show test result
   printf("Checking if player 1's hand count has decreased by 2: ");
   custom_assert(G.handCount[player1] == 3);
   printf("Checking if player 1's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player1] == 1);
   printf("Checking if supply of copper cards has decreased to 0 (1 returned and 2 taken): ");
   custom_assert(G.supplyCount[copper] == 0);
   printf("Checking if player 2's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player2] == 3);
   printf("Checking if player 2's discard pile now has a copper card: ");
   custom_assert(G.discard[player2][2] == copper);
   printf("Checking if player 3's discard pile has increased by 1: ");
   custom_assert(G.discardCount[player3] == 1);
   printf("Checking if player 3's discard pile now has a copper card: ");
   custom_assert(G.discard[player3][0] == copper);
   printf("Checking if player 4's discard pile has stayed the same due to empty supply: ");
   custom_assert(G.discardCount[player4] == 4);

   printf("Testing completed.\n");

   return 0;
}
