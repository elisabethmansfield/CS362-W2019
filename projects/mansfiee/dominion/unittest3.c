/* unittest3.c
* Elisabeth Mansfield - mansfiee
* CS261 - Assignment 3
* Test implementation of buyCard()
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
	// gameState variables
	struct gameState G;
	int seed = 1000;

  	// Kingdom Card variables
  	int c_num = 27;
  	int c[] = {curse, estate, duchy, province,
    	copper, silver, gold,
    	adventurer, council_room, feast, gardens, mine, 
    	remodel, smithy, village, baron, great_hall,
    	minion, steward, tribute, ambassador, cutpurse, 
    	embargo, outpost, salvager, sea_hag, treasure_map};     	
  	int c_costs[] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
  	char* c_names[] = {"curse", "estate", "duchy", "province",
    	"copper", "silver", "gold",
    	"adventurer", "council_room", "feast", "gardens", "mine", 
    	"remodel", "smithy", "village", "baron", "great_hall",
    	"minion", "steward", "tribute", "ambassador", "cutpurse", 
    	"embargo", "outpost", "salvager", "sea_hag", "treasure_map"};	
    int c_index = -1;

	// Start test
	printf ("*** TESTING buyCard(): ***\n");		
	int test_fail = 0;
	int i,j,r,fail;

	// for each card
	for(i=0; i < c_num; i++){
		fail = 0;
		int condition[] = {0,0,0,0,0,0};
		c_index++;

		// Initialize Game
		if(c_index<17){
			memset(&G, 23, sizeof(struct gameState)); // clear the game state
			r = initializeGame(MAX_PLAYERS, &c[7], seed, &G); // initialize a new game	
		}
		else{
			// reinitialize game with 10 new kingdom cards
			memset(&G, 23, sizeof(struct gameState)); // clear the game state
			r = initializeGame(MAX_PLAYERS, &c[17], seed, &G); // initialize a new game			
		}

		// 111 If one card in pile, one buy, & enough coins
		#if (NOISY_TEST == 1)
			printf("TEST cases to buy card: \'%s\'",c_names[i]);
		#endif			
		G.supplyCount[c[i]] = 1;
		G.numBuys = 1;
		G.coins = c_costs[i];
		r = buyCard(c[i],&G);
		// must return 0
		if(r!=0){		
			fail++;	
			condition[0] = 1;	
		}

		// 110 If one card in pile, one buy, & not enough coins		
		G.supplyCount[c[i]] = 1;
		G.numBuys = 1;
		G.coins = c_costs[i]-1;
		r = buyCard(c[i],&G);
		// must return -1
		if(r==0){	
			fail++;	
			condition[1] = 1;	
		}

		// 101 If one card in pile, zero buy, & enough coins		
		G.supplyCount[c[i]] = 1;
		G.numBuys = 0;
		G.coins = c_costs[i];
		r = buyCard(c[i],&G);
		// must return -1
		if(r==0){	
			fail++;	
			condition[2] = 1;	
		}

		// 011 If zero card in pile, one buy, & enough coins		
		G.supplyCount[c[i]] = 0;
		G.numBuys = 1;
		G.coins = c_costs[i];
		r = buyCard(c[i],&G);
		// must return -1
		if(r==0){	
			fail++;	
			condition[3] = 1;	
		}

		// 001 If zero card in pile, zero buy, & enough coins		
		G.supplyCount[c[i]] = 0;
		G.numBuys = 0;
		G.coins = c_costs[i];
		r = buyCard(c[i],&G);
		// must return -1
		if(r==0){	
			fail++;	
			condition[4] = 1;	
		}

		// 000 If zero card in pile, zero buy, & not enough coins		
		G.supplyCount[c[i]] = 0;
		G.numBuys = 0;
		G.coins = c_costs[i]-1;
		r = buyCard(c[i],&G);
		// must return -1
		if(r==0){	
			fail++;	
			condition[5] = 1;	
		}

		if(fail){
			#if (NOISY_TEST == 1)
				printf("\t... FAIL");
				for(j=0; j<6; j++){
					if(condition[j])
						printf(" | case_%d",j);
				}	
				printf("\n");
			#endif			
			test_fail++;				
		}
		else{
			#if (NOISY_TEST == 1)
				printf("\t... PASS (5 cases)\n");
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