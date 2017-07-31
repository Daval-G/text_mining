#include <cptriedisk.hpp>
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
 * \fn bool compare(Result r1, Result r2)
 * \brief Compare les résultats.
 *
 * \param sz Chaîne à stocker dans l'objet Str_t, ne peut être NULL.
 * \return Retourne la valeur r1 < r2.
 *
 * Sert à établir une relation d'ordre entre les résultats pour les trier.
 *
 */
bool compare(Result r1, Result r2)
{
    if (r1.distance != r2.distance)
        return r1.distance < r2.distance;
    if (r1.frequence != r2.frequence)
        return r1.frequence > r2.frequence;
    return strcmp(r1.word, r2.word) > 0;
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

        std::map<unsigned, CPTrieDisk::Result> map = dict.distance_map(word, strlen(word), distance);

        std::cout << "OUT" << std::endl;
        std::flush(std::cout);
        
        results = std::vector<std::pair<unsigned, CPTrieDisk::Result>>(map.begin(), map.end());

        std::cout << "OUT" << std::endl;
        std::flush(std::cout);

        std::cout << "[";
        for (auto result: results)
        {
            printf("{\"word\":%.*s,\"freq\":%ld,\"distance\":%u}", result.second.size, result.second.word, result.second.freq, result.second.distance);
            if (&result != &results.back())
                std::cout << ",";
        }
        std::cout << "]" << std::endl;

        results.clear();
    }
}
