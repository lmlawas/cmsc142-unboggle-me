import java.util.*;
import java.io.*;

class TryTrie{

    public static void main(String[] args){
		LinkedList<Tray> trays = new LinkedList<Tray>();
		Trie dictionary = new Trie();

        readTrays( trays );
        readDictionary( dictionary );

        boolean found = dictionary.searchWord( "ABALONS" );
        if( found ) System.out.println("Found1!!");

        found = dictionary.searchWord( "ABALONE" );
        if( found ) System.out.println("Found2!!");
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
				Tray tray = new Tray();
				tray.size = Integer.parseInt( br.readLine() );
				char[][] values = new char[tray.size][tray.size];

				for( int j = 0; j < tray.size; j++ ){
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

				tray.values = values;

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
            int i = 0;

            // while dictionary.txt has words
            while( (word = br.readLine()) != null ) {

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
