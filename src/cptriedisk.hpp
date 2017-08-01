#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cstring>

/**
 * \file cptrie.hpp
 * \brief Structure de CPTrieDisk.
 * \author daval-_g moreau_2
 *
 * Déclare la structure CPTrieDisk et ses composants principaux.
 *
 */

/**
 * \class CPTrieDisk
 * \brief Classe contenant tous les noeuds.
 */
class CPTrieDisk
{
    public:
        /**
         * \struct Node
         * \brief Noeud de l'arbre.
         */
        struct Node
        {
            Node() : start(NULL), pf(0), fd(0), freq(0), size(0) {}
            Node(char* s, unsigned char len, long f) : start(s), pf(0), fd(0), freq(f), size(len) {}
            Node(char* s, unsigned char len, long f, int fd) : start(s), pf(0), fd(fd), freq(f), size(len) {}
            Node(int pf, char* s, unsigned char len, long f) : start(s), pf(pf), fd(0), freq(f), size(len) {}
            unsigned pf;
            unsigned fd;
            long freq;
            unsigned char size;
            char* start;
        } __attribute__((packed));

        /**
         * \struct Result
         * \brief Résultat type des calculs.
         */
        struct Result
        {
            Result() : word(NULL), freq(0), distance(0), size(0) {}
            Result(char *w, long f, unsigned d, unsigned char len) : word(w), freq(f), distance(d), size(len) {}
            char *word;
            long freq;
            unsigned distance;
            unsigned char size;
        } __attribute__((packed));
    
    public:
        /**
         * \brief Constructeur utilisé pour lire le dictionnaire.
         */
        CPTrieDisk() { nodes.push_back(Node()); }

        /**
         * \brief Constructeur à partir du fichier mot/frequence.
         */
        CPTrieDisk(std::vector<std::string>& words, std::vector<long>& freqs)
        {
            nodes.reserve(words.size() * 2);
            nodes.push_back(Node());
            for (unsigned i = 0; i < words.size(); i++)
                add(words[i], freqs[i]);
        }
        ~CPTrieDisk() {}
        size_t nb_nodes() { return nodes.size() - 1; }
        void add(std::string& word, long freq, unsigned char j = 0);
        void write(std::ostream& os);
        void read(std::istream& is);
        std::vector<Result> distance(char* word, unsigned char size, unsigned max_distance);
        void distance_map(std::map<unsigned, Result>& res, char* word, unsigned char size, unsigned max_distance);
        void distance_rec(char* word, unsigned char size, std::vector<Result>& res, unsigned distance, unsigned index, unsigned char i, unsigned char j, unsigned max_distance, char previous_letter, char word_previous);
        void distance_rec_map(char* current_word, unsigned char cum_size, char* word, unsigned char size, std::map<unsigned, Result>& res, unsigned distance, unsigned index, unsigned char i, unsigned char j, unsigned max_distance, char previous_letter, char word_previous);
        void distance_other(char* word, unsigned char size, std::vector<Result>& res, unsigned distance);
        void distance_rec_other(char* word, unsigned char size, std::vector<Result>& res, unsigned distance, unsigned index, unsigned cum);

    private:
        std::vector<Node> nodes;
};
