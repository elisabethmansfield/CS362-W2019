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

# Unit & Card Tests - Assignment 3
unittestresults:
	make cleantests
	make dominion.o
	make unittests
	make cardtests
	make rununittests &> unittestresults.out
	make runcardtests >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

mytest:
	make cleantests
	make dominion.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 &> testresults/cardtest4.out
	# gcov -f dominion.c
	# cat dominion.c.gcov 	

unittests: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)	
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)	
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)	
	
rununittests:
	./unittest1	
	./unittest2
	./unittest3	
	./unittest4

cardtests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS) 
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS) 
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS) 
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS) 

runcardtests:
	./cardtest1	
	./cardtest2	
	./cardtest3		
	./cardtest4

cleantests:
	rm -f dominion.o dominion.c.gcov dominion.g* unittestresults.out
	rm -f unittest1 unittest1.g* unittest2 unittest2.g* unittest3 unittest3.g* unittest4 unittest4.g*
	rm -f cardtest1 cardtest1.g* cardtest2 cardtest2.g* cardtest3 cardtest3.g* cardtest4 cardtest4.g*
	rm -rf unittest1.dSYM unittest2.dSYM unittest3.dSYM unittest4.dSYM
	rm -rf cardtest1.dSYM cardtest2.dSYM cardtest3.dSYM cardtest4.dSYM
######

# Random Tests - Assignment 4
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
######

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
