#include "cptrie.hpp"

/**
 * \file cptrie.cpp
 * \brief Implémente les méthodes principales du CPTrie.
 * \author daval-_g moreau_2
 */

/**
 * \fn void CPTrie::add(std::string& word, long freq, int j)
 * \brief Ajoute un mot à l'arbre.
 *
 * \param word Mot à ajouter.
 * \param freq Fréquence du mot.
 * \param j Indice d'avancement sur la string.
 */
void CPTrie::add(std::string& word, long freq, int j)
{
    if (!nodes[0].pf)
    {
        nodes[0].pf = nodes.size();
        nodes.push_back(Node(word, freq));
        return;
    }
    Node *node = &nodes[nodes[0].pf];
    int index = nodes[0].pf;
    while (node->edge != "")
    {
        size_t i;
        for (i = 0; i + j < word.size() && i < node->edge.size() && node->edge[i] == word[i + j]; ++i)
            ;;
        if (!i)
        {
            if (nodes[node->fd].edge != "")
                index = node->fd;
            node = &nodes[node->fd];
            continue;
        }
        if (i < node->edge.size())
        {
            std::string s = node->edge.substr(i, node->edge.size() - i);
            nodes[index].edge = node->edge.substr(0, i);
            if (i + j == word.size())
            {
                nodes.push_back(Node(node->pf, s, node->freq));
                nodes[index].freq = freq;
                nodes[index].pf = nodes.size() - 1;
            }
            else
            {
                nodes.push_back(Node(node->pf, s, node->freq));
                nodes[index].freq = 0;
                nodes[index].pf = nodes.size();
                nodes.push_back(Node(word.substr(i + j, word.size() - i - j), freq, nodes.size() - 1));
            }
            return;
        }
        else if (i == node->edge.size() && i + j < word.size())
        {
            j += i;
            if (node->pf)
            {
                index = node->pf;
                node = &nodes[node->pf];
            }
            else
            {
                nodes[index].pf = nodes.size();
                nodes.push_back(Node(word.substr(j, word.size() - j), freq));
                return;
            }
        }
        else
        {
            nodes[index].freq = freq;
            return;
        }
    }
    nodes[index].fd = nodes.size();
    nodes.push_back(Node(word.substr(j, word.size() - j), freq));
}

/**
 * \fn std::ostream& print(std::ostream& stream, const CPTrie& trie, int index)
 * \brief Affichage de l'arbre.
 *
 * \param stream Stream dans lequel afficher l'arbre.
 * \param trie Arbre à écrire.
 * \param Index à partir duquel afficher l'arbre.
 * \return La valeur du digit.
 */
std::ostream& print(std::ostream& stream, const CPTrie& trie, int index)
{
    stream << trie.nodes[index].edge << ":" << trie.nodes[index].freq;
    CPTrie::Node n = trie.nodes[trie.nodes[index].pf];
    int current = trie.nodes[index].pf;
    while (n.edge != "")
    {
        stream << "(";
        print(stream, trie, current);
        stream << ")";
        current = n.fd;
        n = trie.nodes[n.fd];
    }
    return stream;
}

/**
 * \fn std::ostream& operator <<(std::ostream& stream, const CPTrie& trie)
 * \brief Opérateur de stream.
 *
 * \param stream Stream dans lequel afficher l'arbre.
 * \param trie Arbre à écrire.
 * \return Le stream utilisé après écriture.
 *
 */
std::ostream& operator <<(std::ostream& stream, const CPTrie& trie)
{
    return print(stream, trie, 0);
}

/**
 * \fn void CPTrie::write(std::ostream& os)
 * \brief Enregistre les données sur disque.
 *
 * \param os Output stream dans lequel écrire la structure.
 */
void CPTrie::write(std::ostream& os)
{
    typename std::vector<Node>::size_type size = nodes.size();
    os.write((char*)&size, sizeof(size));
    os.write((char*)&nodes[0], nodes.size() * sizeof(Node));
}

/**
 * \fn void CPTrie::read(std::istream& is)
 * \brief Récupère les données sur disque.
 *
 * \param is Input stream depuis lequel lire la structure.
 */
void CPTrie::read(std::istream& is)
{
    typename std::vector<Node>::size_type size = 0;
    is.read((char*)&size, sizeof(size));
    nodes.resize(size);
    is.read((char*)&nodes[0], nodes.size() * sizeof(Node));
}
