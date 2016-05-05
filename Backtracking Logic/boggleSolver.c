#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "boggleSolver.h"
#define MINIMUM_WORD 3

int main(){
	int i;
	WORD * generatedWords = NULL;
	TRAY * puzzles = NULL; 
	TRAY * ptr;

	readFile(&puzzles);

	ptr = puzzles;

	while(ptr != NULL){
		printTray(ptr->values, ptr->size);
		ptr = ptr->next;
	}
	   
	generateWords(puzzles, 3);
	
	for(i = 0; i < puzzles->size; i++){
		free(puzzles->values[i]);
	}
	free(puzzles->values);
	free(puzzles);
}
