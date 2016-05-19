import java.util.*;

class Tray{

	Letter values[][];
	int size;
	LinkedList<String> words;
	
	public Tray(char values[][], int size){
		this.values = new Letter[size][size];
	
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				Letter l = new Letter(values[i][j], i, j);
				this.values[i][j] = l;
			}
		}
		this.words = new LinkedList<String>();
		this.size = size;
		generateWords();
		printTray();
		System.out.println(this.words);
	}

	void printTray(){
		for(int i = 0; i < this.size; i++){
			for(int j = 0; j < this.size; j++){
				System.out.print(this.values[i][j].c);
			}
			System.out.println();
		}	
	}

	void generateWords(){
		int start, move;
		int length = this.size*this.size+2;
		int nopts[] = new int[length];
		Letter option[][] = new Letter[length][length];
		int i, j, row, col, neighbor_count;
		Letter candidate[] = new Letter[8];
		
		
		//prep for stack printing
		for(i = 0; i < length; i++){
			for(j = 0; j < length; j++){
				Letter l = new Letter('-', i, j);
				option[i][j] = l;
			}		
		}
		
		//initialize nopts
		Arrays.fill(nopts, 0);
		
		start = 0;
		move = 1;
		nopts[start] = 1;
		
		//initialize roots
		for(i = 0; i < this.size; i++){
			for(j = 0; j < this.size; j++){
				Letter l = new Letter(values[i][j].c, i, j);
				option[1][i*this.size+j+1] = l;
				nopts[1]++;
			}
		}
		
		System.out.println(length);
		
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
				for(i = 1; i < move; i++){
					String c = Character.toString(option[i][nopts[i]].c);
					word += c;
				}
				
				//generated word as string
				//System.out.println(word);
				
				this.words.add(new String(word));
				
				ArrayList<Letter> neighbors = new ArrayList<Letter>(8);
				neighbors = this.getNeighbors(option[move-1][nopts[move-1]]);
				
				i = 0;
				for(Letter l : neighbors){
					for(j = move; j >= 1; j--){
						if(l.row == option[j][nopts[j]].row && l.col == option[j][nopts[j]].col){
							break;
						}
					}
					
					if(j == 0){
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
		

	}//end of generateWords

	ArrayList<Letter> getNeighbors(Letter l){
		
		ArrayList<Letter> arr = new ArrayList<Letter>(8);
		
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				if(l.row+i >= 0 && l.row+i < this.size && l.col+j >= 0 && l.col+j < this.size){
					if( !(i==0 && j==0) ){					
						arr.add(this.values[l.row+i][l.col+j]);
					}
				}
			}
		}
		
		return arr;		
	}
	
}
