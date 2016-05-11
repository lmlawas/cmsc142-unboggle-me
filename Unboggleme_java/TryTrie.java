import java.util.*;

class TryTrie{

    public static void main(String args[]){
        TrieNode root = new TrieNode();
    }

    public void readFile(TrieNode root){
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

                if( word.length < 3 ) continue;

                /* insert logic here har har */
            }

            // stop reading
            fr.close();

        }catch(Exception e){
            System.out.println("Error.");
        }

    }// end of readFile()
}
