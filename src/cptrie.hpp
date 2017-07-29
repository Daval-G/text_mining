#pragma once

#include <vector>
#include <string>
#include <iostream>

class CPTrie
{
    public:
        struct Node
        {
            Node() : pf(0), fd(0), freq(0) {}
            Node(std::string s, long f) : edge(s), pf(0), fd(0), freq(f) {}
            Node(std::string s, long f, int fd) : edge(s), pf(0), fd(fd), freq(f) {}
            Node(int pf, std::string s, long f) : edge(s), pf(pf), fd(0), freq(f) {}
            std::string edge;
            size_t pf;
            size_t fd;
            long freq;
        };
    
    public:
        CPTrie() { Node n; nodes.push_back(n); }
        CPTrie(std::vector<std::string>& words, std::vector<long> freqs)
        {
            Node n;
            nodes.push_back(n);
            for (unsigned i = 0; i < words.size(); i++)
                add(words[i], freqs[i]);
        }
        ~CPTrie() {}
        void add(std::string& word, long freq, int j = 0);
        bool remove(std::string& word, int j = 0) {return false;}
        friend std::ostream& print(std::ostream& stream, const CPTrie& trie, int index);
        friend std::ostream& operator <<(std::ostream& stream, const CPTrie& trie);

    private:
        std::vector<Node> nodes;
};
