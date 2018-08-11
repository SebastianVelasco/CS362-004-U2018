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
    int k[10] = { adventurer, gardens, great_hall, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy};

    struct gameState state, stateOG;

    printf("\n~~~~~~~~~~~~ Card Test 3: Great Hall() ~~~~~~~~~~~~~~~~~~\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&stateOG,23,sizeof(struct gameState)); //Check to see if it works

    initializeGame(2, k, seed, &state);

    // Copy original to compare
    memcpy(&stateOG, &state, sizeof(struct gameState));

    // Run tests for smithy
    cardEffect(great_hall, 0, 0, 0, &state, 0, 0);

    printf("\nChecking to see if one card has been added\n");
    int before = stateOG.handCount[0];
    int after = state.handCount[0];
    assertTrue(before, after); // Replaces smithy and adds additional 2

    printf("\nChecking deck count to make sure it is 1 card less\n");
    before = stateOG.deckCount[0];
    after = state.deckCount[0];
    assertTrue(before-1, after); // Took 3 cards from players pile

    // Checking Actions
    printf("\nChecking to see if action is plus 1\n");
    before = stateOG.numActions;
    after = state.numActions;
    assertTrue(before+1, after); // Replaces village

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

    printf("\n~~~~~~~~~~~~~~~~ End Testing of Great Hall() ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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