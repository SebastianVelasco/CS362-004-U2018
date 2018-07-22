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
    struct gameState state;
    int seed = 5;
    int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy};
    int i, j, status;

    // Print to .out sheet
    printf("\n~~~~~ Unit Test 3: updateCoins() ~~~~~\n");

    // Check if updateCoins is updating the coins
    state.handCount[0] = 10;
    
    printf("\nStarting with Copper\n");
    printf("\nExpecting: 10 coins\n");
    // Start with copper
    for(i = 0; i < 10; i ++)
    {
        state.hand[0][i] = copper;
    }
    updateCoins(0, &state, 0);
    assertTrue(state.coins, 10);

    printf("\nNow Silver\n");
    printf("\nExpecting: 20 coins\n");
    // Start with copper
    for(i = 0; i < 10; i ++)
    {
        state.hand[0][i] = silver;
    }
    updateCoins(0, &state, 0);
    assertTrue(state.coins, 20);

    printf("\nFinally Gold\n");
    printf("\nExpecting: 30 coins\n");
    // Start with copper
    for(i = 0; i < 10; i ++)
    {
        state.hand[0][i] = gold;
    }
    updateCoins(0, &state, 0);
    assertTrue(state.coins, 30);

    printf("\nFinally a Mix\n");
    printf("\nExpecting: 10 coins\n");
    // Start with copper
    for(i = 0; i < 10; i ++)
    {
        if(i % 2 == 0)
        {
            state.hand[0][i] = copper;
        }
        else
        {
            state.hand[0][i] = gold;
        }
        
    }
    updateCoins(0, &state, 0);
    assertTrue(state.coins, 20);

    printf("\n~~~~~ End of Unit Test 3 ~~~~~\n");

    return 0;
}

 
void assertTrue(int a, int b)
{
       if (a == b)
       {
             printf("\nTest: Passed\n");
       }
       else
       {
             printf("\nTest: Failed\n");
       }

}