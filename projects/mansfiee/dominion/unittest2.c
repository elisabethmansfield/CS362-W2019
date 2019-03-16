/* unittest2.c
* Elisabeth Mansfield - mansfiee
* CS261 - Assignment 3
* Test implementation of handCard()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	srand(time(NULL));

	// gameState variables
	struct gameState G;
	int seed = 1000;

	// Card variables
	int c_num = 17;
	int c[] = {curse, estate, duchy, province,
		copper, silver, gold,
		adventurer, council_room, feast, mine, smithy, 
		great_hall, minion, tribute, sea_hag, treasure_map};			

	// Start test
	printf ("*** TESTING handCard(): ***\n");		
	int test_fail = 0;
	int i,j,r,fail;
	int failhand[MAX_HAND];
	for (i = 0; i < sizeof(failhand)/sizeof(int); i++) {
	    failhand[i] = 0;
	}

	// for each player
	for(i=0; i < MAX_PLAYERS; i++){	

		// Initialize Game
		memset(&G, 23, sizeof(struct gameState)); // clear the game state
		r = initializeGame(MAX_PLAYERS, &c[7], seed, &G); // initialize a new game		

		fail = 0;		
		G.whoseTurn = i;
		#if (NOISY_TEST == 1)
			printf("TEST get card for each hand from player: %d",i);
		#endif	
		// for each hand position
		for(j=0; j < MAX_HAND; j++){
			// fill player's hand with random cards			
			G.hand[i][j] = c[(rand() % c_num)];	
			// test if hand matches			
			if(handCard(j,&G) != G.hand[i][j]){
				fail++;
				failhand[j] = j;
			}
		}
		// if player failed
		if(fail){
			#if (NOISY_TEST == 1)
				printf("\t... FAIL");
				for(j=0; j<MAX_HAND; j++){
					if(failhand[j])
						printf("\t hand_%d",j);
				}
				printf("\n");
			#endif			
			test_fail++;				
		}
		else{
			#if (NOISY_TEST == 1)
				printf("\t... PASS (all hand)\n");
			#endif			
		}
	}

	if(test_fail){
		printf("*** TEST FAILURE DETECTED. ***\n");		
	}
	else{
		printf("*** ALL TESTS PASS! ***\n");		
	}
	return 0;
}