/* unittest4.c
* Elisabeth Mansfield - mansfiee
* CS261 - Assignment 3
* Test implementation of supplyCount()
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

	// Card variables
	int c_num = 27;
	int c[] = {curse, estate, duchy, province,
		copper, silver, gold,
		adventurer, council_room, feast, gardens, mine, 
		remodel, smithy, village, baron, great_hall,
		minion, steward, tribute, ambassador, cutpurse, 
		embargo, outpost, salvager, sea_hag, treasure_map};	
	char* c_names[] = {"curse", "estate", "duchy", "province",
		"copper", "silver", "gold",
		"adventurer", "council_room", "feast", "gardens", "mine", 
		"remodel", "smithy", "village", "baron", "great_hall",
		"minion", "steward", "tribute", "ambassador", "cutpurse", 
		"embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	int c_index = -1;	

	// Start test
	printf ("*** TESTING supplyCount(): ***\n");		
	int test_fail = 0;
	int i,j,r,fail,match_condition,neg_condition;

	// for each card
	for(i=0; i < c_num; i++){
		fail = 0;
		c_index++;
		match_condition = 0;
		neg_condition = 0;

		// Initialize Game - first 10 kingdom cards
		if(c_index<17){
			memset(&G, 23, sizeof(struct gameState)); // clear the game state
			r = initializeGame(MAX_PLAYERS, &c[7], seed, &G); // initialize a new game	
		}
		// Initialize Game - last 10 kingdom cards
		else{
			memset(&G, 23, sizeof(struct gameState)); // clear the game state
			r = initializeGame(MAX_PLAYERS, &c[17], seed, &G); // initialize a new game			
		}

		#if (NOISY_TEST == 1)
			printf("TEST supply count of card: \'%s\'",c_names[i]);
		#endif	

		// test supplies -5 to 5
		for(j=-5; j<=5; j++){
			G.supplyCount[c[i]] = j;
			r = supplyCount(c[i],&G);
			// if values don't match
			if(r != j){
				fail++;
				match_condition++;
			}
			// if returned negative value
			if(r < 0){
				fail++;
				neg_condition++;
			}
		}

		if(fail){
			#if (NOISY_TEST == 1)
				printf("\t... FAIL");							
				if(match_condition)
					printf(" | Match_case");	
				if(neg_condition)
					printf(" | Neg_case");
				printf("\n");
			#endif			
			test_fail++;					
		}
		else{
			#if (NOISY_TEST == 1)
				printf("\t... PASS\n");
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