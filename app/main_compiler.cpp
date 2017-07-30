#include <cptrie.hpp>
#include <cstring>
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-h"))
    {
        std::cerr << "Usage: " << argv[0] << " /path/to/word/freq.txt /path/to/output/dict.bin" << std::endl;
        return 1;
    }

    std::vector<std::string> w;
    std::vector<long> u;

    std::ifstream file;
    file.open(argv[1]);
    if (! file.is_open())
    {
        std::cerr << "Error: " << argv[1] << " does not exist." << std::endl;
        return 1;
    }

    std::string word;
    long freq;
    while (file >> word)
    {
        file >> freq;
        w.push_back(word);
        u.push_back(freq);
    }
    CPTrie dict(w, u);

    std::fstream binary;
    binary.open(argv[2], std::ios::out | std::ios::binary);
    if (! binary.is_open())
    {
        std::cerr << "Error: can not create " << argv[2] << " file." << std::endl;
        return 1;
    }

    dict.write(binary);
    binary.close();
}
