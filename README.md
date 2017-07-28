=============
Projet TMLN 1
=============

Sujet:
======
 * construire un outil en ligne de commande de correction orthographique rapide et stable en utilisant une distance de Damerau-Levenshtein
 * par groupe de 2 personnes

Projet:
=======
 * pour compiler le projet: "cmake .; make"
 * pour utiliser les deux binaires générés:
   1.     TextMiningCompiler <path to words.txt> <path to dict.bin>
   2.     TextMiningApp      <path to dict.bin>
   Le premier génère un dictionnaire compilé en prenant en entrée une liste mots/fréquences. Le second utilise le dictionnaire pour répondre à des requêtes selon le format suivant:
     * echo "approx 0 test" | ./TextMiningApp <path to dict.bin>
     * echo "approx 0 test\napprox 2 test" | ./TextMiningApp <path to dict.bin>
     * cat test.txt | ./TextMiningApp <path to dict.bin>


Remarques:
==========
 * les programmes ne consomment jamais plus de 512Mo de RAM
 * la réponse est au format JSON
 * les résultats sont triés par:
   1.     distance croissante
   2.     fréquence décroissante
   3.     ordre lexicographique croissant

Questions:
==========
 1.     Decrivez les choix de design de votre programme



 2.     Listez l’ensemble des tests effectués sur votre programme (en plus des units tests)



 3.     Avez-vous détecté des cas où la correction par distance ne fonctionnait pas (même avec une distance élevée) ?



 4.     Quelle est la structure de données que vous avez implémentée dans votre projet, pourquoi ?



 5.     Proposez un réglage automatique de la distance pour un programme qui prend juste une chaîne de caractères en entrée, donner le processus d’évaluation ainsi que les résultats



 6.     Comment comptez vous améliorer les performances de votre programme



 7.     Que manque-t-il à votre correcteur orthographique pour qu’il soit à l’état de l’art ?


