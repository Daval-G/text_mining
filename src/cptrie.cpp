#include "cptrie.hpp"



void CPTrie::add(std::string& word, long freq, int j)
{
    if (!nodes[0].pf)
    {
        nodes[0].pf = nodes.size();
        nodes.push_back(Node(word, freq));
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
            std::string s = node.edge.substr(i, node.edge.size() - i);
            nodes[index].edge = node.edge.substr(0, i);
            if (i + j == word.size())
            {
                nodes.push_back(Node(node.pf, s, node.freq));
                nodes[index].freq = freq;
                nodes[index].pf = nodes.size() - 1;
            }
            else
            {
                nodes.push_back(Node(node.pf, s, node.freq));
                nodes[index].freq = 0;
                nodes[index].pf = nodes.size();
                nodes.push_back(Node(word.substr(i + j, word.size() - i - j), freq, nodes.size() - 1));
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
    nodes.push_back(Node(word.substr(j, word.size() - j), freq));
}
