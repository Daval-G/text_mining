#include <ptrie.hpp>

int main()
{
    std::vector<std::string> v;
    v.push_back("haha");
    v.push_back("halo");
    v.push_back("caca");
    v.push_back("cacao");
    PTrie trie(v);
    std::cout << trie << std::endl;
    std::vector<std::string> words;
    trie.get_words(words);
    for (auto w: words)
        std::cout << w << " ";
    std::cout << std::endl;
    return 0;
}
