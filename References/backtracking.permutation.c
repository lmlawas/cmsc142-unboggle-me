#include <stdio.h>
#include <stdlib.h>
#define N 3

int main(){
	int start, move;				// move = current level at the tree
	int nopts[N+2];					// nopts = no. of options = top of stacks
	int option[N+2][N+2];			// option = stack (extra 2 cols and 2 rows for easier implementation)
	int i, candidate, count = 0;

	move = start = 0; 
	nopts[start]= 1;				// temporary number of options; if nopts[i] == 0. program ends

	while (nopts[start] >0){
		if(nopts[move]>0){			// **cond1** -- if there are still options, branch out
			move++;
			nopts[move]=0;
			
			// Print the solution when the sequence has lenght N
			if(move==N+1){			// **cond2** -- if the solution is found
				for(i=1;i<move;i++)
					printf("%2i",option[i][nopts[i]]);	// print top of stacks
				printf("\n");
				count++;
			}
			
			else {					// **cond3** -- enumerate the possible branches(?)
				// Generate candidate solutions
				for(candidate = N; candidate >=1; candidate --) {
					// Check the top of stacks
					for(i = move; i >= 1; i--){
						if(candidate == option[i][nopts[i]]) break;
					}
					if(i == 0){
						nopts[move]++;
						option[move][nopts[move]] = candidate;
					}					
				}            
			}
		}
		
		//if there are no more options on the current stack, backtrack
		else {						// **cond1** -- else backtrack
			move--;
			nopts[move]--;
		}
  	}

  	printf("\n%d\n", count);
}

// note: comment out lines 20, 25, 27 and 39
// to get the perutations from 1 to N, not just N