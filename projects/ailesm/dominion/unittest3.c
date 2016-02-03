#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define TEST "getCost"

int getRealCost(int i)
{
    if (i == curse) {
            return 0;
        } else if (i == estate) {
            return 2;
        } else if (i == duchy) {
            return 5;
        } else if (i == province) {
            return 8;
        } else if (i == copper) {
            return 0;
        } else if (i == silver) {
            return 3;
        } else if (i == gold) {
            return 6;
        } else if (i == adventurer) {
            return 6;
        } else if (i == council_room) {
            return 5;
        } else if (i == feast) {
            return 4;
        } else if (i == gardens) {
            return 4;
        } else if (i == mine) {
            return 5;
        } else if (i == remodel) {
            return 4;
        } else if (i == smithy) {
            return 4;
        } else if (i == village) {
            return 3;
        } else if (i == baron) {
            return 4;
        } else if (i == great_hall) {
            return 3;
        } else if (i == minion) {
            return 5;
        } else if (i == steward) {
            return 3;
        } else if (i == tribute) {
            return 5;
        } else if (i == ambassador) {
            return 3;
        } else if (i == cutpurse) {
            return 4;
        } else if (i == embargo) {
            return 2;
        } else if (i == outpost) {
            return 5;
        } else if (i == salvager) {
            return 4;
        } else if (i == sea_hag) {
            return 4;
        } else if (i == treasure_map) {
            return 4;
        } else {
            return -1;
        }
}

int main() {
    int i, p, randomCard;
    int seed = 1000;
    int numPlayers = 2;
    int r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState GTest;
    int handRandom, deckRandom;
    
    printf("Testing %s()\n", TEST);
    
    for (p = 0; p < numPlayers; p++) {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        assert(initializeGame(numPlayers, k, seed, &G) == 0);
        
        printf("Testing player %d hand card cost\n", p );
        handRandom = rand() % MAX_HAND;
        G.handCount[p] = handRandom;
        for (i = 0; i < handRandom; i++) {
            randomCard = rand() % 27;
            G.hand[p][i] = randomCard;
            assert(getCost(G.hand[p][i]) == getRealCost(randomCard));
        }
        printf("Testing player %d deck card cost\n", p );
        deckRandom = rand() % MAX_DECK;
        G.deckCount[p] = deckRandom;
        for (i = 0; i < deckRandom; i++) {
            randomCard = rand() % 27;
            G.deck[p][i] = randomCard;
            assert(getCost(G.deck[p][i]) == getRealCost(randomCard));
        }
    }
    
    printf("All test passed for getCost() \n");
    
    return 0;
}