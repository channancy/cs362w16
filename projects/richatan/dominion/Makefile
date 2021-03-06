CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testHelpers.o: test_helpers.h test_helpers.c dominion.o rngs.o 
	gcc -c test_helpers.c -g $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: testHelpers.o dominion.o rngs.o
	echo "-------------------------------------------------" > unittestresults.out
	echo -e "\tResults for Function Unit Tests" >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out
	
	echo "unittest1.c: shuffle()" >> unittestresults.out
	gcc -o unittest1 unittest1.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out
	
	echo "unittest2.c: gainCard()" >> unittestresults.out
	gcc -o unittest2 unittest2.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out

	echo "unittest3.c: buyCard()" >> unittestresults.out
	gcc -o unittest3 unittest3.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out

	echo "unittest4.c: getWinners()" >> unittestresults.out
	gcc -o unittest4 unittest4.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	
	echo -e "\n-------------------------------------------------" >> unittestresults.out
	echo -e "\tResults for Card Unit Tests" >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out
	
	echo "cardtest1.c: smithy" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out

	echo "cardtest2.c: adventurer" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out

	echo "cardtest3.c: council_room" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out

	echo "cardtest4.c: baron" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	
	echo -e "\n-------------------------------------------------" >> unittestresults.out
	echo -e "\t\tCode Coverage" >> unittestresults.out
	echo "-------------------------------------------------" >> unittestresults.out
	gcov ./dominion.c >> unittestresults.out

randomtestadventurer.out: testHelpers.o dominion.o rngs.o
	echo "-----------------------------------------------------------" > randomtestadventurer.out
	echo -e "\tResults for Random Tests: Adventurer Card" >> randomtestadventurer.out
	echo "-----------------------------------------------------------" >> randomtestadventurer.out
	
	gcc -o randomtestadventurer randomtestadventurer.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	
	echo -e "\n-----------------------------------------------------------" >> randomtestadventurer.out
	echo -e "\t\tCode Coverage" >> randomtestadventurer.out
	echo "-----------------------------------------------------------" >> randomtestadventurer.out
	gcov ./dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard.out: testHelpers.o dominion.o rngs.o
	echo "-----------------------------------------------------------" > randomtestcard.out
	echo -e "\tResults for Random Tests: Village Card" >> randomtestcard.out
	echo "-----------------------------------------------------------" >> randomtestcard.out
	
	gcc -o randomtestcard randomtestcard.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./randomtestcard >> randomtestcard.out
	
	echo -e "\n-----------------------------------------------------------" >> randomtestcard.out
	echo -e "\t\tCode Coverage" >> randomtestcard.out
	echo "-----------------------------------------------------------" >> randomtestcard.out
	gcov ./dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittest*.exe cardtest*.exe *.gcov *.gcda *.gcno *.so *.out
