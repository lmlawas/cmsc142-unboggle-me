class TrieNode{
    char letter;
    boolean valid;
    TrieNode parent;
    TrieNode sibling;
    TrieNode first;

    public TrieNode(){
        letter = '^';
        valid = false;
        parent = null;
        sibling = null;
        first = null;
    }

    public TrieNode(char c, TrieNode p, TrieNode s, TrieNode f){
        letter = c;
        valid = false;
        parent = p;
        sibling = s;
        first = f;
    }
}
