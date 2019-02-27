CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

randomtestresults:
	make cleanrandomtests
	make randomtestcard1
	make randomtestcard2
	make randomtestadventurer

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	rm -f dominion.o dominion.c.gcov dominion.g* 
	make dominion.o
	gcc -o randomtestcard1 randomtestcard1.c -g  dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 &> randomtestcard1.out
	gcov -f dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	rm -f dominion.o dominion.c.gcov dominion.g* 
	make dominion.o
	gcc -o randomtestcard2 randomtestcard2.c -g  dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 &> randomtestcard2.out
	gcov -f dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o 
	rm -f dominion.o dominion.c.gcov dominion.g* 
	make dominion.o
	gcc -o randomtestadventurer randomtestadventurer.c -g  dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer &> randomtestadventurer.out
	gcov -f dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

cleanrandomtests:
	rm -f dominion.o dominion.c.gcov dominion.g* randomtestcard1.out randomtestcard2.out randomtestadventurer.out
	rm -f randomtestcard1 randomtestcard1.g* randomtestcard2 randomtestcard2.g* randomtestadventurer randomtestadventurer.g* 
	rm -rf randomtestcard1.dSYM randomtestcard2.dSYM randomtestadventurer.dSYM 

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
