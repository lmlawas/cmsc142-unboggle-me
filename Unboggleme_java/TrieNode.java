/*
    reference: http://www.programcreek.com/2014/05/leetcode-implement-trie-prefix-tree-java/
*/

import java.util.*;

class TrieNode {
    char letter;
    boolean valid;
    HashMap<Character, TrieNode> children = new HashMap<Character, TrieNode>();

    public TrieNode() {}

    public TrieNode(char letter){
        this.letter = letter;
    }
}
