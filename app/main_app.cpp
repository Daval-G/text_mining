#include <cptriedisk.hpp>
#include <cstdlib>
#include <cstring>
#include <fstream>

void error_app(char *argv[])
{
    std::cerr << "Usage: " << argv[0] << " /path/to/compiled/dict.bin" << std::endl;
    exit(EXIT_FAILURE);
}

bool compare(Result r1, Result r2)
{
    if (r1.distance != r2.distance)
        return r1.distance < r2.distance;
    if (r1.frequence != r2.frequence)
        return r1.frequence > r2.frequence;
    return strcmp(r1.word, r2.word) > 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || ! strcmp(argv[1], "-h"))
        error_app(argv);

    CPTrieDisk dict;

    std::ifstream binary;
    binary.open(argv[1], std::ios::in | std::ios::binary);
    if (! binary.is_open())
        error_app(argv);

    dict.read(binary);
}
