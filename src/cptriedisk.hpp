#pragma once

#include <vector>
#include <string>
#include <iostream>

class CPTrieDisk
{
    public:
        struct Node
        {
            Node() : start(NULL), pf(0), fd(0), freq(0), size(0) {}
            Node(char* s, char len, long f) : start(s), pf(0), fd(0), freq(f), size(len) {}
            Node(char* s, char len, long f, int fd) : start(s), pf(0), fd(fd), freq(f), size(len) {}
            Node(int pf, char* s, char len, long f) : start(s), pf(pf), fd(0), freq(f), size(len) {}
            unsigned pf;
            unsigned fd;
            long freq;
            char* start;
            char size;
        } __attribute__((packed));
    
    public:
        CPTrieDisk() { nodes.push_back(Node()); }
        CPTrieDisk(std::vector<std::string>& words, std::vector<long>& freqs)
        {
            nodes.reserve(words.size() * 2);
            nodes.push_back(Node());
            for (unsigned i = 0; i < words.size(); i++)
                add(words[i], freqs[i]);
        }
        ~CPTrieDisk() {}
        size_t nb_nodes() { return nodes.size() - 1; }
        void add(std::string& word, long freq, int j = 0);
        void write(std::ostream& os);
        void read(std::istream& is);

    private:
        std::vector<Node> nodes;
};

struct Result
{
    Result() : word(NULL), frequence(0), distance(0) {}
    Result(char *w, long f, size_t d) : word(w), frequence(f), distance(d) {}
    char *word;
    long frequence;
    size_t distance;
};