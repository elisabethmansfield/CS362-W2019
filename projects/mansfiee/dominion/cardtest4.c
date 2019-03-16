/* cardtest4.c
* Elisabeth Mansfield - mansfiee
* CS261 - Assignment 3
* Test implementation of card village
TESTS:
1. Add 1 card to hand, discard 1 card.
2. Add 2 action to state.
3. No state change should occur for other players.
4. No state change should occur to the victory card piles and kingdom card piles.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	// gameState variables
	struct gameState G, testG;
	int seed = 1000;

	// Card variables
  	int c_num = 17;	
  	int c[] = {curse, estate, duchy, province,
  			copper, silver, gold,
  			adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};	
	char* c_names[] = {"curse", "estate", "duchy", "province",
	    "copper", "silver", "gold",
	    "adventurer", "embargo", "village", "minion", "mine", "cutpurse",
		"sea_hag", "tribute", "smithy", "great_hall"};	 
	int k[] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};	    	

	// Initialize Game
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	initializeGame(MAX_PLAYERS, k, seed, &G); // initialize a new game	
	memcpy(&testG, &G, sizeof(struct gameState));    		

    int curPlayer = 0, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int i,j,fail = 0, test_fail = 0;		
	printf ("*** TESTING card village: ***\n");

	// ----------- TEST 1: Add 1 card to hand, discard 1 card --------------	
	printf("TEST 1: Add 1 card to hand, discard 1 card");
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);	
	if(testG.handCount[curPlayer] != G.handCount[curPlayer]) {
		printf("\t... FAIL\n");
		test_fail++;
	}
	else{
		printf("\t... PASS\n");
	}

	// ----------- TEST 2: Add 2 action to state --------------	
	printf("TEST 2: Add 2 action to state");
	memcpy(&testG, &G, sizeof(struct gameState));    			
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);	
	if(testG.numActions != (G.numActions + 2)){
		printf("\t... FAIL\n");
		test_fail++;
	}
	else{
		printf("\t... PASS\n");
	}

	// ----------- TEST 3: No state change in other players --------------	
	printf("TEST 3: No state change in other players");
	memcpy(&testG, &G, sizeof(struct gameState));  	
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	fail = 0;
	// loop all players, look at state
	for(i=curPlayer+1; i < MAX_PLAYERS; i++){
		if (testG.deckCount[i] != G.deckCount[i]){
			fail++;
			printf("\t... FAIL deckCount");
		}
		if (testG.handCount[i] != G.handCount[i]){
			fail++;
			printf("\t... FAIL handCount");
		}
		if (testG.discardCount[i] != G.discardCount[i]){
			fail++;
			printf("\t... FAIL discardCount");
		}		
		for(j=0; j<MAX_DECK; j++){
			if(testG.deck[i][j] != G.deck[i][j]){
				fail++;
				printf("\t... FAIL deck");
			}
			if(testG.discard[i][j] != G.discard[i][j]){
				fail++;
				printf("\t... FAIL discard");
			}
			if(testG.hand[i][j] != G.hand[i][j]){
				fail++;
				printf("\t... FAIL hand");
			}			
		}
	}
	if(fail){
		printf("\t... FAIL");
		test_fail++;
	}
	else
		printf("\t... PASS");
	printf("\n");

	// ----------- TEST 4: No state change in card piles --------------
	printf("TEST 4: No state change in card piles");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);	
	fail = 0;
	// loop all card piles, look at state
	for(i=0; i < c_num; i++){
		if(testG.supplyCount[c[i]] != G.supplyCount[c[i]]){
			fail++;
			printf("\t... FAIL card_%s",c_names[i]);
		}
	}
	if(fail){
		printf("\t... FAIL");		
		test_fail++;
	}
	else
		printf("\t... PASS");
	printf("\n");	

	if(test_fail){
		printf("*** TEST FAILURE DETECTED. ***\n");		
	}
	else{
		printf("*** ALL TESTS PASS! ***\n");		
	}

	return 0;
}
