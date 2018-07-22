#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void assertTrue(int a, int b);

// Test Smithy

// This Tests whether or not the game is over
int main()
{
    int i;
    int seed = 5;
    int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy};

    struct gameState state, stateOG;

    printf("\n~~~~~~~~~~~~ Card Test 4: Adventurer() ~~~~~~~~~~~~~~~~~~\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&stateOG,23,sizeof(struct gameState)); //Check to see if it works

    initializeGame(2, k, seed, &state);

    // Copy original to compare
    memcpy(&stateOG, &state, sizeof(struct gameState));
    printf("\nHello\n");
    // Run tests for smithy
    cardEffect(adventurer, 0, 0, 0, &state, 0, 0);

    printf("\nChecking to see if tw cards have been added\n");
    int before = stateOG.handCount[0];
    int after = state.handCount[0];
    assertTrue(before+1, after); // Replaces smithy and adds additional 2

    int treasure_after, treasure_before;

    // Check treasure gained
    for(i =0; i < stateOG.handCount[0]; i++)
    {
        int card = stateOG.hand[0][i];
        if(card == copper || card == silver || card == gold)
        {
            treasure_before++;
        }
    }

    // Check treasure gained
    for(i =0; i < state.handCount[0]; i++)
    {
        int card = state.hand[0][i];
        if(card == copper || card == silver || card == gold)
        {
            treasure_after++;
        }
    }

    // Check to see if treasure cards gained == 2
    printf("\nAre there +2 treasure cards\n");
    assertTrue(before+2,after);

    // Check Discard Pile
    printf("\nChecking discard pile to make sure it was added\n");
    before = stateOG.discardCount[0];
    after = state.discardCount[0];
    assertTrue(before-1, after);

    // Check Victory Card Piles
    printf("\nChange to victory card piles?\n");
    printf("Province Pile\n");
    assertTrue(state.supplyCount[province],stateOG.supplyCount[province]);
    printf("Duchy Pile\n");
    assertTrue(state.supplyCount[duchy],stateOG.supplyCount[duchy]);
    printf("Estate Pile\n");
    assertTrue(state.supplyCount[estate],stateOG.supplyCount[estate]);

    // Kingdom Card Piles
    printf("\nNo change to kingdom card piles\n");
    int diff = 0;
    for (i = 0; i < 10; i++) {
        if(state.supplyCount[k[i]] != stateOG.supplyCount[k[i]])
        {
            diff == 1;
            break;
        }
    }

    if (diff == 1)
    {
        assertTrue(diff, 0);
    }
    else
    {
        assertTrue(diff, 0);
    }

    printf("\n~~~~~~~~~~~~~~~~ End Testing of Adventurer() ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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