/* unittest1.c
* Elisabeth Mansfield - mansfiee
* CS261 - Assignment 3
* Test implementation of getCost()
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
  	int c_costs[] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
  	char* c_names[] = {"curse", "estate", "duchy", "province",
	    "copper", "silver", "gold",
    	"adventurer", "council_room", "feast", "gardens", "mine", 
	    "remodel", "smithy", "village", "baron", "great_hall",
    	"minion", "steward", "tribute", "ambassador", "cutpurse", 
    	"embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    int c_index = -1;
	
	int i,r;	
	int fail;
	int test_fail = 0;
	// Initialize Game
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(MAX_PLAYERS, &c[7], seed, &G); // initialize a new game		

	printf ("*** TESTING getCost(): ***\n");

	// Loop through every card
	for(i=0; i<c_num; i++){
		c_index++;
		fail = 0;
		#if (NOISY_TEST == 1)
			printf("TEST get cost of card: \'%s\'", c_names[i]);
		#endif		
		if(c_index>=17){
			memset(&G, 23, sizeof(struct gameState)); // clear the game state
			r = initializeGame(MAX_PLAYERS, &c[17], seed, &G); // initialize a new game				
		}
		if(getCost(i)!=c_costs[i]){
			#if (NOISY_TEST == 1)		
				printf("\t... FAIL\n");
			#endif			
			fail++;
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