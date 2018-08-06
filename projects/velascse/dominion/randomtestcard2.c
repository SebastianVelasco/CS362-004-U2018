#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// Global Variables to Count Number of Failures
int handFailure, deckFailure, discardCardFails, 
    drawCardFails, cardEffectFails, passes, actionFails;

void villageRandomCheck(int player, struct gameState* state)
{
    int i,j,ret,s,t,u;

    // Create and copy the gamestate that was passed in
    struct gameState before;
    memcpy(&before,state,sizeof(struct gameState));

    // Call the Smithy Card with no bonus
    ret = cardEffect(village, 0,0,0,state,0,0);

    // Manually Run Village Actions on copy of passed in game state
    s = drawCard(player, &before);

    // Add Actions
    before.numActions = before.numActions + 2;

    // Dicard Card
    j = discardCard(0, player, &before, 0);

    // Get Values before continuing
    int beforeDeckCount = before.deckCount[player];
    int beforeHandCount = before.handCount[player];
    int beforeDiscard = before.discardCount[player];
    int before_actions = before.numActions;

    // Get Values of deck post
    int afterDeckCount = state->deckCount[player];
    int afterHandCount = state->handCount[player];
    int afterDiscard = state->discardCount[player];
    int after_actions = state->numActions;

    int passed = 1;

    // Check Draw Card
    if ((s == -1 || t == -1 || u == -1) && (before.deckCount != 0))
    {
        drawCardFails++;
        passed = 0;
    }
    // Check Card Effect && Discard Card
    if(ret != 0)
    {
        cardEffectFails++;
        passed = 0;
    }
    // Discard Card Fails
    if((j != 0) || (beforeDiscard != afterDiscard))
    {
        discardCardFails++;
        passed = 0;
    }
    // Deck Count
    if (afterDeckCount != (beforeDeckCount))
    {
        deckFailure++;
        passed = 0;
    }
    // Check Hand
    if (afterHandCount != (beforeHandCount))
    {
        handFailure++;
        passed = 0;
    }
    // Check Actions
    if(before_actions != after_actions)
    {
        actionFails++;
        passed = 0;
    }

    // Check if all passed
    if (passed == 1)
    {
        passes++;
    }
}

int main()
{
    printf("~~~~~~~~~~~~~~~~~~~~  RANDOM TEST  ~~~~~~~~~~~~~~~~~~~~\n");
    printf("Checking Village Card here\n");

    // Set up variables
    int i, j, player;
    struct gameState G;

    // Begin with random tests over 10000 random iterations
    for(i = 0; i < 10000; i++)
    {
        // Fill gamestate G with random bytes
        for (j = 0; j < sizeof(struct gameState); j++) 
        {
            ((char*)&G)[j] = floor(Random() * 256);
        }

        // Randomly generate a "Sane" gamestate
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * (MAX_DECK-1));
        G.whoseTurn = player;

        // Check Smithy Using the Function
        villageRandomCheck(player,&G);
    }

    // END OF TESTING (upto 10000 * 3)
    int total_failures = handFailure + deckFailure + discardCardFails + drawCardFails + cardEffectFails + actionFails;

    printf("\n~~~~~~~~~~~~~~ RESULTS ~~~~~~~~~~~~~~~~~~~\n");
    printf("PASSED TESTS: %d\n",passes); // Means All tests passed the test
    printf("FAILED TESTS: %d\n",total_failures);

    if (total_failures == 0) 
    {
        printf (" ~~~~~~~~~~~~~~~ PASSED ALL RANDOM TEST ~~~~~~~~~~~~~~~~\n\n");
    }
    else 
    {
        printf("\n~~~~~~~~~~~~~~~~~ FAILURE REPORT ~~~~~~~~~~~~~~~~~~\n");
        printf("Discard failed: %d\n",discardCardFails);
        printf("Deck Count mismatch: %d\n",deckFailure);
        printf("Hand Count mismatch: %d\n",handFailure);
        printf("Draw Card Failures: %d\n",drawCardFails);
        printf("Card Effects Failures: %d\n",cardEffectFails);
        printf("Actions: %d\n", actionFails);
        printf ("***** FAILED RANDOM TEST *****\n\n");
    }
    printf("~~~~~~~~~~~~~~~~~~~~  END OF RANDOM TEST  ~~~~~~~~~~~~~~~~~~~~\n");

    printf("~~~~~~~~~~~~~~~~~~~~  COVERAGE  ~~~~~~~~~~~~~~~~~~~~\n\n");
}