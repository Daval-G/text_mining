#include <ptrie.hpp>

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int parseLine(char* line)
{
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue()
{
    //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int main(int argc, char *argv[])
{
    // Ptrie test
    std::vector<std::string> v;
    v.push_back("haha");
    v.push_back("halo");
    v.push_back("caca");
    v.push_back("cacao");

    std::vector<long> u;
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
    long freq;
    while (file >> word)
    {
        file >> freq;
        v.push_back(word);
        u.push_back(freq);
    }
    PTrie dict(v, u);
    std::cout << getValue() << "Kb\n";
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
