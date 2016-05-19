import java.util.*;
import java.io.*;

class UnboggleMe{

    public static void main(String[] args){
		LinkedList<Tray> trays = new LinkedList<Tray>();		
		Trie dictionary = new Trie();
		boolean success_reading = false;

		success_reading = readDictionary( dictionary );
		if( success_reading ){
			System.out.println("Reading dictionary.txt ...");
			success_reading = readTrays( trays, dictionary );
		}
        
        if( success_reading ){

        	System.out.println("Reading input.txt ...");

        	boolean success_writing = saveResult( trays );

        	if( success_writing ){
        		System.out.println("Valid words successfully saved to output.txt !");
        	}
        	else{
        		System.out.println("Error writing to output file.");
        	}
        }
        else{
        	System.out.println("Error reading necessary input files.");
        }

    }

    private static boolean saveResult(LinkedList<Tray> trays){
	/***************************************************************************
		This method saves the valid words of each tray to output.txt
	***************************************************************************/
		try{
			// open output.txt
			FileWriter fw = new FileWriter("output.txt");
			
			for( int i = 0; i < trays.size(); i++ ){
	        	LinkedList<String> valid_words = trays.get(i).valid_words;
	        	fw.write( "TRAY " + (i+1) + "\n" );
	        	fw.write( valid_words.size() + "\n" );
	        	for( int j = 0; j < valid_words.size(); j++ ){
	        		fw.write( valid_words.get(j) + "\n" );	        		
	        	}
	        	fw.write( "\n" );
	        }

	        // stop writing to output.txt
			fw.close();

			// success writing to file
			return true;
		}
		catch( Exception e ){
			System.out.println("Error: "+e);
		}

		// error writing to file
		return false;

	}// end of saveResult()

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

    private static boolean readDictionary(Trie root){
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
