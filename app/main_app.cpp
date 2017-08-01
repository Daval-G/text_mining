#include <cptriedisk.hpp>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

/**
 * \file main_app.cpp
 * \brief Pour les requêtes.
 * \author daval-_g moreau_2
 *
 * Programme pour effectuer des requêtes sur le dictionnaire compilé.
 *
 */

/**
 * \fn void error_app(char *argv[])
 * \brief Gestion des erreurs.
 *
 * \param argv Liste des arguments en entrée. Seul argv[0] est utilisé.
 *
 * Affiche le message d'erreur et sort du programme.
 *
 */
void error_app(char *argv[])
{
    std::cerr << "Usage: " << argv[0] << " /path/to/compiled/dict.bin" << std::endl;
    exit(EXIT_FAILURE);
}

/**
 * \fn bool strcmp_compare(Result r1, Result r2)
 * \brief Compare les chaines sans \0.
 *
 * \param r1 Première chaine à comparer.
 * \param r2 Seconde chaine à comparer.
 * \return Retourne la valeur w1 < w2.
 */
bool strcmp_ranged(const char *w1, const char *w2, unsigned s1, unsigned s2)
{
    while(s1 && s2 && (*w1 == *w2))
    {
        w1++;
        w2++;
        s1--;
        s2--;
    }

    if (s1 == 0 || s2 == 0)
        return ! (s2 == 0);
    return (*(const unsigned char*) w1 - *(const unsigned char*) w2) < 0;
}

/**
 * \fn bool compare(Result r1, Result r2)
 * \brief Compare les résultats.
 *
 * \param r1 Premier résultat à comparer.
 * \param r2 Second résultat à comparer.
 * \return Retourne la valeur r1 < r2.
 *
 * Sert à établir une relation d'ordre entre les résultats pour les trier.
 *
 */
bool compare(std::pair<unsigned, CPTrieDisk::Result> r1,
             std::pair<unsigned, CPTrieDisk::Result> r2)
{
    if (r1.second.distance != r2.second.distance)
        return r1.second.distance < r2.second.distance;
    if (r1.second.freq != r2.second.freq)
        return r1.second.freq > r2.second.freq;
    return strcmp_ranged(r1.second.word, r2.second.word, r1.second.size, r2.second.size);
}

/**
 * \fn int main(int argc, char *argv[])
 * \brief Répond aux requêtes.
 *
 * \param argc Nombre d'arguments en entrée de l'executable.
 * \param argv Liste des arguments passés par l'utilisateur.
 *
 * Le programme lit le fichier dictionnaire passé en argument,
 * puis répond aux requêtes.
 *
 */
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

    std::string token;
    unsigned distance;
    char *word;
    std::vector<std::pair<unsigned, CPTrieDisk::Result>> results;
    while (std::cin >> token && token == "approx") {
        std::cin >> distance;
        std::cin >> token;
        word = &token[0];

        std::map<unsigned, CPTrieDisk::Result> map;
        dict.distance_map(map, word, strlen(word), distance);
        results = std::vector<std::pair<unsigned, CPTrieDisk::Result>>(map.begin(), map.end());
        std::sort(results.begin(), results.end(), compare);

        auto last = results[results.size() - 1];
        std::cout << "[";
        for (auto result: results)
        {
            printf("{\"word\":\"%.*s\",\"freq\":%ld,\"distance\":%u}", result.second.size, result.second.word, result.second.freq, result.second.distance);
            if (result.first != last.first)
                std::cout << ",";
        }
        std::cout << "]" << std::endl;

        results.clear();
    }
}
