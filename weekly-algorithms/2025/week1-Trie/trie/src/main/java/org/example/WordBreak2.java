package org.example;


import java.util.ArrayList;
import java.util.List;

public class WordBreak2 {

    // link: https://leetcode.com/problems/word-break-ii/?envType=problem-list-v2&envId=trie

    private final List<String> wordDict;
    private final Trie trie;
    public WordBreak2(List<String> wordDict) {
        this.wordDict = wordDict;
        this.trie = new Trie();
        initTrie();
    }

    public void initTrie() {
        for (String word : wordDict) {
            trie.insert(word);
        }
    }

    private void wordBreakHelper(TrieNode itr, List<String> sentences, String s, int i, int length, String sentence) {
        System.out.println("sentence = " + sentence + " i = " + i + " length = " + length + " sentence = " + sentence);
        if (i == length) {
            sentences.add(sentence);
            return;
        }
        for (int j = i; j < length; j++) {
            if (itr.children.get(s.charAt(j)) == null) {
                return;
            }
            itr = itr.children.get(s.charAt(j));
            sentence += s.charAt(j);
            if (itr.isEndOfWord) {
                wordBreakHelper(this.trie.getRoot(), sentences, s, j + 1, length, (j + 1 == length ? sentence: sentence + " "));
            }
        }
    }

    public List<String> wordBreak(String s) {
        List<String> sentences = new ArrayList<String>();
        wordBreakHelper(this.trie.getRoot(), sentences, s, 0, s.length(), "");
        return sentences;
    }

    public static void main(String[] args) {
        List<String> wordDict = new ArrayList<>();
        wordDict.add("cat");
        wordDict.add("cats");
        wordDict.add("and");
        wordDict.add("sand");
        wordDict.add("dog");

        WordBreak2 wordBreak = new WordBreak2(wordDict);
        List<String> res = wordBreak.wordBreak("catsanddog");
        System.out.println(res.toString());

    }
}
