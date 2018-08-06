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
int cardEffectFails, shuffleFails, drawCardFails, handCountFails, 
    deckCountFails, discardFails, treasureCountFails;

void advRandomCheck(int player, struct gameState* state)
{
    int beforeTreasureCount = 0;
    int afterTreasureCount = 0;

    int temporary_hand[MAX_HAND];
    int drawntreasure = 0;
    // game state variable to manually act on the functions actions
    struct gameState before;

    int cardDrawn, card;

    int ret;
    int s,t,i; // Stores to see if any returned with negative values to check for errors.
    int z = 0;
    // copy the passed in game state to before
    memcpy(&before,state,sizeof(struct gameState));

    // call the card effect function with the adventurerCard
    r = cardEffect(adventurer,0,0,0,state,0,0);
    if (r) // Check if any errors returned
    {
        cardEffectFails++;
    }

    // Perform adventurerCard actions and then compare the results (Copy of process from adventurer function)
    while(drawntreasure < 2) {
            if (before.deckCount[p] < 1) 
            {
                //if the deck is empty we need to shuffle discard and add to deck
                    s = shuffle(p, &before);
                    // check if shuffle failed
                    if (s == -1 && before.deckCount[p] >= 1) {
                      shuffleFails++;
                    }
            }
            t = drawCard(p, &before);
            // check if drawcard failed
            if (t == -1 && before.deckCount[p] != 0) 
            {
                drawCardFails++;
            }
            cardDrawn = before.hand[p][before.handCount[p] - 1];//top card of hand is most recently drawn card.
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            {
                drawntreasure++;
            }     
            else
            {
                    temporary_hand[z] = cardDrawn;
                    before.handCount[p]--; //this should just remove the top card (the most recently drawn one).
                    z++;
            }
    }
    while(z - 1 >= 0) {
            before.discard[p][before.discardCount[p]++] = temporary_hand[z - 1]; // discard all cards in play that have been drawn
            z = z - 1;
    }
    // Before Treasure Count
    for (i = 0; i < before.handCount[p]; i++) {
        before_ card = before.hand[p][i];
        if (before_card == copper || before_card == silver || before_card == gold) {
            beforeTreasureCount++;
        }

        after_card = before.hand[p][i];
        if (after_card == copper || after_card == silver || after_card == gold) {
            afterTreasureCount++;
        }

    }

    if(beforeTreasureCount != afterTreasureCount)
    {
        treasureCountFails++;
    }

    // Values before 
    int before_hand_count = before.handCount[p];
    int before_deck_count = before.deckCount[p];
    int before_discard_count = before.discardCount[p];
    
    // Values after
    int after_hand_count = after->handCount[p];
    int after_deck_count = after->deckCount[p];
    int after_discard_count = after->discardCount[p];
    
    // check if the hand and deck counts dont match up
    if(before_hand_count == after_hand_count)
    {
        handCountFails++;
    }
    if(before_deck_count == after_deck_count)
    {
        deckCountFails++;
    }
    if(before_deck_count == after_deck_count)
    {
        discardFails++;
    }
}

int main()
{
    printf("~~~~~~~~~~~~~~~~~~~~  RANDOM TEST  ~~~~~~~~~~~~~~~~~~~~\n");
    printf("Checking Adventurer Card here\n");

    // Set up variables
    int i, j, player;
    int treasure = {gold, silver, copper};
    int mumTreasures;

    cardEffectFails = shuffleFails = drawCardFails = handCountFails = treasureCountFails = 0;

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

        G.deckCount[player] = floor(Random() * ((MAX_DECK - 5) + 1) + 5); // Must have at least 5 cards 
        number_of_treasures = floor(Random() * ((G.deckCount[player] - 5) + 1) + 5);

        // Random entry of treasure cards
        for(j = 0; j < number_of_treasures; j++)
        {
            int random = rand() % 3;
            G.deck[player] = treasures[random];
        }

        // Set up additional variables
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * ((MAX_HAND - 5) + 1) + 5);
        G.whoseTurn = player;

        // Check Smithy Using the Function
        advRandomCheck(player,&G);
    }

    // END OF TESTING (upto 10000 * 3)
    total_failures = handFailure + deckFailure + discardFailure;

    printf("\n~~~~~~~~~~~~~~ RESULTS ~~~~~~~~~~~~~~~~~~~\n");
    printf("PASSED TESTS: %d\n",passes); // Means All tests passed the test
    printf("FAILED TESTS: %d\n",total_failures);

    if (total_failures == 0) {
        printf (" ~~~~~~~~~~~~~~~ PASSED ALL RANDOM TEST ~~~~~~~~~~~~~~~~\n\n");
    }
    else {
        printf("\n~~~~~~~~~~~~~~~~~ FAILURE REPORT ~~~~~~~~~~~~~~~~~~\n");
        printf("Discard failed: %d\n",discardFailure);
        printf("Deck Count mismatch: %d\n",deckFailure);
        printf("Hand Count mismatch: %d\n",handFailure);
        printf ("***** FAILED RANDOM TEST *****\n\n");
    }
    printf("~~~~~~~~~~~~~~~~~~~~  END OF RANDOM TEST  ~~~~~~~~~~~~~~~~~~~~\n");

    printf("~~~~~~~~~~~~~~~~~~~~  COVERAGE  ~~~~~~~~~~~~~~~~~~~~\n\n");
}