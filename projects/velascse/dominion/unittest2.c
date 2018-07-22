#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void assertTrue(int a, int b);

int main()
{
    // Initialize values to get game started
    struct gameState state;
    int seed = 5;
    int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy};
    int i;

    int pre_shuffle[12];
    int post_shuffle[12];

    initializeGame(2, k, seed, &state);
        
    // Print to .out sheet
    printf("\n~~~~~ Unit Test 2: shuffle() ~~~~~\n");
    printf("Is the deck being shuffled\n");

    // Test 0 cards in deck
    printf("\nPlayer deck count == 0\n");
    state.deckCount[0] = 0;
    int ret = shuffle(0, &state);
    assertTrue(ret, -1); 

    // Check that deck is shuffled with 10 cards
    printf("\nPlayer deck count == 10");
    printf("\nWill the deck shuffle?\n");
    state.deckCount[0] = 10;
    ret = shuffle(0, &state);
    // Store Deck before hand
    for(i = 0; i<10;i++)
    {
        pre_shuffle[i] = state.deck[0][i];
    }
    //Shuffle Deck and Re store cards
    shuffle(0,&state);
    for(i = 0; i<10;i++)
    {
        post_shuffle[i] = state.deck[0][i];
    }

    // Check the next each card to see if any are different
    int diff = 0; 
    for(i = 0; i < 10; i++)
    {
        if(post_shuffle[i]!= pre_shuffle[i])
        {
            diff = 1;
            break;
        }
    }

    if(diff == 1) // Different
    {
        assertTrue(1, 1);
    }
    else // Not different
    {
        assertTrue(0,1);
    }

    printf("\n~~~~~ End of Unit Test 2 ~~~~~\n");
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