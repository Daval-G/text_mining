#include "cptriedisk.hpp"

std::map<unsigned, CPTrieDisk::Result> CPTrieDisk::distance_map(char* word, unsigned char size, unsigned max_distance)
{
    std::map<unsigned, Result> res;
    distance_rec_map(word, size, res, max_distance + 1, 0, 0, 0, max_distance + 1, 0, 0);
    return res;
}

void CPTrieDisk::distance_rec_map(char* word, unsigned char size, std::map<unsigned, Result>& res, unsigned distance, unsigned index, unsigned char i, unsigned char j, unsigned max_distance, char previous_letter, char word_previous)
{
    if (!distance)
        return;
    if (i < nodes[index].size)
    {
        if (j < size && word[j] == nodes[index].start[i])
            distance_rec_map(word, size, res, distance, index, i + 1, j + 1, max_distance, nodes[index].start[i], word[j]);
        if (j < size)
        {
            // Deletion
            distance_rec_map(word, size, res, distance - 1, index, i, j + 1, max_distance, previous_letter, word[j]);
            // Replace
            distance_rec_map(word, size, res, distance - 1, index, i + 1, j + 1, max_distance, nodes[index].start[i], word[j]);
        }
        // Swap
        if (previous_letter && word_previous)
        {
            if (word[j] == previous_letter && word_previous == nodes[index].start[i])
                distance_rec_map(word, size, res, distance, index, i + 1, j + 1, max_distance, nodes[index].start[i], word_previous);
            distance_rec_map(word, size, res, distance - 1, index, i + 1, j + 1, max_distance, nodes[index].start[i], word_previous);
        }
        // Insertion
        distance_rec_map(word, size, res, distance - 1, index, i + 1, j, max_distance, nodes[index].start[i], word_previous);
    }
    else
    {
        if (nodes[index].freq && j == size)
            if (res.find(index) == res.end())
                res[index] = Result(nodes[index].start, nodes[index].freq, max_distance - distance, nodes[index].size);
            else if (res[index].distance > distance)
                res[index].distance = distance;
        unsigned new_index = nodes[index].pf;
        while (nodes[new_index].start)
        {
            distance_rec_map(word, size, res, distance, new_index, 0, j, max_distance, previous_letter, word_previous);
            new_index = nodes[new_index].fd;
        }
    }
}

std::vector<CPTrieDisk::Result> CPTrieDisk::distance(char* word, unsigned char size, unsigned max_distance)
{
    std::vector<Result> res;
    distance_rec(word, size, res, max_distance + 1, 0, 0, 0, max_distance + 1, 0, 0);
    return res;
}

void CPTrieDisk::distance_rec(char* word, unsigned char size, std::vector<Result>& res, unsigned distance, unsigned index, unsigned char i, unsigned char j, unsigned max_distance, char previous_letter, char word_previous)
{
    if (!distance)
        return;
    if (i < nodes[index].size)
    {
        if (j < size && word[j] == nodes[index].start[i])
            distance_rec(word, size, res, distance, index, i + 1, j + 1, max_distance, nodes[index].start[i], word[j]);
        if (j < size)
        {
            // Deletion
            distance_rec(word, size, res, distance - 1, index, i, j + 1, max_distance, previous_letter, word[j]);
            // Replace
            distance_rec(word, size, res, distance - 1, index, i + 1, j + 1, max_distance, nodes[index].start[i], word[j]);
        }
        // Swap
        if (previous_letter && word_previous)
        {
            if (word[j] == previous_letter && word_previous == nodes[index].start[i])
                distance_rec(word, size, res, distance, index, i + 1, j + 1, max_distance, nodes[index].start[i], word_previous);
            distance_rec(word, size, res, distance - 1, index, i + 1, j + 1, max_distance, nodes[index].start[i], word_previous);
        }
        // Insertion
        distance_rec(word, size, res, distance - 1, index, i + 1, j, max_distance, nodes[index].start[i], word_previous);
    }
    else
    {
        if (nodes[index].freq && j == size)
            res.push_back(Result(nodes[index].start, nodes[index].freq, max_distance - distance, nodes[index].size));
        unsigned new_index = nodes[index].pf;
        while (nodes[new_index].start)
        {
            distance_rec(word, size, res, distance, new_index, 0, j, max_distance, previous_letter, word_previous);
            new_index = nodes[new_index].fd;
        }
    }
}

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

void CPTrieDisk::write(std::ostream& os)
{
    typename std::vector<Node>::size_type size = nodes.size();
    os.write((char*)&size, sizeof(size));
    for (auto i = 0; i < size; ++i)
    {
        os.write((char*)&nodes[i], 2 * sizeof(unsigned) + sizeof(long));
        os.write((char*)&nodes[i].size, 1);
        os.write((char*)&nodes[i].start, nodes[i].size);
    }
}

void CPTrieDisk::read(std::istream& is)
{
    typename std::vector<Node>::size_type size = 0;
    is.read((char*)&size, sizeof(size));
    nodes.resize(size);
    for (auto i = 0; i < size; ++i)
    {
        is.read((char*)&nodes[i], 2 * sizeof(unsigned) + sizeof(long));
        is.read((char*)&nodes[i].size, 1);
        is.read((char*)&nodes[i].start, nodes[i].size);
    }
}
