#include "cptriedisk.hpp"


void CPTrieDisk::add(std::string& word, long freq, int j)
{
    if (!nodes[0].pf)
    {
        nodes[0].pf = nodes.size();
        nodes.push_back(Node(&word[0], word.size(), freq));
        return;
    }
    Node *node = &nodes[nodes[0].pf];
    int index = nodes[0].pf;
    while (node->start)
    {
        char i;
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
            short len = node->size - i;
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
        os.write((char*)&nodes[i].size, sizeof(char));
        os.write((char*)&nodes[i].start, nodes[i].size * sizeof(char));
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
        is.read((char*)&nodes[i].size, sizeof(char));
        is.read((char*)&nodes[i].start, nodes[i].size * sizeof(char));
    }
}