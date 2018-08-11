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
    int k[10] = { adventurer, gardens, smithy, village, minion, mine, cutpurse,
            sea_hag, tribute, embargo};

    struct gameState state, stateOG;

    printf("\n\n~~~~~~~~~~~~ Card Test 1: Smithy() ~~~~~~~~~~~~~~~~~~\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&stateOG,23,sizeof(struct gameState)); //Check to see if it works

    initializeGame(2, k, seed, &state);

    // Copy original to compare
    memcpy(&stateOG, &state, sizeof(struct gameState));

    // Run tests for smithy
    cardEffect(smithy, 0, 0, 0, &state, 0, 0);

    printf("\nChecking to see if three cards have been added\n");
    int before = stateOG.handCount[0];
    printf("Hand Before: %d\n",before);
    int after = state.handCount[0];
    printf("Hand After: %d\n",after);
    assertTrue(before+2, after); // Replaces smithy and adds additional 2

    printf("\nChecking deck count to make sure it is 3 cards less\n");
    before = stateOG.deckCount[0];
    printf("Deck Before: %d\n",before-3);
    after = state.deckCount[0];
    printf("Deck After: %d\n",after);
    assertTrue(before-3, after); // Took 3 cards from players pile

    // Check Discard Pile
    printf("\nChecking discard pile to make sure it was added\n");
    before = stateOG.discardCount[0];
    printf("Discard Before: %d\n",before);
    after = state.discardCount[0];
    printf("Deiscard After: %d\n",after);
    assertTrue(before-1, after);

    // Check Victory Card Piles
    printf("\nChange to victory card piles?");
    printf("\nProvince Pile\n");
    assertTrue(state.supplyCount[province],stateOG.supplyCount[province]);
    printf("\nDuchy Pile\n");
    assertTrue(state.supplyCount[duchy],stateOG.supplyCount[duchy]);
    printf("\nEstate Pile\n");
    assertTrue(state.supplyCount[estate],stateOG.supplyCount[estate]);

    // Kingdom Card Piles
    printf("\nNo change to kingdom card piles\n");
    int diff = 0;
    for (i = 0; i < 10; i++) {
        printf("\n%d\n", state.supplyCount[k[i]]);
        printf("%d\n", stateOG.supplyCount[k[i]]);
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

    printf("\n~~~~~~~~~~~~~~~~ End Testing of Smithy() ~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
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