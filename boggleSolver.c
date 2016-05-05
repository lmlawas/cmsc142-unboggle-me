#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "boggleSolver.h"
#define MINIMUM_WORD 3

int main(){
	WORD * generatedWords = NULL;
	TRAY * puzzles = NULL; 
	TRAY * ptr;

	readFile(&puzzles);

	ptr = puzzles;

	while(ptr != NULL){
		printTray(ptr->values, ptr->size);
		ptr = ptr->next;
	}

	dummyData(&generatedWords);	
	
	if(generatedWords != NULL) linearSearch(generatedWords);
}
