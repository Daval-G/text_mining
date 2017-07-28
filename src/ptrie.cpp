#include "ptrie.hpp"

int PTrie::nb_nodes()
{
    int res = 1;
    for (auto &c: childs)
        res += c->nb_nodes();
    return res;
}

void PTrie::get_words(std::vector<std::string>& res, std::string current) const
{
    current += root;
    if (freq)
        res.push_back(current);
    for (auto &c: childs)
        c->get_words(res, current);
}

bool PTrie::remove(std::string& word, int j)
{
    for (auto &c : childs)
    {
        size_t i;
        for (i = 0; i + j < word.size() && i < c->get_root().size() && c->get_root()[i] == word[i + j]; ++i)
            ;;
        if (!i)
            continue;
        if (i < c->get_root().size())
            return false;
        else if (i == c->get_root().size() && i + j < word.size())
            return c->remove(word, i + j);
        else
            childs.erase(std::remove(childs.begin(), childs.end(), c), childs.end());
        return true;
    }
    return false;
}

void PTrie::distance(std::string& word)
{
    //TODO
}

void PTrie::add(std::string& word, long freq, int j)
{
    for (auto &c: childs)
    {
        size_t i;
        for (i = 0; i + j < word.size() && i < c->get_root().size() && c->get_root()[i] == word[i + j]; ++i)
            ;;
        if (!i)
            continue;
        if (i < c->get_root().size())
        {
            c->set_root(c->get_root().substr(i, c->get_root().size() - i));
            childs.erase(std::remove(childs.begin(), childs.end(), c), childs.end());
            PTrie *trie = new PTrie(word.substr(j, i), (i + j) == word.size() ? freq : 0);
            trie->add_child(c);
            if (i + j != word.size())
                trie->add_child(new PTrie(std::string(word.substr(i + j, word.size() - i - j)), freq));
            childs.push_back(trie);
        }
        else if (i == c->get_root().size() && i + j < word.size())
            c->add(word, freq, i + j);
        else
            c->set_freq(freq);
        return;
    }
    childs.push_back(new PTrie(word.substr(j, word.size() - j), freq));
}
