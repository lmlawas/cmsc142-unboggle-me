import java.util.*;

class Tray{

	/* Tray attributes */
	Letter values[][];
	int size;
	LinkedList<String> valid_words;
	
	/* Tray constructor */
	public Tray(char values[][], int size, Trie dictionary){
		System.out.println( "Loading tray...");
		this.values = new Letter[size][size];
		
		for( int i = 0; i < size; i++ ){
			for( int j = 0; j < size; j++ ){
				Letter l = new Letter( values[i][j], i, j );
				this.values[i][j] = l;
			}
		}

		this.valid_words = new LinkedList<String>();
		this.size = size;
		generateValidWords( dictionary );
		//printTray();
		//System.out.println( this.valid_words ); 	//print all valid words
		System.out.println( "Tray now loaded!");
	}

	void printTray(){
	/***************************************************************************
        This method displays the contents of the tray of values.
    ***************************************************************************/
		for( int i = 0; i < this.size; i++ ){
			for( int j = 0; j < this.size; j++ ){
				System.out.print( this.values[i][j].c );
			}
			System.out.println();
		}	
	}

/*	Letters[][] getTray(int size){
		Letters[][] t = new Letters[size][size];
	}*/

	void generateValidWords(Trie dictionary){
	/***************************************************************************
        This method generates a list of valid words using
        	(1) iterative backtracking to list all possible words; and
        	(2) Trie data structure to counter check the possible word
        	to the dictionary.
    ***************************************************************************/
		int start, move;
		int length = this.size*this.size+2;
		int nopts[] = new int[length];
		Letter option[][] = new Letter[length][length];
		int i, j, row, col, neighbor_count;
		Letter candidate[] = new Letter[8];
		
		
		//prep for stack printing
		for( i = 0; i < length; i++ ){
			for( j = 0; j < length; j++ ){
				Letter l = new Letter( '-', i, j );
				option[i][j] = l;
			}		
		}
		
		//initialize nopts
		Arrays.fill( nopts, 0 );
		
		start = 0;
		move = 1;
		nopts[start] = 1;
		
		//initialize roots
		for( i = 0; i < this.size; i++ ){
			for( j = 0; j < this.size; j++ ){
				Letter l = new Letter( values[i][j].c, i, j );
				option[1][i*this.size+j+1] = l;
				nopts[1]++;
			}
		}
		
		//System.out.println( length );
		
		while(nopts[start] > 0){
			if(nopts[move] > 0){
				move++;				
				nopts[move] = 0;
				
				String word = "";
				
				//
				/*for(i = 0; i < length; i++){
					for(j = 0; j < length; j++){
						System.out.print(option[i][j].c + " ");
					}
					System.out.println();		
				}*/
				
				//add each character to the string
				for( i = 1; i < move; i++ ){
					String c = Character.toString(option[i][nopts[i]].c);
					word += c;
				}
				
				//generated word as string
				boolean found = dictionary.searchWord( new String(word) );
	        	if( found ) this.valid_words.add( new String(word) );
				
				ArrayList<Letter> neighbors = new ArrayList<Letter>(8);
				neighbors = this.getNeighbors(option[move-1][nopts[move-1]]);
				
				i = 0;
				for( Letter l : neighbors ){
					for( j = move; j >= 1; j-- ){
						if( l.row == option[j][nopts[j]].row && l.col == option[j][nopts[j]].col){
							break;
						}
					}
					
					if( j == 0 ){
						nopts[move]++;
						option[move][nopts[move]] = l;
					}
					i++;
				}
			}else{
				move--;
				nopts[move]--;
			}		
		}
	}// end of generateValidWords()

	ArrayList<Letter> getNeighbors(Letter l){
	/***************************************************************************
        This method gets the list of valid neighbors of Letter l.
    ***************************************************************************/
		
		ArrayList<Letter> neighbors = new ArrayList<Letter>(8);
		
		for( int i = -1; i < 2; i++ ){
			for( int j = -1; j < 2; j++ ){
				if( l.row+i >= 0 && l.row+i < this.size && l.col+j >= 0 && l.col+j < this.size ){
					if( !(i==0 && j==0) ){					
						neighbors.add( this.values[l.row+i][l.col+j] );
					}
				}
			}
		}

		return neighbors;		
	}// end of getNeighbors()
	
}
