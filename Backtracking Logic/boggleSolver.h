#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct letter{
	char c;
	struct letter * first;
	struct letter * sibling;
	struct letter * parent;
	int valid;
}LETTER;

typedef struct word{
	char *str;
	int length;
	int valid;
	struct word * next;	
}WORD;

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

void createTray(TRAY **ptr, int size){
/*******************************************************************************
	This function allocates a new tray instance.
*******************************************************************************/
	int i;

	// assign values of the tray instance
	(*ptr) = (TRAY *)malloc(sizeof(TRAY));
	(*ptr)->size = size;
	(*ptr)->next = NULL;

	// allocate the values 2D array
	(*ptr)->values = (char **)malloc(sizeof(char *)*size);
	for(i = 0; i < size; i++){
		((*ptr)->values)[i] = (char *)malloc(sizeof(char)*size);
	}
}

void readFile(TRAY **head){
/*******************************************************************************
	This function reads input file containing the tray dimension and
	the alphabet of the tray.
*******************************************************************************/
	int size = 0, i, j, k, noOfTrays = 0;
	TRAY *ptr, *temp;
	FILE *fp;
	fp = fopen("trays.in", "r");
	
	// if input.txt does not exist
	if(fp == NULL) return;
	
	// read number of trays
	if(!feof(fp)){
		fscanf(fp, "%d\n", &noOfTrays);
		printf("noOfTrays: %d\n", noOfTrays);
	}
	else{
		printf("FAIL!\n");
		return;
	}
	
	for(k= 0; k < noOfTrays; k++){

		// read size
		if(!feof(fp)) fscanf(fp, "%d\n", &size);
		else break;		

		// create new tray instance
		createTray(&temp, size);
		
		// read values for the tray instance
		for(i = 0; i < size; i++){
			for(j = 0; j < size; j++){
				if(j < size - 1) fscanf(fp, "%c ", &((temp->values)[i][j]));
				else fscanf(fp, "%c\n", &((temp->values)[i][j]));			
			}			
		}		
	
		// point head to first tray instance
		if( (*head) == NULL) ptr = (*head) = temp;		
		else{
			ptr->next = temp;
			ptr = temp;
		}		

		// free tray instance
		// freeTray(&temp, size);
		// free(temp);
	}
	
	fclose(fp);
	return;
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
	TRAY * ptr = head;
	int nopts[ptr->size*ptr->size+2];
	char option[ptr->size*ptr->size+2][ptr->size*ptr->size+2];
	int i, j, row, col, neighbor_count;
	char candidate[8];
	FILE *write;
	
	write = fopen("generatedWords.txt","w");
	ptr = head;
	
	while(ptr != NULL){
		printf("Tray size: %d\n", ptr->size);
		start = 0;
		move = 1;
		nopts[start] = 1;
		nopts[move] = 0;
		
		for(i = 0; i < ptr->size*ptr->size+2; i++){
			for(j = 0; j < ptr->size*ptr->size+2; j++){
				option[i][j] = '-';
			}
		}
	
		for(i = 0; i < ptr->size; i++){
			for(j = 0; j < ptr->size; j++){
				option[1][i*ptr->size+j+1] = ptr->values[i][j];
				printf("%c", option[1][i*ptr->size+j+1]);
				nopts[1]++;			
				printf("%d\n", nopts[1]);	
			}
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
					
					//get neighbors
					neighbor_count = getNeighbors(ptr, candidate, row, col);
				
					//add each neighbor as candidate
					for(i = 0; i < neighbor_count; i++){
					//make sure there are no repetitons
						// Check the top of stacks
						for(j = move; j >= 1; j--){
							if(candidate[i] == option[j][nopts[j]]) break;
						}
						if(j == 0){
							nopts[move]++;
							option[move][nopts[move]] = candidate[i];
						}
					}
				//}
		
			} else {
				move--;
				nopts[move]--;
			}
		}
		
		ptr = ptr->next;
		
	}

}
