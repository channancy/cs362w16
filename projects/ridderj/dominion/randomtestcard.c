/* -----------------------------------------------------------------------
 * Testing baron card
 Basic requirements of smithy card
   1)Increase current players hand by 1 card
   2)Actions increased by 2
 * -----------------------------------------------------------------------
 */
 
 /*
 -started off testing number of buys

-Need to update Hand so its not 0
 
countNum: 337 Deck: 74 Hand: 0     Player 0 number of buys = 16,expected 18
randomtestcard: randomtestcard.c:141: main: Assertion `G.numBuys == (numBuysRandom+1)' failed.
make: *** [randomtestcard.out] Aborted (core dumped)
make: *** Deleting file `randomtestcard.out'

-this never tested

 102205:  991:	  else if (p > state->handCount[currentPlayer]){
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  992:	    if(DEBUG) {
        -:  993:	      printf("No estate cards in your hand, invalid choice\n");
        -:  994:	      printf("Must gain an estate if there are any\n");
        -:  995:	    }
    #####:  996:	    if (supplyCount(estate, state) > 0){
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  997:	      gainCard(estate, state, 0, currentPlayer);
call    0 never executed
    #####:  998:	      state->supplyCount[estate]--;//Decrement estates
    #####:  999:	      if (supplyCount(estate, state) == 0){
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####: 1000:		isGameOver(state);
call    0 never executed
        -: 1001:	      }
        -: 1002:	    }
    #####: 1003:	    card_not_discarded = 0;//Exit the loop
        -: 1004:	  }

        
        
      TEST START---------------------------------
TEST NUM: 355 Deck: 11 Hand: 2 Discard: 51 Player 3
GET ESTATE CARD---
Coins = 1 ,expected 1
Number of buys = 9,expected 9
Estate Supply Count = 0 ,expected -1
TEST FAIL
Hand Supply Count = 2 ,expected 2
Discard Supply Count = 51 ,expected 52
randomtestcard: randomtestcard.c:261: main: Assertion `G.discardCount[G.whoseTurn] == discardRandom+1' failed.
make: *** [randomtestcard.out] Aborted (core dumped)
make: *** Deleting file `randomtestcard.out'



TEST START---------------------------------
TEST NUM: 446 Deck: 39 Hand: 73 Discard: 97 Player 2
ESTATE CARD NOT FOUND---
Coins = 20 ,expected 20
Number of buys = 7,expected 7
Estate Supply Count = 0 ,expected 0
Deck Supply Count = 39 ,expected 39
Hand Supply Count = 73 ,expected 72
TEST FAIL
Discard Supply Count = 97 ,expected 98
randomtestcard: randomtestcard.c:342: main: Assertion `G.discardCount[G.whoseTurn] == discardRandom+1' failed.

        
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <limits.h>

#define DEBUG 1

int main() {
    int i;
    int j;
    int l;
    //Used to print out correct name of card being tested in printf statement.
    const char* cardNames[] =
    {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
      "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
     "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map" };
    int countNum = 0;
    int coinRandom;
    int supplyRandomEstate;
    int randomNum;
    int deckRandom;
    int handRandom;
    int discardRandom;
    int numBuysRandom;
    int locOfBaron;
    int nameCards[MAX_HAND][MAX_HAND];
    int testAllCards;
    int deckCards;
    int handCards;
    int discardCards;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, t;
    int countCopper = 0;
    int whoseTurnIsIt = 0;
    int smithyFound = 0;
    int supplyCountCheck = 0;
    int treasure[3] = {4,5,6};
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int pointCards[6] = {0,1,2,3,16,10}; //Used to orginize point cards used
    int pointValue[6] = {-1,1,3,6,1,0}; //Used to orginize the point values that go with pointcards
    int score; //keeps return number for fullDeckCount(p, allCards, &G)
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG, sizeS;
    int totalCards = 5;
    //Make Array called nameCards, that holds decks full of same card name
    for (i = 0; i < MAX_HAND; i++) {
       for (j = 0; j < MAX_HAND; j++) {
      nameCards[i][j] = i;
       }
    }
    

     SelectStream(2);
     PutSeed(3);
    
    
    //printf ("TESTING cutpurse card:%d \n\n", INT_MAX);
    
   
    
    while(countNum < 100000){ //Stops testing after a certain number of attemtps
    if(DEBUG)
      printf("\nTEST START---------------------------------\n");

          //Setup game, number of players, whose turn is it-----------------------------
          seed = floor(Random()*2147483646); //Random see for initializeGame state
          numPlayer = floor(Random()*3) + 2;
          memset(&G, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
          G.whoseTurn = floor(Random()*numPlayer); //set current player
          
          
 
               
          
          
          
          //Cards in DECK SETUP------------------------------------------------
          deckRandom = floor(Random()*100);
          for (i = 0; i < deckRandom; i++) {
            G.deck[G.whoseTurn][i] = floor(Random()*27); 
          }
          //printf("What is deckRandom: %d\n",deckRandom);
          G.deckCount[G.whoseTurn] = deckRandom;
          
          
          
          
          
          
          //Cards in HAND SETUP------------------------------------------------
          //Fill hand with 1 baron cards, maybe 1 estate
          handRandom = floor((Random()*100)+2);
          for (i = 0; i < handRandom; i++) {
            randomNum = floor(Random()*27);
            if(randomNum != estate) { //make sure inital hand never gets an estate, it will be added later
               G.hand[G.whoseTurn][i] = 2;//just make it a duchy card
            } else { G.hand[G.whoseTurn][i] = randomNum; }
          }
          //Make sure 1 baron is in hand
          //G.hand[G.whoseTurn][locOfBaron] = baron;
          G.hand[G.whoseTurn][0] = baron;
          G.hand[G.whoseTurn][1] = floor(Random()*2); //Does player have estate card in hand. 
          G.handCount[G.whoseTurn] = handRandom;
          
          
          
          
          
          
          //Cards in DISCARD SETUP------------------------------------------------
          //Cards in discard deck
          discardRandom = floor(Random()*100);
          for (i = 0; i < discardRandom; i++) {
            G.deck[G.whoseTurn][i] = floor(Random()*27); 
          }
          G.discardCount[G.whoseTurn] = discardRandom;
          
          
          
          
          
          //SETUP COINS------------------------------------------------
          coinRandom = floor(Random()*27);
          G.coins = coinRandom;
          
          //SETUP SUPPLY COUNT------------------------------------------------
          supplyRandomEstate = floor(Random()*100);
          G.supplyCount[estate] = supplyRandomEstate;
          
          //SETUP NUMBER OF BUYS COUNT------------------------------------------------
          numBuysRandom = floor(Random()*20);//set intial buys
          G.numBuys = numBuysRandom; 
           
          //What CHOICE?------------------------------------------------
          choice1 = floor(Random()*2);//0 or 1

          
          
          
          
          //RUN CARD FUNCTION------------------------------------------------
          handpos = 0, choice1, choice2 = 0, choice3 = 0, bonus = 0;
          cardEffect(baron, choice1, choice2, choice3, &G, handpos, &bonus);
          
          

          printf("TEST NUM: %d Deck: %d Hand: %d Discard: %d Player %d\n",countNum, deckRandom, handRandom, discardRandom, G.whoseTurn+1);
          //////////////////////
          ///GET ESTATE CARD
          ////////////////////////
          if(choice1 == 0 && (G.hand[G.whoseTurn][1] == 1)) {
             if(DEBUG) {
                printf("GET ESTATE CARD---\n");
                
                printf("Coins = %d ,expected %d\n",G.coins, coinRandom);
                assert( G.coins == coinRandom);
                
                printf("Number of buys = %d,expected %d\n",G.numBuys, (numBuysRandom+1));
                assert( G.numBuys == (numBuysRandom+1));
                
                printf("Estate Supply Count = %d ,expected %d\n", G.supplyCount[estate], supplyRandomEstate-1);
                if(G.supplyCount[estate] != supplyRandomEstate-1)
                   printf("TEST FAIL\n");
                
                printf("Hand Supply Count = %d ,expected %d\n", G.handCount[G.whoseTurn], handRandom);
                assert(G.handCount[G.whoseTurn] == handRandom);
            
                printf("Discard Supply Count = %d ,expected %d\n", G.discardCount[G.whoseTurn], discardRandom+1);
                //assert(G.discardCount[G.whoseTurn] == discardRandom+1);
                if(G.discardCount[G.whoseTurn] != discardRandom+1);
                  printf("TEST FAIL\n");
                

             }
          }
          
          
          
          //////////////////////
          ///DISCARD ESTATE CARD
          ////////////////////////
          if(choice1 == 1 && (G.hand[G.whoseTurn][1] == 1)) {
             if(DEBUG) {
               printf("DISCARD ESTATE CARD---\n");
               
               printf("Coins = %d ,expected %d\n",G.coins, coinRandom+4);
               assert( G.coins == coinRandom+4);
               
               printf("Number of buys = %d,expected %d\n",G.numBuys, (numBuysRandom+1));
               assert( G.numBuys == (numBuysRandom+1));
               
               printf("Estate Supply Count = %d ,expected %d\n", G.supplyCount[estate], supplyRandomEstate);
               assert( G.supplyCount[estate] == supplyRandomEstate);
               
               printf("Hand Supply Count = %d ,expected %d\n", G.handCount[G.whoseTurn], handRandom-1);
                assert(G.handCount[G.whoseTurn] == handRandom-1);
               
               printf("Discard Supply Count = %d ,expected %d\n", G.discardCount[G.whoseTurn], discardRandom+1);
                assert(G.discardCount[G.whoseTurn] == discardRandom+1);
             }
         
          }
          
          
          //////////////////////
          ///ESTATE CARD NOT FOUND IN HAND
          ////////////////////////
           if(choice1 == 1 && G.hand[G.whoseTurn][1] != estate){
            if(DEBUG) {
               printf("ESTATE CARD NOT FOUND---\n");
               
               printf("Coins = %d ,expected %d\n",G.coins, coinRandom);
               //assert( G.coins == coinRandom);
               if(G.coins != coinRandom)
                   printf("TEST FAIL\n");
               
               printf("Number of buys = %d,expected %d\n",G.numBuys, (numBuysRandom+1));
               assert( G.numBuys == (numBuysRandom+1));        
               
               printf("Estate Supply Count = %d ,expected %d\n", G.supplyCount[estate], supplyRandomEstate);
               //assert( G.supplyCount[estate] == 10);
               if(G.supplyCount[estate] != supplyRandomEstate)
                   printf("TEST FAIL\n");
               
               printf("Deck Supply Count = %d ,expected %d\n", G.deckCount[G.whoseTurn], deckRandom);
               assert(G.deckCount[G.whoseTurn] == deckRandom);
               
               printf("Hand Supply Count = %d ,expected %d\n", G.handCount[G.whoseTurn], handRandom-1);
               //assert(G.handCount[G.whoseTurn] == handRandom-1);
               if(G.handCount[G.whoseTurn] != handRandom-1)
                  printf("TEST FAIL\n");
               
               
               printf("Discard Supply Count = %d ,expected %d\n", G.discardCount[G.whoseTurn], discardRandom+1);
               //assert(G.discardCount[G.whoseTurn] == discardRandom+1);
               if(G.discardCount[G.whoseTurn] == discardRandom+1);
                  printf("TEST FAIL\n");
               }
        
          } 

          countNum++;
       }
     

       
       
 
    
    
    

    return 0;
}