#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "boggleSolver.h"
#define MINIMUM_WORD 3

int main(){
	int size, i, j;
	TRAY *head = NULL;
	//size = readFile(&tray);
	
	head = (TRAY *)malloc(sizeof(TRAY));
	head->size = 4;
	head->values = (char **)malloc(sizeof(char *)*head->size);
	for(i = 0; i < head->size; i++){
		head->values[i] = (char *)malloc(sizeof(char)*head->size);
	}
	
	for(i = 0; i < head->size; i++){
		for(j = 0; j < head->size; j++){
			head->values[i][j] = (char)('A' + i * head->size + j);
		}
	}
		
	printTray(head->values, head->size);
	//readDictionary();
	   
	generateWords(head, MINIMUM_WORD);
	
	for(i = 0; i < head->size; i++){
		free(head->values[i]);
	}
	free(head->values);
	free(head);
}
