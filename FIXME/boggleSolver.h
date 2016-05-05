#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* GLOBAL VARIABLES */
int totalValidWords = 0;

/* STRUCTURE DEFINITION */
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

void createWord(WORD **ptr, char *str, int size){
/*******************************************************************************
	This function allocates a new word instance.
*******************************************************************************/

	// assign values of the word instance
	(*ptr) = (WORD *)malloc(sizeof(WORD));
	(*ptr)->length = size;
	(*ptr)->valid = -1;
	(*ptr)->str = (char *)malloc(sizeof(char)*size);
	(*ptr)->str = str;
	(*ptr)->next = NULL;
}

void freeTray(TRAY **ptr, int size){
/*******************************************************************************
	This function frees the tray instance.
*******************************************************************************/
	int i;

	for(i = 0; i < size; i++){
		free(((*ptr)->values)[i]);
	}

	free((*ptr)->values);	

}

void readFile(TRAY **head){
/*******************************************************************************
	This function reads input file containing the tray dimension and
	the alphabet of the tray.
*******************************************************************************/
	int size = 0, i, j, k, noOfTrays = 0;
	TRAY *ptr, *temp;
	FILE *fp;
	fp = fopen("input.txt", "r");
	
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

void dummyData(WORD ** head){
/*******************************************************************************
	This function generates dummy data of generated words for testing purposes.
*******************************************************************************/	
	WORD *tmp, *ptr;
	
	/* DUMMY DATA WHEN THERE ARE VALID AND INVALID WORDS */
	createWord(&tmp, "HELLO", strlen("HELLO"));
	(*head) = tmp;
	ptr = (*head);

	createWord(&tmp, "INVALID", strlen("INVALID"));
	ptr->next = tmp;
	ptr = tmp;

	createWord(&tmp, "AMAZING", strlen("AMAZING"));
	ptr->next = tmp;
	ptr = tmp;

	createWord(&tmp, "TECHNOLOGY", strlen("TECHNOLOGY"));
	ptr->next = tmp;
	ptr = tmp;

	createWord(&tmp, "DAZZLE", strlen("DAZZLE"));
	ptr->next = tmp;
	ptr = tmp;

	createWord(&tmp, "JEJEJE", strlen("JEJEJE"));
	ptr->next = tmp;
	ptr = tmp;

	/* DUMMY DATA IF ALL WORDS ARE INVALID */
	// createWord(&tmp, "HEYYO", strlen("HEYYO"));
	// (*head) = tmp;
	// ptr = (*head);

	// createWord(&tmp, "LALLALA", strlen("LALLALA"));
	// ptr->next = tmp;
	// ptr = tmp;

	// createWord(&tmp, "JEJEMON", strlen("JEJEMON"));
	// ptr->next = tmp;
	// ptr = tmp;

	// createWord(&tmp, "NAYZ", strlen("NAYZ"));
	// ptr->next = tmp;
	// ptr = tmp;

	// createWord(&tmp, "WANDERFUL", strlen("WANDERFUL"));
	// ptr->next = tmp;
	// ptr = tmp;
}

void linearSearch(char * word1, WORD **answer){
/*******************************************************************************
	This function compares the generated word word1 from the tray 
	against the	words in the dictionary.
*******************************************************************************/
	WORD *temp, *ptr;
	FILE *read, *write;
	int len1, len2;	
	char word2[100];
		
	removeBN(word1);
	len1 = strlen(word1);

	// read words from the dictionary
	read = fopen("dictionary.txt", "r");

	if(read == NULL){
		printf("\nNo words in dictionary for linear search.\n\n");			
		return ;
	}

	else{
		// traverse the words in the dictionary
		while(!feof(read)){

			fscanf(read, "%s\n", word2);
			removeBN(word2);
			len2 = strlen(word2);

			// if word1 and word2 have same length
			if(len1 == len2){

				// if word1 and word2 are equal
				if( strcmp(word1, word2) == 0){
					createWord(&temp, word1, len1);
					temp->valid = 1;				
					totalValidWords++;
					break;
				}
			}				
		}
	}
		
	fclose(read);

	if( (*answer) == NULL ) *answer = temp;
	else{
		ptr = (*answer);
		while( ptr->next != NULL ){
			ptr = ptr->next;
		}
		ptr->next = temp;
	}

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
	char * word1;
	TRAY * ptr = NULL;
	FILE *write;
	WORD *answer, *traverse;
		
	ptr = head;
		
		printf("Tray size: %d\n", ptr->size);		
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
				nopts[1]++;				
			}			
		}
	
		while(nopts[start] > 0){
			if(nopts[move] > 0){
			
				move++;
				nopts[move] = 0;

					word1 = (char *)malloc(sizeof(char)*move-1);
				
					for(i = 1; i < move; i++){
						word1[i-1] = option[i][nopts[i]];
					}
					linearSearch(word1, &answer);
					free(word1);
		
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
		
			} else {
				move--;
				nopts[move]--;
			}
	
		}

	// write result to file	
	write = fopen("output.txt", "w");
	fprintf(write, "%d\n", totalValidWords);

	traverse = answer;

	while(traverse != NULL){
		if(traverse->valid == 1) fprintf(write, "%s\n", traverse->str);
		traverse = traverse->next;
	}

	fclose(write);
}