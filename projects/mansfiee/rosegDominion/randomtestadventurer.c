/* randomtestadventurer.c
* Elisabeth Mansfield - mansfiee
* CS261 - Assignment 4
* Random test implementation of card adventurer
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h> 
#include <time.h> 
#define NUMTESTS 100

// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
// int adventurerCase(int drawntreasure, struct gameState *state, int currentPlayer, int temphand[], int z)
// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
// cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);

int testCard(int testNum) {
	
	// Non-randomized variables
	int seed = 1000;	// randomSeed for rngs.c
    int card = adventurer;
	int i, j, n, r, treasure, test_treasure, index1, index2, test_fail,
		choice1, choice2, choice3, handPos, bonus, curPlayer;    
    i = j = n = r = treasure = test_treasure = test_fail =
    choice1 = choice2 = choice3 = handPos = bonus = curPlayer = 0;
    index1 = index2 = -1;
	struct gameState G, testG;

	// Randomized variables 
	// rand() % (MAX + 1 - MIN) + MIN	
	int numPlayers = rand() % (MAX_PLAYERS+1 - 2) + 2;	// random 2-4 players
   	int kingdomCards[] = {council_room, feast, gardens, mine, remodel, smithy, 
					   	village, baron, great_hall, minion, steward, tribute, 
					   	ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};		   	
	int k[10];
	memset(&k,0,10*sizeof(kingdomCards[0]));
	int adv = rand() % 10;

	// need 10 random kingdom cards to initialize game	 
	for(i=0; i<10; i++){
		if(i==adv) 
			k[i] = adventurer;
		while(!k[i]){
			j = rand() % 19;
			if(kingdomCards[j]){
				k[i] = kingdomCards[j];
				kingdomCards[j] = 0;
			}
		}
	}			

	// Initialize Game and testGame
	memset(&G, 23, sizeof(struct gameState)); 		// clear the game state
	r = initializeGame(numPlayers, k, seed, &G); 		// initialize a new game	
	if(r != 0)
		test_fail++;
	memcpy(&testG, &G, sizeof(struct gameState));   // copy game state to testGame 		 

	// Initialize Comparison Variables
	for(i=0; i<G.handCount[curPlayer]; i++){
		if(G.hand[curPlayer][i] == copper || G.hand[curPlayer][i] == silver || G.hand[curPlayer][i] == gold)
			treasure++;
	}

	for(i=G.deckCount[curPlayer]-1; i>=0; i--){
		if(G.deck[curPlayer][i] == copper || G.deck[curPlayer][i] == silver || G.deck[curPlayer][i] == gold){
			if(index1 < 0) 
				index1 = i;
			else if(index1 >= 0 && index2 < 0){
				index2 = i;
				break;
			}
		}
	}	

	// Random Test
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Compare Results
	// 2 Treasure cards added to hand 
	for(i=0; i<testG.handCount[curPlayer];i++){
		if(testG.hand[curPlayer][i] == copper || testG.hand[curPlayer][i] == silver || testG.hand[curPlayer][i] == gold){
			test_treasure++;		
		}
	}
	if(test_treasure != (treasure + 2))
		test_fail++;

	// Top cards in deck are discarded
	if(testG.deck[curPlayer][index2])
		test_fail++;		

	// No state change in other players 
	for(i=curPlayer+1; i < numPlayers; i++){
		if( (testG.deckCount[i] != G.deckCount[i]) 
			|| (testG.handCount[i] != G.handCount[i]) 
			|| (testG.discardCount[i] != G.discardCount[i]) )
			test_fail++;	
		for(j=0; j<MAX_DECK; j++){
			if( (testG.deck[i][j] != G.deck[i][j])
				|| (testG.discard[i][j] != G.discard[i][j])
				|| (testG.hand[i][j] != G.hand[i][j]) )
				test_fail++;			
		}
	}

	// Output Results	
	printf("TEST %d: numPlayers: %d, kingdomCards: ",testNum,numPlayers);	
	for(i=0; i<10; i++){
		printf("%d, ",k[i]);
	}	
	if(test_fail)
		printf("...FAIL\n");				
	else
		printf("...PASS\n");	

	return test_fail;
}

int main() {

	srand(time(0));
    int i, test, test_fail;
	i = test = test_fail = 0;    
	printf ("*** RANDOM TESTING card adventurer: ***\n");
	sleep(2);

	for(i=1; i<=NUMTESTS; i++){
		test = testCard(i);
		if(test)
			test_fail++;
	}

	if(test_fail)
		printf("*** TEST FAILURE DETECTED. ***\n");		
	else
		printf("*** ALL TESTS PASS! ***\n");		

	return 0;
}
