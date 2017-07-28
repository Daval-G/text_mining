#pragma once

#include <time.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>

class PTrie
{
    public:
        PTrie() : freq(0) {};
        PTrie(std::string root, long freq)
        {
            this->root = root;
            this->freq = freq;
        };
        PTrie(std::vector<std::string> words, std::vector<long> freqs) : freq(0)
        {
            for (unsigned i = 0; i < words.size(); i++)
                this->add(words.at(i), freqs.at(i));
        };
        ~PTrie()
        {
        };

    public:
        std::string get_root() const { return root; };
        std::vector<PTrie *> get_childs() const { return childs; };
        bool is_word() const { return (freq != 0); };
        int nb_nodes();
        void get_words(std::vector<std::string>& res, std::string current = "") const;
        void add_child(PTrie *child) { childs.push_back(child); };
        void set_root(std::string root) { this->root = root; };
        void set_freq(long freq) { this->freq = freq; };
        void add(std::string& word, long freq = 0, int j = 0);
        void add(std::string& word, int j = 0);
        bool remove(std::string& word, int j = 0);
        void distance(std::string& word);
        friend std::ostream& operator <<(std::ostream& stream, const PTrie& trie)
        {
            stream << trie.get_root();
            for (auto c: trie.get_childs())
                stream << "(" << *c << ")";
            return stream;
        }


    private:
        long freq;
        std::string root;
        std::vector<PTrie *> childs;
};
