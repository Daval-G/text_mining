#include <ptrie.hpp>

int main(int argc, char *argv[])
{
    // Ptrie test
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
    v.clear();
    u.clear();

    // Read test
    if (argc == 0) return 0;

    std::ifstream file;
    file.open(argv[1]);
    if (! file.is_open()) return 1;

    clock_t tStart = clock();

    std::string word;
    unsigned freq;
    while (file >> word)
    {
        file >> freq;
        v.push_back(word);
        u.push_back(freq);
    }
    PTrie dict(v, u);

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
