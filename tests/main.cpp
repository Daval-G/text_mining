#include <ptrie.hpp>

int main()
{
    std::vector<std::string> v;
    v.push_back("haha");
    v.push_back("halo");
    v.push_back("caca");
    v.push_back("cacao");

    std::vector<unsigned> u;
    u.push_back(10);
    u.push_back(56);
    u.push_back(1);
    u.push_back(697);

    PTrie trie(v, u);
    std::cout << trie << std::endl;
    std::vector<std::string> words;
    trie.get_words(words);
    for (auto w: words)
        std::cout << w << " ";
    std::cout << std::endl;
    return 0;
}
