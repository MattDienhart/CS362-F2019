// bug4_unit.c
// This program performs unit testing on the isGameOver() function
// when Sea Hag and Treasure Map supplies are empty per Bug #3.
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
   int k[10] = { adventurer, sea_hag, treasure_map, gardens, baron,
                 remodel, smithy, village, mine, great_hall };

   // declare the game state
   struct gameState G;

   printf("Begin testing the isGameOver() function:\n");

   // set up the game state for testing
   int seed = 5; // arbitrary seed for RNG

 
   // set up test-specific conditions
   
   // player attempts to trash an estate card and gain a province card
   printf(" -- Testing Bug #4 --\n");
   initializeGame(2, k, seed, &G);
   
   // set supply piles for all cards to 3
   int i;
   for (i=curse; i<=treasure_map; i++) {
      G.supplyCount[i] = 3;
   }

   // set supply count for Sea Hag, Treasure Map, and Adventurer to 0
   G.supplyCount[sea_hag] = 0;
   G.supplyCount[treasure_map] = 0;
   G.supplyCount[adventurer] = 0;

   // call the function to be tested
   int result;
   result = isGameOver(&G);

   // show test result
   printf("Checking if the game has ended due to supply depletion: ");
   custom_assert(result == 1);

   printf("Testing completed.\n");

   return 0;
}
