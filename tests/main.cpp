#include <cptriedisk.hpp>
#include <cptrie.hpp>
#include <ptrie.hpp>

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <fstream>
#ifdef __APPLE__
#include <mach/mach_host.h>
#include <mach/task.h>
#endif /* __APPLE__ */

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

void getValue()
{
    #ifdef __APPLE__
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (KERN_SUCCESS != task_info(mach_task_self(),
                TASK_BASIC_INFO, (task_info_t)&t_info, 
                &t_info_count))
    {
        return;
    }
    std::cout << "res size: " << t_info.resident_size << std::endl;
    std::cout << "virtual size: " << t_info.virtual_size << std::endl;

    #else
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
    std::cout << result << "Kb" << std::endl;
    #endif
}

int main(int argc, char *argv[])
{
    // Ptrie test
    std::vector<std::string> v;
    v.push_back("haha");
    v.push_back("hahi");
    v.push_back("haha");
    v.push_back("hahu");
    v.push_back("halo");
    v.push_back("caca");
    v.push_back("cacao");

    std::vector<long> u;
    u.push_back(10);
    u.push_back(56);
    u.push_back(1);
    u.push_back(2);
    u.push_back(3);
    u.push_back(4);
    u.push_back(697);

    CPTrieDisk trie(v, u);
    std::cout << "size: " << sizeof(CPTrieDisk::Node) << std::endl;

    v.clear();
    u.clear();

    // Read test
    if (argc == 1) return 0;

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
    CPTrieDisk dict(v, u);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    std::cout << "Nb nodes: " << dict.nb_nodes() << std::endl;
    getValue();

    tStart = clock();
    std::ofstream writer;
    writer.open("dict.bin", std::ios::out | std::ios::binary);
    dict.write(writer);
    writer.close();
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    tStart = clock();
    std::ifstream reader;
    reader.open("dict.bin", std::ios::in | std::ios::binary);
    dict = CPTrieDisk();
    dict.read(reader);
    reader.close();
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    std::cout << "Nb nodes: " << dict.nb_nodes() << std::endl;
    
    return 0;
}
