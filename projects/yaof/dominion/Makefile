CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

compareStates.o: compareStates.h compareStates.c
	gcc -c compareStates.c -g $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o compareStates.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o compareStates.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o compareStates.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o compareStates.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o compareStates.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o compareStates.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o compareStates.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o compareStates.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o compareStates.o
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o compareStates.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o compareStates.o
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o compareStates.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o compareStates.o
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o compareStates.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o compareStates.o
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o compareStates.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./randomtestcard > randomtestcard.out
	./randomtestadventurer > randomtestadventurer.out
	gcov -b -c -f dominion >> unittestresults.out

randomtestcard: randomtestcard.c dominion.o rngs.o compareStates.o
	gcc -o randomtestcard randomtestcard.c dominion.o rngs.o compareStates.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o compareStates.o
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o compareStates.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard randomtestadventurer unittestresults.out 

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer unittestresults.out