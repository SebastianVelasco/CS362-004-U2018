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
    int ret_cost[12];
    int costs[] = {6, 4, 2, 3, 5, 5, 4, 4, 5, 4}; //Costs expected for each card in k
    int i;

    // Print to .out sheet
    printf("\n~~~~~ Unit Test 4: getCost() ~~~~~\n");
    printf("\nCheck costs for all cards in hand\nAre they Correct?\n");

    // Initialize the game
    int a = initializeGame(2, k, seed, &state);

    // Get the cost of each card
    for(i = 0; i < 10; i++)
    {
        ret_cost[i] = getCost(k[i]);
    }

    // Check to see if card values are correct
    int all_right = 1;
    for(i = 0; i < 5; i++)
    {
        int okay = 1;
        printf("\n%d\n", k[i]);
        if(ret_cost[i] != costs[i])
        {
            okay = 0;
            all_right = 0;
        }
        if(all_right == 1)
        {
        assertTrue(0,0);
        printf("Cost is correct\n");
        }
        else
        {
        assertTrue(0, 1);
        printf("Cost is Wrongwrong\n");
        }
    }

    if(all_right == 1)
    {
        assertTrue(0,0);
        printf("\nAll returned costs are correct\n");
    }
    else
    {
        assertTrue(0, 1);
        printf("\n One or more returned costs are wrong\n");
    }

    // Assert it is not, as it just started
    printf("\n~~~~~ End of Unit Test 4 ~~~~~\n");

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