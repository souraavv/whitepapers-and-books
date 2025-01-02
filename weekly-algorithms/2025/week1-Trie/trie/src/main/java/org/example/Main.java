package org.example;

public class Main {
    public static void main(String[] args) {
        Trie trie = new Trie();

        trie.insert("apple");
        trie.insert("app");
        trie.insert("apricot");

        System.out.println(trie.search("apple"));
        System.out.println(trie.search("app"));
        System.out.println(trie.search("apricot"));
        System.out.println(trie.search("banana"));

        System.out.println(trie.startsWith("app"));
        System.out.println(trie.startsWith("apr"));
        System.out.println(trie.startsWith("ban"));
    }
}