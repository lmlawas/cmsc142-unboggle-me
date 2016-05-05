#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node{
	char c;
	struct node * first;
	struct node * sibling;
	struct node * parent;
	int valid;
}NODE;

typedef struct tray{
	char **values;
	int size;
	struct tray * next;
}TRAY;

void removeBN(char x[100]){
/*******************************************************************************
	This function removes the newline character of a word.
*******************************************************************************/
	int i;
	for(i = 0; i<100; i++){
		if(x[i]=='\n'){
			x[i] = '\0';
		}
	}
}

void printTray(char **tray, int size){
/*******************************************************************************
	This function prints the tray of dimension size by size.
*******************************************************************************/
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			printf("%c ", tray[i][j]);
		}
		putchar('\n');		
	}
}

int readFile(char ***tray){
/*******************************************************************************
	This function reads input file containing the tray dimension and
	the alphabet of the tray.
*******************************************************************************/
	int size = 0, i, j, k, noOfTrays = 0;
	FILE *fp;
	fp = fopen("input.txt", "r");
	
	if(fp == NULL) return -1;
	
	if(!feof(fp)){
		fscanf(fp, "%d\n", &noOfTrays);
		printf("size: %d\n", noOfTrays);
	}
	else{
		printf("FAIL!\n");
		return -1;
	}
	
	//allocate trays bwahahaha
	
	
	for(k= 0; k < noOfTrays; k++){
		if(!feof(fp)) fscanf(fp, "%d\n", &size);
		printf("%d\n", size);
		*tray = (char **)malloc(sizeof(char *)*size);
		for(i = 0; i < size; i++){
			(*tray)[i] = (char *)malloc(sizeof(char)*size);
		} 
	
		while(!feof(fp)){
			for(i = 0; i < size; i++){
				for(j = 0; j < size; j++){
					if(j < size - 1) fscanf(fp, "%c ", &((*tray)[i][j]));
					else fscanf(fp, "%c\n", &((*tray)[i][j]));
				}
			}
		}
	}
	
	fclose(fp);
	return size;
}

void readDictionary(){
/*******************************************************************************
	This function reads the dictionary of valid words.
*******************************************************************************/
	FILE *fp;
	char word[100];

	fp = fopen("dictionary.txt", "r");	

	if(fp == NULL) return ;
	else{
		while(!feof(fp)){
			fscanf(fp, "%s\n", word);
			removeBN(word);
			//printf("%s\n", word);
		}
	}

	fclose(fp);
}

void getIndex(TRAY * head, char c, int * row, int * col){
/*******************************************************************************
	This function gets the index.
*******************************************************************************/
	int i, j;
	
	*row = -1;
	*col = -1;
	
	for(i = 0; i < head->size; i++){
		for(j = 0; j < head->size; j++){			
			if(head->values[i][j] == c){
				*row = i;
				*col = j;
				break;
			}
		}
	}
	
	
}

int getNeighbors(TRAY * head, char candidate[8], int row, int col){
/*******************************************************************************
	This function gets the neighbors of the pointed value of head
	and pushes them to candidate array.
*******************************************************************************/
	int i, j, tos = 0;	
	for(i = -1; i < 2; i++){
		for(j = -1; j < 2; j++){
			if(row+i >= 0 && row+i < head->size && col+j >= 0 && col+j < head->size){
				if( !(i==0 && j==0) ){					
					candidate[tos] = head->values[row+i][col+j];
					tos++;
				}
			}
		}
	}
	
	return tos;
	
}

void generateWords(TRAY * head, int min_word_size){
/*******************************************************************************
	This function generates possible words in the tray.
*******************************************************************************/
	int start, move;
	int nopts[head->size*head->size+2];
	char option[head->size*head->size+2][head->size*head->size+2];
	int i, j, row, col, neighbor_count;
	char candidate[8];
	TRAY * ptr = NULL;
	FILE *write;
	
	write = fopen("generatedWords.txt","w");
	ptr = head;
	
	//while(ptr != NULL){
		printf("Tray size: %d\n", ptr->size);
		//printf("00: %c\n", ptr->values[0][0]);
		start = 0;
		move = 1;
		nopts[start] = 1;
		
		for(i = 0; i < head->size*head->size+2; i++){
			for(j = 0; j < head->size*head->size+2; j++){
				option[i][j] = '-';
			}
		}
	
		for(i = 0; i < ptr->size; i++){
			for(j = 0; j < ptr->size; j++){
				option[1][i*ptr->size+j+1] = ptr->values[i][j];
				//printf("%c\t", option[1][i*ptr->size+j+1]);
				nopts[1]++;				
			}
			//printf("nopts1: %d\n", nopts[1]);
		}
	
		while(nopts[start] > 0){
			if(nopts[move] > 0){
			
				move++;
				nopts[move] = 0;
			
				//if(move >= min_word_size){
				
					for(i = 1; i < move; i++){
						printf("%c", option[i][nopts[i]]);
						fprintf(write, "%c", option[i][nopts[i]]);
					}
					fprintf(write, "\n");
					putchar('\n');
				
				
					/*for(i = 0; i < head->size*head->size+2; i++){
						for(j = 0; j < head->size*head->size+2; j++){
							printf("%c ", option[i][j]);
						}
						printf("\n");
					}*/
				
				//} else {
					//get index of top of stack of previous level
					getIndex(ptr, option[move-1][nopts[move-1]], &row, &col);
					//printf("%c\n", option[move-1][nopts[move-1]]);
					//printf("%d %d\n", row, col);
					//get neighbors
					neighbor_count = getNeighbors(ptr, candidate, row, col);
					//printf("%d neigh neigh\n", neighbor_count);
					//for(i = 0; i < neighbor_count; i++){
					//	printf("%c\t", candidate[i]);
					//}
					//putchar('\n');
					
					//neighbor_count = 0;
				
					//add each neighbor as candidate
					for(i = 0; i < neighbor_count; i++){
					//make sure there are no repetitons
						// Check the top of stacks
						for(j = move; j >= 1; j--){
							//printf("candidate: %c || stack:%c\n", candidate[i], option[j][nopts[j]]);
							if(candidate[i] == option[j][nopts[j]]) break;
						}
						//printf("\nmove %d\n", move);
						if(j == 0){
							nopts[move]++;
							option[move][nopts[move]] = candidate[i];
							//printf("%c\t", option[move][nopts[move]]);
						}
					}
			
				//}
		
			} else {
				move--;
				nopts[move]--;
			}
	
		}
		
		//ptr = ptr->next;
		
	//}

}
