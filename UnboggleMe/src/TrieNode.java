/*
    reference: http://www.programcreek.com/2014/05/leetcode-implement-trie-prefix-tree-java/
*/

import java.util.HashMap;

class TrieNode {

	/* TrieNode attributes */
    char letter;
    boolean valid;
    HashMap<Character, TrieNode> children = new HashMap<Character, TrieNode>();

    /* TrieNode root contructor */
    public TrieNode() {}

    /* TrieNode contstructor */
    public TrieNode( char letter ){
        this.letter = letter;        
    }
}
