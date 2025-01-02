package org.example;
import java.util.HashMap;

class TrieNode {
    HashMap<Character, TrieNode> children;
    boolean isEndOfWord;

    public TrieNode() {
        children = new HashMap<>();
        isEndOfWord = false;
    }
}

public class Trie {
    private final TrieNode root;

    public Trie() {
        root = new TrieNode();
    }

    public void insert(String word) {
        TrieNode currentNode = root;

        for (char c : word.toCharArray()) {
            currentNode.children.putIfAbsent(c, new TrieNode());
            currentNode = currentNode.children.get(c);
        }
        currentNode.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode currentNode = root;

        for (char c : word.toCharArray()) {
            currentNode = currentNode.children.get(c);
            if (currentNode == null) {
                return false;
            }
        }
        return currentNode.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode currentNode = root;

        for (char c : prefix.toCharArray()) {
            currentNode = currentNode.children.get(c);
            if (currentNode == null) {
                return false;
            }
        }
        return true;
    }
}
