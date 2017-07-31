#include <ptrie.hpp>
#include <cstdlib>

void error_app(char *argv[])
{
    std::cerr << "Usage: " << argv[0] << " /path/to/compiled/dict.bin" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "-h"))
        error_app(argv);

    CPTrie dict;

    std::fstream binary;
    binary.open(argv[1], std::ios::in | std::ios::binary);
    if (! binary.is_open())
        error_app(argv);

    dict.read(binary);
}
