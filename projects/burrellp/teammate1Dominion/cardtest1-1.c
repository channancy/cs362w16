/*
 
 cardtest1-1.c
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 3
 Test for: Smithy (playSmithy() function)
 MODIFIED FOR smithyEffect() FOR TEAMMATE 1 CODE IN ASSIGNMENT 5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/*
 smithy effect(s):
 Draw three cards
 */


/*
 Items to test:
 Player who plays smithy has 2 more cards in hand (3 drawn - 1 discarded (smithy))
 Player who plays smithy has 3 fewer cards in deck
 Player who plays smithy has 1 more card in discard pile
 Last card in player's discard pile is smithy
 State does not change for other players
 */

int testSmithy(struct gameState *pre, struct gameState *post, int player);
int compareStatesSmithy(struct gameState *a, struct gameState *b, int player);

int main()
{
    //s1 will hold state after initialization, s2 will be state after draw card
    struct gameState *gs1 = malloc(sizeof(struct gameState));
    struct gameState *gs2 = malloc(sizeof(struct gameState));
    //Cards used in test instance of game
    int gameCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, remodel,
        village, baron, great_hall};
    int numPlayers;
    int seed = 55;
    int p;
    int passed = 0;
    
    //Run tests for all game sizes and for each player in game
    printf("Testing for smithyEffect beginning.\n");
    for (numPlayers = 2; numPlayers <= 4; numPlayers++)
    {
        printf("Testing a %d player game.\n", numPlayers);
        
        //Initialize game and test for success
        if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
        {
            printf("Game state failed to initialize. No testing completed.\n");
            return -1;
        }
        
        //Test for each player
        for (p = 0; p < numPlayers; p++)
        {
            printf("Testing for player %d playing smithy card.\n", p + 1);
            //A random card will be assigned to smith
            int card = rand() % 5;
            gs1->hand[p][card] = smithy;
            
            //Save state of game for comparison before and after playSmithy()
            memcpy(gs2, gs1, sizeof(struct gameState));
            smithyEffect(card, p, gs1);
            //Test changes that occurred during playSmith()
            if (!testSmithy(gs2, gs1, p))
                passed = -1;
            
        }
    }
    if (passed != -1)
        printf("PASS all tests for playSmithy().\n");
    
    
    return 0;
}


/************************************************************************************
 testSmithy()
 This function compares the game state before and after a call to playSmithy() to
 verify that the state changes were as expected.
 Tests for player who played card:
 Size of hand has increased by 2
 Size of discard has increased by 1
 Size of deck has decreased by 2
 Tests for other players:
 No change in state
 Other tests on state change:
 numPlayers is the same
 supplyCount of each card remains the same
 embargoTokens count for each card remains the same
 outpostPlayed and outpostTurn remain the same
 whoseTurn stays the same
 phase stays the same
 numActions stays the same
 numBuys stays the same
 playedCardCount increases by 1
 ************************************************************************************/
int testSmithy(struct gameState *pre, struct gameState *post, int player)
{
    int returnValue = 0;
    int numPlayers = pre->numPlayers;
    int i, j;
    int change;
    
    //Test for player who played card
    //Hand size should have increased by two cards
    if (post->handCount[player] != (pre->handCount[player] + 2))
    {
        change = post->handCount[player] - pre->handCount[player];
        printf("FAIL. Player's hand count did not increase by 2. It changed by %d.\n", change);
        returnValue = -1;
    }
    //Discard size should have increased by 1
    if (post->discardCount[player] != (pre->discardCount[player] + 1))
    {
        change = post->discardCount[player] - pre->discardCount[player];
        printf("FAIL. Player's discard count did not increase by 1. It changed by %d.\n", change);
        returnValue = -1;
    }
    //Size of deck should have decreased by 3
    if (post->deckCount[player] != (pre->deckCount[player] - 3))
    {
        change = pre->deckCount[player] - post->deckCount[player];
        printf("FAIL. Player's deck count did not decrease by 3. it changed by %d.\n", change);
        returnValue = -1;
    }
    
    //Tests for all other players
    for (i = 0; i < numPlayers; i++)
    {
        //Run tests for all players other than one who played card
        if (i != player)
        {
            //Test that deck count did not change
            if (post->deckCount[i] != pre->deckCount[i])
            {
                printf("FAIL. Player %d had invalid change in deck count.\n", i);
                returnValue = -1;
            }
            //Test that hand count did not change
            if (post->handCount[i] != pre->handCount[i])
            {
                printf("FAIL. Player %d had invalid change in hand count.\n", i);
                returnValue = -1;
            }
            //Test that discard count did not change
            if (post->discardCount[i] != pre->discardCount[i])
            {
                printf("FAIL. Player %d had invalid change in discard count.\n", i);
                returnValue = -1;
            }
            //Test that specific cards are still the same for all other players
            for (j = 0; j < MAX_HAND; j++)
            {
                if (post->hand[i][j] != pre->hand[i][j])
                {
                    printf("FAIL. Invalid change to card %d in player %d hand.\n", j, i + 1);
                    returnValue = -1;
                }
            }
            for (j = 0; j < MAX_DECK; j++)
            {
                if (post->deck[i][j] != pre->deck[i][j])
                {
                    printf("FAIL. Invalid change to card %d in player %d deck.\n", j, i + 1);
                    returnValue = -1;
                }
                if (post->discard[i][j] != pre->discard[i][j])
                {
                    printf("FAIL. Invalid change to card %d in player %d discard.\n", j, i + 1);
                    returnValue = -1;
                }
            }
        }
        
    }
    
    
    //General tests on the state change
    //numPlayers should be unchangd
    if (post->numPlayers != pre->numPlayers)
    {
        printf("FAIL. numPlayers changed.\n");
        returnValue = -1;
    }
    //supplyCount and embargoToken should stay the same for all cards
    for (i = 0; i < treasure_map + 1; i++)
    {
        if (post->supplyCount[i] != pre->supplyCount[i])
        {
            printf("FAIL. supplyCount changed for card %d.\n", i);
            returnValue = -1;
        }
        if (post->embargoTokens[i] != pre->embargoTokens[i])
        {
            printf("FAIL. embargoTokens changed for card %d.\n", i);
            returnValue = -1;
        }
    }
    //outpostPlayed should be unchanged
    if (post->outpostPlayed != pre->outpostPlayed)
    {
        printf("FAIL. outpostPlayed changed.\n");
        returnValue = 1;
    }
    //outpostTurn should be unchanged
    if (post->outpostTurn != pre->outpostTurn)
    {
        printf("FAIL. outpostTurn changed.\n");
        returnValue = -1;
    }
    //whoseTurn should be unchanged
    if (post->whoseTurn != pre->whoseTurn)
    {
        printf("FAIL. whoseTurn changed.\n");
        returnValue = -1;
    }
    //phase should be unchanged
    if (post->phase != pre->phase)
    {
        printf("FAIL. phase changed.\n");
        returnValue = -1;
    }
    //numActions should be unchanged
    if (post->numActions != pre->numActions)
    {
        printf("FAIL. numActions changed.\n");
        returnValue = -1;
    }
    //numBuys should be unchanged
    if (post->numBuys != pre->numBuys)
    {
        printf("FAIL. numBuys changed.\n");
        returnValue = -1;
    }
    //playedCardCount should increase by 1
    if (post->playedCardCount != pre->playedCardCount + 1)
    {
        printf("FAIL. playedCardCount changed.\n");
        returnValue = -1;
    }
    
    return returnValue;
}



