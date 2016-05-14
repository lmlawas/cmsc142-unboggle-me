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

            if( children.containsKey(c) ) node = children.get(c);
            else{
                node = new TrieNode(c);
                children.put(c, node);
            }

            children = node.children;

            if( i == word.length()-1 ) node.valid = true;
        }
    }// end of addWord()

    public boolean searchWord(String word) {
    /***************************************************************************
        This method looks for the String word in the Trie.
    ***************************************************************************/
        TrieNode node = searchNode(word);

        if( node != null && node.valid ) return true;
        return false;
    }// end of searchWord()

    public TrieNode searchNode(String word){
        Map<Character, TrieNode> children = root.children;
        TrieNode node = null;
        for(int i = 0; i < word.length(); i++){
            char c = word.charAt(i);
            if( children.containsKey(c) ){
                node = children.get(c);
                children = node.children;
            }
            else return null;
        }

        return node;
    }// end of searchNode()
}
