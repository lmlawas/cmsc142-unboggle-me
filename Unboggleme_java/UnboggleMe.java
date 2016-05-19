import java.util.*;
import java.io.*;

class UnboggleMe{

    public static void main(String[] args){
		LinkedList<Tray> trays = new LinkedList<Tray>();		
		Trie dictionary = new Trie();
		boolean success_reading = false;

		success_reading = readDictionary( dictionary );
		if( success_reading ){
			success_reading = readTrays( trays, dictionary );
		}
        
        if( success_reading ){
        	for( int i = 0; i < trays.size(); i++ ){
	        	LinkedList<String> valid_words = trays.get(i).valid_words;

	        	System.out.println( valid_words.size() );
	        	for( int j = 0; j < valid_words.size(); j++ ){
	        		System.out.println( valid_words.get(j) );
	        	}
	        	System.out.println();
	        }
        }
        else{
        	System.out.println("Error reading necessary input files.");
        }

        

    }

    private static boolean readTrays(LinkedList<Tray> trays, Trie dictionary){
	/***************************************************************************
		This method reads input.txt to get the values of the trays,
		as well as the list of valid words generated from the tray
		by searching the dictionary.
	***************************************************************************/
		try{
			FileReader fr = new FileReader("input.txt");
			BufferedReader br = new BufferedReader( fr );

			// get number of trays
			int noOfTrays = Integer.parseInt( br.readLine() );

			for( int i = 0; i < noOfTrays; i++ ){
				
				int size = Integer.parseInt( br.readLine() );
				char[][] values = new char[size][size];

				for( int j = 0; j < size; j++ ){
					String row = br.readLine();
					char[] arr = row.toCharArray();
					int n = 0;

					// update values attribute of the tray
					for( int k = 0; k < row.length(); k++ ){
						if( arr[k] != ' '){
							values[j][n] = arr[k];
							n++;
						}
					}

				}

				Tray tray = new Tray( values, size, dictionary );

				// add the tray instance
				trays.add( tray );
			}

			// stop reading
			fr.close();

			// if reading dictionary is successful
            return true;

		}catch( IOException e ){
			System.out.println("No input.txt file found.");
		}

		// if reading dictionary is not successful
		return false;

	}// end of readTrays()

    public static boolean readDictionary(Trie root){
    /***************************************************************************
        This method reads dictionary.txt and adds them to the Trie.
    ***************************************************************************/

        try{
            FileReader fr = new FileReader("dictionary.txt");
            BufferedReader br = new BufferedReader( fr );
            String word = null;

            // while dictionary.txt has words
            while( (word = br.readLine()) != null ) {

                // only add words with length 3 or more
                if( word.length() < 3 ) continue;
                root.addWord(word);

            }

            // stop reading
            fr.close();

            // if reading dictionary is successful
            return true;

        }catch( IOException e ){
			System.out.println("No dictionary.txt file found.");
		}

		// if reading dictionary is not successful
		return false;

    }// end of readDictionary()
}
