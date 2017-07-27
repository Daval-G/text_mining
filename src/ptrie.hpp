#pragma once

#include <time.h>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

class PTrie
{
    public:
        PTrie() : word(false) {};
        PTrie(std::string root, bool word)
        {
            this->root = root;
            this->word = word;
        };
        PTrie(std::vector<std::string> words, std::vector<unsigned> freqs) : word(false)
        {
            for (unsigned i = 0; i < words.size(); i++)
                this->add(words.at(i), freqs.at(i));
        };
        ~PTrie()
        {
            for (auto c: childs)
                delete(c);
        };

    public:
        std::string get_root() const { return root; };
        std::vector<PTrie *> get_childs() const { return childs; };
        bool is_word() const { return word; };
        void get_words(std::vector<std::string>& res, std::string current = "") const;
        void add_child(PTrie *child) { childs.push_back(child); };
        void set_root(std::string root) { this->root = root; };
        void set_word(bool word) { this->word = word; };
        void add(std::string word, unsigned freq);
        void remove(std::string& word);
        friend std::ostream& operator <<(std::ostream& stream, const PTrie& trie)
        {
            stream << trie.get_root();
            for (auto c: trie.get_childs())
                stream << "(" << *c << ")";
            return stream;
        }


    private:
        bool word;
        std::string root;
        std::vector<PTrie *> childs;
};
