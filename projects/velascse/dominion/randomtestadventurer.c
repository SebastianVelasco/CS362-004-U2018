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
int handFailure, deckFailure, discardCardFails, treasureFails, 
    drawCardFails, cardEffectFails, passes, shuffleFails, actionFails;

void advRandomCheck(int player, struct gameState* state)
{
    int i,j,ret,s,t,u, z = 0;
    int cardDrawn, card, drawnTreasure = 0;
    int temphand[MAX_HAND];

    // Create and copy the gamestate that was passed in
    struct gameState before;
    memcpy(&before,state,sizeof(struct gameState));

    // Call the Smithy Card with no bonus
    ret = cardEffect(adventurer, 0,0,0,state,0,0);

    // Manually Run Adventurer Actions on copy of passed in game state
    while(drawnTreasure < 2)
    {
        //printf("DrawnTreasure: %d\n",drawnTreasure);
        if(before.deckCount[player] < 1) // Shuffle Deck
        {
            s = shuffle(player, &before);
            if(s == -1) // Shuffle Problems
            {
                shuffleFails++;
            }
        }
        t = drawCard(player, &before);
        if (t==-1) // check for issues
        {
            drawCardFails++;
        }
        //Top Card is most recently drawn
        cardDrawn = before.hand[player][before.handCount[player] - 1];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
        {
            drawnTreasure++; 
        }
        else
        {
            temphand[z] = cardDrawn;
            // Remove top card
            before.handCount[player]--;
            z++;
        }

        while(z - 1  >= 0)
        {
            before.discard[player][before.discardCount[player]++] = temphand[z-1];
            z--;
        }
    }

    // Get the treasure counts
    int before_tc = 0;
    int after_tc = 0;
    // Before
    for(j = 0; j < before.handCount[player]; j++)
    {
        card = before.hand[player][j];
        if (card == copper || card == silver || card == gold)
        {
            before_tc++;
        }
    }
    // After
    for(j = 0; j < state->handCount[player]; j++)
    {
        card = state->hand[player][j];
        if (card == copper || card == silver || card == gold)
        {
            before_tc++;
        }
    }

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

    // Check Treause Count
    if(before_tc != after_tc)
    {
        treasureFails++;
        passed = 0;
    }
    // Check Card Effect && Discard Card
    if(ret != 0)
    {
        cardEffectFails++;
        passed = 0;
    }
    // Discard Card Fails
    if((beforeDiscard != afterDiscard))
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

    // Check if all passed
    if (passed == 1)
    {
        passes++;
    }
}

int main()
{
    printf("~~~~~~~~~~~~~~~~~~~~  RANDOM TEST  ~~~~~~~~~~~~~~~~~~~~\n");
    printf("Checking Adventurer Card\n");

    // Set up variables
    int i, j, player = 0 ;
    struct gameState G;
    int treasures[] = {copper,silver,gold};
    srand(time(NULL));

    // Begin with random tests over 10000 random iterations
    for(i = 0; i < 10000; i++)
    {
        //printf("Iteration: %d\n", i);
        // Fill gamestate G with random bytes
        for (j = 0; j < sizeof(struct gameState); j++) 
        {
            ((char*)&G)[j] = floor(Random() * 256);
        }

        // Randomly generate a "Sane" gamestate
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * ((MAX_DECK - 3) + 1) + 3);
        int treasureAmount = floor(Random() * ((G.deckCount[player] - 3) + 1) + 3);
        // Add Treasure to deck
        for(j = 0; j < treasureAmount; j++)
        {
            int random = rand() % 3;
            G.deck[player][j] = treasures[random];
        }

        G.discardCount[player] = 0;
        G.handCount[player] = floor(Random() * ((MAX_HAND - 3) + 1) + 3);
        G.whoseTurn = player;

        // Check Smithy Using the Function
        advRandomCheck(player,&G);
    }

    // END OF TESTING (upto 10000 * 3)
    int total_failures = handFailure + deckFailure + discardCardFails + drawCardFails + cardEffectFails + treasureFails;

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
        printf("Treasure Failures: %d\n",treasureFails);
        printf ("***** FAILED RANDOM TEST *****\n\n");
    }
    printf("~~~~~~~~~~~~~~~~~~~~  END OF RANDOM TEST  ~~~~~~~~~~~~~~~~~~~~\n");

    printf("~~~~~~~~~~~~~~~~~~~~  COVERAGE  ~~~~~~~~~~~~~~~~~~~~\n\n");
}