#include "cptriedisk.hpp"

/**
 * \file cptriedisk.cpp
 * \brief Implémente les méthodes principales du CPTrieDisk.
 * \author daval-_g moreau_2
 */

/**
 * \fn void CPTrieDisk::distance_map(std::map<unsigned, Result>& res, char* word, unsigned char size, unsigned max_distance)
 * \brief Calcule les mots à une certaine distance.
 *
 * \param word Mot de référence.
 * \param size Taille du mot.
 * \param max_distance Distance maximale autorisée.
 * \return Une map de tous les résultats.
 */
void CPTrieDisk::distance_map(std::map<unsigned, Result>& res, char* word, unsigned char size, unsigned max_distance)
{
    char* current_word = new char[256];
    distance_rec_map(current_word, 0, word, size, res, max_distance + 1, 0, 0, 0, max_distance + 1, 0, 0);
}

/**
 * \fn void CPTrieDisk::distance_rec_map(char* current_word, unsigned char cum_size, char* word, unsigned char size, std::map<unsigned, Result>& res, unsigned distance, unsigned index, unsigned char i, unsigned char j, unsigned max_distance, char previous_letter, char word_previous)
 * \brief Traite récursivement les distances.
 */
void CPTrieDisk::distance_rec_map(char* current_word, unsigned char cum_size, char* word, unsigned char size, std::map<unsigned, Result>& res, unsigned distance, unsigned index, unsigned char i, unsigned char j, unsigned max_distance, char previous_letter, char word_previous)
{
    if (!distance)
        return;
    // Deletion
    if (j < size)
        distance_rec_map(current_word, cum_size, word, size, res, distance - 1, index, i, j + 1, max_distance, previous_letter, word[j]);
    if (i < nodes[index].size)
    {
        if (j < size)
        {
            // Replace
            distance_rec_map(current_word, cum_size, word, size, res, distance - 1, index, i + 1, j + 1, max_distance, nodes[index].start[i], word[j]);
            if (word[j] == nodes[index].start[i])
                distance_rec_map(current_word, cum_size, word, size, res, distance, index, i + 1, j + 1, max_distance, nodes[index].start[i], word[j]);
            // Swap
            if (word[j] == previous_letter && word_previous == nodes[index].start[i])
                distance_rec_map(current_word, cum_size, word, size, res, distance, index, i + 1, j + 1, max_distance, nodes[index].start[i], word_previous);
        }
        // Insertion
        distance_rec_map(current_word, cum_size, word, size, res, distance - 1, index, i + 1, j, max_distance, nodes[index].start[i], nodes[index].start[i]);
    }
    else
    {
        if (nodes[index].freq && j == size)
        {
            if (res.find(index) == res.end())
            {
                char* result = new char[cum_size];
                memcpy(result, current_word, cum_size);
                res[index] = Result(result, nodes[index].freq, max_distance - distance, cum_size);
            }
            else if (res[index].distance > max_distance - distance)
                res[index].distance = max_distance - distance;
        }
        unsigned new_index = nodes[index].pf;
        while (nodes[new_index].start)
        {
            memcpy(current_word + cum_size, nodes[new_index].start, nodes[new_index].size);
            distance_rec_map(current_word, cum_size + nodes[new_index].size, word, size, res, distance, new_index, 0, j, max_distance, previous_letter, word_previous);
            new_index = nodes[new_index].fd;
        }
    }
}

/**
 * \fn void CPTrieDisk::add(std::string& word, long freq, int j)
 * \brief Ajoute un mot à l'arbre.
 *
 * \param word Mot à ajouter.
 * \param freq Fréquence du mot.
 * \param j Indice d'avancement sur la string.
 */
void CPTrieDisk::add(std::string& word, long freq, unsigned char j)
{
    if (!nodes[0].pf)
    {
        nodes[0].pf = nodes.size();
        nodes.push_back(Node(&word[0], word.size(), freq));
        return;
    }
    Node *node = &nodes[nodes[0].pf];
    unsigned index = nodes[0].pf;
    while (node->start)
    {
        unsigned char i;
        for (i = 0; i + j < word.size() && i < node->size && node->start[i] == word[i + j]; ++i)
            ;;
        if (!i)
        {
            if (nodes[node->fd].start)
                index = node->fd;
            node = &nodes[node->fd];
            continue;
        }
        if (i < node->size)
        {
            unsigned char len = node->size - i;
            nodes[index].size = i;
            if (i + j == word.size())
            {
                nodes.push_back(Node(node->pf, node->start + i, len, node->freq));
                nodes[index].freq = freq;
                nodes[index].pf = nodes.size() - 1;
            }
            else
            {
                nodes.push_back(Node(node->pf, node->start + i, len, node->freq));
                nodes[index].freq = 0;
                nodes[index].pf = nodes.size();
                nodes.push_back(Node(&word[i + j], word.size() - i - j, freq, nodes.size() - 1));
            }
            return;
        }
        else if (i == node->size && i + j < word.size())
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
                nodes.push_back(Node(&word[j], word.size() - j, freq));
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
    nodes.push_back(Node(&word[j], word.size() - j, freq));
}

/**
 * \fn void CPTrieDisk::write(std::ostream& os)
 * \brief Enregistre les données sur disque.
 *
 * \param os Output stream dans lequel écrire la structure.
 */
void CPTrieDisk::write(std::ostream& os)
{
    typename std::vector<Node>::size_type size = nodes.size();
    os.write((char*)&size, sizeof(size));
    for (std::vector<Node>::size_type i = 0; i < size; ++i)
    {
        os.write((char*)&nodes[i].pf, sizeof(unsigned));
        os.write((char*)&nodes[i].fd, sizeof(unsigned));
        os.write((char*)&nodes[i].freq, sizeof(long));
        os.write((char*)&nodes[i].size, sizeof(unsigned char));
        os.write(nodes[i].start, nodes[i].size * sizeof(char));
    }
}

/**
 * \fn void CPTrieDisk::read(std::istream& is)
 * \brief Récupère les données sur disque.
 *
 * \param is Input stream depuis lequel lire la structure.
 */
void CPTrieDisk::read(std::istream& is)
{
    typename std::vector<Node>::size_type size = 0;
    is.read((char*)&size, sizeof(size));
    nodes.resize(size);
    for (std::vector<Node>::size_type i = 0; i < size; ++i)
    {
        is.read((char*) &nodes[i].pf, sizeof(unsigned));
        is.read((char*) &nodes[i].fd, sizeof(unsigned));
        is.read((char*) &nodes[i].freq, sizeof(long));
        is.read((char*) &nodes[i].size, sizeof(unsigned char));
        nodes[i].start = new char[nodes[i].size];
        is.read(nodes[i].start, nodes[i].size * sizeof(char));
    }
    nodes[0].start = NULL;
}
