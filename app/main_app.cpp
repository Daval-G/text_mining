#include <ptrie.hpp>

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "-h"))
    {
        std::cerr << "Usage: " << argv[0] << " /path/to/compiled/dict.bin" << std::endl;
        return 1;
    {

    CPTrie dict;

    std::fstream binary;
    binary.open(argv[1], std::ios::in | std::ios::binary);
    if (! binary.is_open())
        return 1; // TODO

    dict.read(binary);
}
