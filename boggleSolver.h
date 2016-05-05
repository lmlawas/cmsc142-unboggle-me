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

void generateWords(){
/*******************************************************************************
	This function generates possible words in the tray.
*******************************************************************************/

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

void linearSearch(WORD * generatedWords){
/*******************************************************************************
	This function compares the generated words from the tray against the
	words in the dictionary.
*******************************************************************************/
	FILE *read, *write;
	WORD * word1;
	int len1, len2, totalValidWords = 0;	
	char word2[100];
		
	if(generatedWords == NULL){
		printf("\nNo words generated for linear search.\n\n");
		return ;
	}

	word1 = generatedWords;		

	// traverse generated words
	while(word1 != NULL){
		
		len1 = word1->length;

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

				// if word1->str and word2 have same length
				if(len1 == len2){

					// if word1 and word2 are equal
					if( strcmp(word1->str, word2) == 0){
						word1->valid = 1;
						totalValidWords++;
						break;
					}
				}				
			}
		}
		
		fclose(read);

		// get the next generated word
		word1 = word1->next;
	}

	if(totalValidWords == 0){
		printf("NO VALID WORDS!!");
		return ;
	}

	word1 = generatedWords;
	
	// write result to file	
	write = fopen("output.txt", "w");
	fprintf(write, "%d\n", totalValidWords);

	while(word1 != NULL){
		if(word1->valid == 1) fprintf(write, "%s\n", word1->str);
		word1 = word1->next;
	}

	fclose(write);	

}