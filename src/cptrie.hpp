#pragma once

#include <vector>
#include <string>
#include <iostream>

/**
 * \file cptrie.hpp
 * \brief Structure de CPTrie.
 * \author daval-_g moreau_2
 *
 * Déclare la structure CPTrie et ses composants principaux.
 *
 */

/**
 * \class CPTrie
 * \brief Classe contenant tous les noeuds.
 */
class CPTrie
{
    public:
        /**
         * \struct Node
         * \brief Noeud de l'arbre.
         */
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
        /**
         * \brief Constructeur utilisé pour lire le dictionnaire.
         */
        CPTrie() { nodes.push_back(Node()); }

        /**
         * \brief Constructeur à partir du fichier mot/frequence.
         */
        CPTrie(std::vector<std::string>& words, std::vector<long>& freqs)
        {
            nodes.reserve(words.size() * 2);
            nodes.push_back(Node());
            for (unsigned i = 0; i < words.size(); i++)
                add(words[i], freqs[i]);
        }
        ~CPTrie() {}
        size_t nb_nodes() { return nodes.size() - 1; }
        void write(std::ostream& os);
        void read(std::istream& is);
        void add(std::string& word, long freq, int j = 0);
        friend std::ostream& print(std::ostream& stream, const CPTrie& trie, int index);
        friend std::ostream& operator <<(std::ostream& stream, const CPTrie& trie);

    private:
        std::vector<Node> nodes;
};
