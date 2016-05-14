/*
    reference: http://www.programcreek.com/2014/05/leetcode-implement-trie-prefix-tree-java/
*/

import java.util.*;

public class Trie {
    private TrieNode root;

    /* constructor */
    public Trie() {
        root = new TrieNode();
    }

    public void addWord(String word) {
    /***************************************************************************
        This method adds String word to the Trie.
    ***************************************************************************/
        HashMap<Character, TrieNode> children = root.children;

        for( int i = 0; i < word.length(); i++){
            char c = word.charAt(i);
            TrieNode node;

            // if letter is already in the Trie
            if( children.containsKey(c) ) node = children.get(c);

            // else, letter is not yet in the Trie
            else{
                node = new TrieNode(c);
                children.put(c, node);
            }

            // get the node's children
            children = node.children;

            // the last letter of the word is labeled valid
            if( i == word.length()-1 ) node.valid = true;
        }
    }// end of addWord()

    public boolean searchWord(String word) {
    /***************************************************************************
        This method checks if the word can be found in the Trie or not.
    ***************************************************************************/
        TrieNode node = searchNode(word);

        // if the last letter of the word is found and is labeled valid
        if( node != null && node.valid ) return true;
        return false;
    }// end of searchWord()

    public TrieNode searchNode(String word){
    /***************************************************************************
        This method looks for the String word in the Trie.
    ***************************************************************************/
        Map<Character, TrieNode> children = root.children;
        TrieNode node = null;

        // traverse the word
        for(int i = 0; i < word.length(); i++){
            char c = word.charAt(i);

            // if the letter is found in the Trie
            if( children.containsKey(c) ){
                node = children.get(c);
                children = node.children;
            }

            // else the letter is not in the Trie
            else return null;
        }

        return node;
    }// end of searchNode()
}
