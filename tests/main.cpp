#include <cptriedisk.hpp>

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <fstream>
#ifdef __APPLE__
#include <mach/mach_host.h>
#include <mach/task.h>
#endif /* __APPLE__ */

/**
 * \file main.cpp
 * \brief Programme de tests.
 * \author daval-_g moreau_2
 *
 * Programme pour effectuer les tests de construction basiques.
 *
 */

/**
 * \fn int parseLine(char* line)
 * \brief Permet de lire une ligne.
 *
 * \param line Buffer dans lequel la ligne est écrite.
 * \return La valeur du digit.
 *
 */
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

/**
 * \fn void getValue()
 * \brief Affiche la consommation RAM.
 */
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
    std::cout << "Memory:\t" << result << "KB" << std::endl;
    #endif
}

void test_performances(CPTrieDisk dict)
{
    char wor[7] = {'b','o','n','j','o','u','r'};
    std::cout << "Distance 0: " << std::endl;
    clock_t tStart = clock();
    for (int i = 0; i < 3000; ++i)
    {
        std::map<unsigned, CPTrieDisk::Result> my_map;
        dict.distance_map(my_map, wor, 7, 0);
    }
    printf("Time:\t%.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    std::cout << "Distance 1: " << std::endl;
    tStart = clock();
    for (int i = 0; i < 300; ++i)
    {
        std::map<unsigned, CPTrieDisk::Result> my_map;
        dict.distance_map(my_map, wor, 7, 1);
    }
    printf("Time:\t%.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    std::cout << "Distance 2: " << std::endl;
    tStart = clock();
    for (int i = 0; i < 30; ++i)
    {
        std::map<unsigned, CPTrieDisk::Result> my_map;
        dict.distance_map(my_map, wor, 7, 2);
    }
    printf("Time:\t%.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    std::cout << "Distance 3: " << std::endl;
    tStart = clock();
    for (int i = 0; i < 10; ++i)
    {
        std::map<unsigned, CPTrieDisk::Result> my_map;
        dict.distance_map(my_map, wor, 7, 3);
    }
    printf("Time:\t%.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

}

/**
 * \fn int main(int argc, char *argv[])
 * \brief Effectue les tests.
 *
 * \param argc Nombre d'arguments en entrée de l'executable.
 * \param argv Liste des arguments passés par l'utilisateur.
 */
int main(int argc, char *argv[])
{
    // STRUCTURE TEST
    std::vector<std::string> v;
    v.push_back("dioups");
    v.push_back("dioup");
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

    std::cout << "Structure size:\t" << sizeof(CPTrieDisk::Node) << std::endl;

    v.clear();
    u.clear();

    if (argc == 1) return 0;

    std::ifstream file;
    file.open(argv[1]);
    if (! file.is_open()) return 1;

    // GENERATION TEST
    std::cout << "Génération de la structure:" << std::endl;
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
    printf("Time:\t%.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    std::cout << "Nodes:\t" << dict.nb_nodes() << std::endl;
    getValue();

    // WRITING TEST
    std::cout << "Ecriture de la structure sur le disque:" << std::endl;
    tStart = clock();
    std::ofstream writer;
    writer.open("dict.bin", std::ios::out | std::ios::binary);
    dict.write(writer);
    writer.close();
    printf("Time:\t%.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    test_performances(dict);

    // READING TEST
    std::cout << "Lecture de la structure depuis le disque:" << std::endl;
    tStart = clock();
    std::ifstream reader;
    reader.open("dict.bin", std::ios::in | std::ios::binary);
    dict = CPTrieDisk();
    dict.read(reader);
    reader.close();
    printf("Time:\t%.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    std::cout << "Nodes:\t" << dict.nb_nodes() << std::endl;
    test_performances(dict);
    
    return 0;
}
