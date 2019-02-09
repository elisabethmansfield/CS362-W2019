/* -----------------------------------------------------------------------
* testUpdateCoins.c
*
* Demonstration of how to write unit tests for dominion-base updateCoins()
* Use this as a template for writing your unit tests. 
* Note the the included tests are very basic and can be improved in many different ways.
* There is also something obviously missing in terms of boundary testing. What is it?
*
* Include the following lines in your makefile:
* testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
* gcc -o testUpdateCoins -g testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {

	// initialize game
	struct gameState G;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};	
	int numPlayer = MAX_PLAYERS;

	// loop variables
	int i;	
	int p, r, handCount;
	int bonus;	
	int maxBonus = 10;
	int maxHandCount = 5;

	// arrays of all 500 coppers, silvers, and golds
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	for (i = 0; i < MAX_HAND; i++){
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}

	printf ("TESTING updateCoins():\n");
	// Loop all players
	for (p = 0; p < numPlayer; p++){
		// Loop all cards in hand
		for (handCount = 1; handCount <= maxHandCount; handCount++){
			// Loop all bonuses
			for (bonus = 0; bonus <= maxBonus; bonus++){

				// Intro
				#if (NOISY_TEST == 1)
					printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
				#endif

				// Initialize Game
				memset(&G, 23, sizeof(struct gameState)); // clear the game state
				r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.handCount[p] = handCount; // set the number of cards on hand

				// Copper Test
				memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
				updateCoins(p, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("Copper = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
				#endif
				assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

				// Silver Test
				memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
				updateCoins(p, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("Silver = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
				#endif
				assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct
				
				// Gold Test
				memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
				updateCoins(p, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("Gold = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
				#endif
				assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
			}
		}
	}
	printf("All tests passed!\n");
	return 0;
}