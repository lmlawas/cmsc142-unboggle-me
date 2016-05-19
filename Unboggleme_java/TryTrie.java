import java.util.*;
import java.io.*;

class TryTrie{

    public static void main(String[] args){
		LinkedList<Tray> trays = new LinkedList<Tray>();
		LinkedList<String> valid_words = new LinkedList<String>();
		Trie dictionary = new Trie();

        readTrays( trays );
        readDictionary( dictionary );

        for( int i = 0; i < trays.size(); i++ ){
        	LinkedList<String> generated_words = trays.get(i).words;

        	for( int j = 0; j < generated_words.size(); j++ ){
        		boolean found = dictionary.searchWord( generated_words.get(j) );
        		if( found ) valid_words.add( generated_words.get(j) );
        	}
        }

        for( int i = 0; i < valid_words.size(); i++ ){
        	System.out.println( valid_words.get(i) );
        }

    }

    private static void readTrays(LinkedList<Tray> trays){
	/***************************************************************************
		This method reads input.txt to get the values of the trays.
	***************************************************************************/
		try{
			FileReader fr = new FileReader("input.txt");
			BufferedReader br = new BufferedReader(fr);

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

				Tray tray = new Tray(values, size);

				// add the tray instance
				trays.add(tray);
			}

			// stop reading
			fr.close();

		}catch(IOException e){
			System.out.println("No input.txt file found.");
		}
	}// end of readTrays()

    public static void readDictionary(Trie root){
    /***************************************************************************
        This method reads dictionary.txt and adds them to the Trie.
    ***************************************************************************/

        try{
            FileReader fr = new FileReader("dictionary.txt");
            BufferedReader br = new BufferedReader(fr);
            String word = null;

            // while dictionary.txt has words
            while( (word = br.readLine()) != null ) {

                // only add words with length 3 or more
                if( word.length() < 3 ) continue;
                root.addWord(word);

            }

            // stop reading
            fr.close();

        }catch(IOException e){
			System.out.println("No dictionary.txt file found.");
		}

    }// end of readDictionary()
}
