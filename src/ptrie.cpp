#include "ptrie.hpp"

void PTrie::get_words(std::vector<std::string>& res, std::string current) const
{
    current += root;
    if (freq)
        res.push_back(current);
    for (auto c:childs)
        c->get_words(res, current);
}

void PTrie::remove(std::string& word)
{
    //TODO
}

void PTrie::add(std::string word, long freq)
{
    bool success;
    for (auto c: childs)
    {
        size_t i;
        for (i = 0; i < word.size() && i < c->get_root().size() && c->get_root()[i] == word[i]; ++i)
            ;;
        if (i > 0)
        {
            if (i < c->get_root().size())
            {
                c->set_root(c->get_root().substr(i, c->get_root().size() - i));
                childs.erase(std::remove(childs.begin(), childs.end(), c), childs.end());
                PTrie *trie = new PTrie(word.substr(0, i), (i == word.size()) ? freq: 0);
                trie->add_child(c);
                if (i != word.size())
                    trie->add_child(new PTrie(std::string(word.substr(i, word.size() - i)), freq));
                childs.push_back(trie);
            }
            else if (i == c->get_root().size() && i < word.size())
                c->add(word.substr(i, word.size() - i), freq);
            else
                c->set_freq(freq);
            return;
        }
    }
    childs.push_back(new PTrie(word, freq));
}
