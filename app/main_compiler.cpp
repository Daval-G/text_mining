#include <cptriedisk.hpp>
#include <cstring>
#include <cstdlib>
#include <fstream>

void error_compiler(char *argv[])
{
    std::cerr << "Usage: " << argv[0] << " /path/to/word/freq.txt /path/to/output/dict.bin" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-h"))
        error_compiler(argv);

    std::vector<std::string> w;
    std::vector<long> u;

    std::ifstream file;
    file.open(argv[1]);
    if (! file.is_open())
        error_compiler(argv);

    std::string word;
    long freq;
    while (file >> word)
    {
        file >> freq;
        w.push_back(word);
        u.push_back(freq);
    }
    CPTrieDisk dict(w, u);

    std::fstream binary;
    binary.open(argv[2], std::ios::out | std::ios::binary);
    if (! binary.is_open())
        error_compiler(argv);

    dict.write(binary);
    binary.close();
    std::cout << "Size structure: 4" << std::endl;
}
