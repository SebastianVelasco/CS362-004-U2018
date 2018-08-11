#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void assertTrue(int a, int b);

// This Tests whether or not the game is over
int main()
{
       // Initialize values to get game started
       struct gameState G;
       int seed = 5;
       int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
             sea_hag, tribute, smithy};

       // Print to .out sheet
       printf("\n~~~~~ Unit Test 1: isGameOver() ~~~~~\n");

       // Initialize the game
       initializeGame(2, k, seed, &G);

       // check if game is over
       int end = isGameOver(&G);
 
       // Assert it is not, as it just started

       assertTrue(end, 0);
       printf("\n~~~~~ End of Unit Test 1 ~~~~~\n");

       return 0;
}

 

void assertTrue(int a, int b)
{
       if (a == b)
       {
             printf("Test: Passed\n");
       }
       else
       {
             printf("Test: Failed\n");
       }

}