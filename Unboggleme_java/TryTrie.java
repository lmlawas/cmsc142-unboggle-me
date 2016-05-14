import java.util.*;
import java.io.*;

class TryTrie{

    public static void main(String args[]){
        Trie dictionary = new Trie();
        readFile( dictionary );
        boolean found = dictionary.searchWord( "ABALONS" );
        if( found ) System.out.println("Found1!!");
        found = dictionary.searchWord( "ABALONE" );
        if( found ) System.out.println("Found2!!");
    }

    public static void readFile(Trie root){
    /***************************************************************************
        This method reads dictionary.txt .
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

        }catch(Exception e){
            System.out.println("Error.");
        }

    }// end of readFile()
}
