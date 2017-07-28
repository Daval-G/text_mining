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
        void add(std::string word, long freq, int j = 0);
        bool remove(std::string& word, int j = 0) {return false;}
        void print()
        {
            std::cout << "size: " << nodes.size() << "\n";
            for (size_t i = 0; i < nodes.size(); ++i)
                std::cout << nodes[i].edge << " ";
        }
        friend std::ostream& operator <<(std::ostream& stream, const CPTrie& trie)
        {
            stream << "size: " << trie.nodes.size() << "\n";
            for (size_t i = 0; i < trie.nodes.size(); ++i)
                stream << trie.nodes[i].edge << " ";
            return stream;
        }

    private:
        std::vector<Node> nodes;
};
