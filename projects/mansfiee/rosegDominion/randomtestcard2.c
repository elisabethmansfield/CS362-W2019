/* randomtestcard2.c
* Elisabeth Mansfield - mansfiee
* CS261 - Assignment 4
* Random test implementation of card village
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
/*    case village:
      //+1 Card
      drawCard(currentPlayer, state);
			
      //+2 Actions
      state->numActions = state->numActions + 2;
			
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
*/
// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
// cardEffect(village, 0, 0, 0, &testG, handPos, 0);

int testCard(int testNum) {
	
	// Non-randomized variables
	int seed = 1000;	// randomSeed for rngs.c
    int card = village;
	int i, j, r, treasure, test_treasure, index1, index2, fail, test_fail,
		choice1, choice2, choice3, handPos, bonus, curPlayer;    
    i = j = r = treasure = test_treasure = fail = test_fail =
    choice1 = choice2 = choice3 = bonus = curPlayer = 0;
    index1 = index2 = -1;
	struct gameState G, testG;

	// Randomized variables 
	// rand() % (MAX + 1 - MIN) + MIN	
	int numPlayers = rand() % (MAX_PLAYERS+1 - 2) + 2;	// random 2-4 players
   	int kingdomCards[] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
					   	baron, great_hall, minion, steward, tribute, 
					   	ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};		   	
	int k[10];
	memset(&k,0,10*sizeof(kingdomCards[0]));
	int vil = rand() % 10;
	handPos = rand() % 5;

	// need 10 random kingdom cards to initialize game	 
	for(i=0; i<10; i++){
		if(i==vil) 
			k[i] = village;
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

	// Random Test
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Compare Results
	// Add 1 card to hand, discard 1 card 	
	if(testG.handCount[curPlayer] != G.handCount[curPlayer]) 
		test_fail++;

	// Add 2 action to state 		
	if(testG.numActions != (G.numActions + 2))
		test_fail++;

	// No state change in other players 	
	for(i=curPlayer+1; i < numPlayers; i++){
		if( (testG.deckCount[i] != G.deckCount[i])
			|| (testG.handCount[i] != G.handCount[i])
			|| (testG.discardCount[i] != G.discardCount[i]) )
			fail++;	
		for(j=0; j<MAX_DECK; j++){
			if( (testG.deck[i][j] != G.deck[i][j])
				|| (testG.discard[i][j] != G.discard[i][j])
				|| (testG.hand[i][j] != G.hand[i][j]) )
				fail++;		
		}
	}
	if(fail){
		test_fail++;
	}

	// Output Results	
	printf("TEST %d: numPlayers: %d, handPos: %d, kingdomCards: ",testNum,numPlayers,handPos);	
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
	printf ("*** RANDOM TESTING card village: ***\n");
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
