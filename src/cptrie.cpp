#include "cptrie.hpp"



void CPTrie::add(std::string word, long freq, int j)
{
    if (!nodes[0].pf)
    {
        nodes[0].pf = nodes.size();
        Node new_node;
        new_node.edge = word;
        new_node.freq = freq;
        nodes.push_back(new_node);
        return;
    }
    Node node = nodes[nodes[0].pf];
    int index = nodes[0].pf;
    while (node.edge != "")
    {
        size_t i;
        for (i = 0; i + j < word.size() && i < node.edge.size() && node.edge[i] == word[i + j]; ++i)
            ;;
        if (!i)
        {
            if (nodes[node.fd].edge != "")
                index = node.fd;
            node = nodes[node.fd];
            continue;
        }
        if (i < node.edge.size())
        {
            Node inter;
            inter.edge = node.edge.substr(i, node.edge.size() - i);
            nodes[index].edge = node.edge.substr(0, i);
            if (i + j == word.size())
            {
                inter.pf = node.pf;
                inter.freq = node.freq;
                nodes[index].freq = freq;
                nodes[index].pf = nodes.size();
                nodes.push_back(inter);
            }
            else
            {
                Node new_node;
                new_node.freq = freq;
                new_node.edge = word.substr(i + j, word.size() - i - j);
                inter.freq = node.freq;
                nodes[index].freq = 0;
                inter.pf = node.pf;
                nodes[index].pf = nodes.size();
                new_node.fd = nodes.size() + 1;
                nodes.push_back(new_node);
                nodes.push_back(inter);
            }
            return;
        }
        else if (i == node.edge.size() && i + j < word.size())
        {
            j += i;
            if (nodes[node.fd].edge != "")
                index = node.pf;
            node = nodes[node.pf];
        }
        else
        {
            nodes[index].freq = freq;
            return;
        }
    }
    nodes[index].fd = nodes.size();
    Node new_node;
    new_node.edge = word.substr(j, word.size() - j);
    new_node.freq = freq;
    nodes.push_back(new_node);
}
