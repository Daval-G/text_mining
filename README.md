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

La structure implémentée est un Patricia Trie compilé. Cette structure permet une bonne économie de noeuds par rapport à un trie classique, tout en restant une bonne structure pour appliquer une distance de Damerau-Levenshtein.

Les noeuds sont composés de:
- 1 long: la fréquence d'un mot
- 2 unsigned: l'indice du premier fils, ainsi que l'indice du frère droit
- 1 short: la taille de la chaine de caractère
- 1 char*: un pointeur vers la chaine de caractère

Plusieurs remarques:
- La fréquence est un long car la plus haute fréquence dans le dictionnaire est 2147483647. Elle sert également à décrire si un noeud représente un mot ou non.
- Les adresses du premier fils et du frère droit font référence à l'indice du std::vector, donc pas besoin d'aller chercher au delà de 4 294 967 295.
- La taille de la chaine de caractère est un short car le mot de taille maximale fait 176 caractères, mais que vous êtes peut-ête fourbe, et que de toute façon avec le padding peu importe d'avoir un char ou un short.
- La taille de la chaine de caractère est stockée pour plusieurs raisons:
    - à la compilation, plutôt que de copier les chaines de caractères, on peut juste pointer vers des bouts des mots du dictionnaire qu'on a chargé en mémoire. Il faut alors juste la taille pour combler le manque de '\0'. Cette amélioration nous a divisé par 1.5 la consommation mémoire, et a amélioré le temps de création de la structure par 2.
    - lors des requêtes, il est plus pratique de charger le fichier en mémoire en connaissant la taille des chaines plutôt qu'en la déterminant en controlant les '\0'.

Les données sont sauvegardées sur disque en binaire au format suivant, avec en entête le nombre de noeuds:
(1) fréquence d'un mot (2) indice du premier fils (3) indice du frère droit (4) taille de la chaine (5) les caractères

 2.     Listez l’ensemble des tests effectués sur votre programme (en plus des units tests)

Tests automatiques (comparaison avec la ref):
- Mot dans le dictionnaire initial à distance 0
- Mot absent du dictionnaire initial à distance 0
- Test d'intégrité de la structure sur quelques mots
- Temps de compilation
- Temps de requêtes
- Tests aléatoires (avec seed) sur des milliers de mots présents dans le dictionnaire de distance 0 à 2

Tests manuels:
- Mémoire consommée à la compilation
- Mémoire consommée lors des requêtes

 3.     Avez-vous détecté des cas où la correction par distance ne fonctionnait pas (même avec une distance élevée) ?

Il faut définir ce que signifie "ne pas fonctionner". Faire des requêtes sur des mots de 3000 caractères ne sera jamais concluant, de même que de chercher à obtenir un mot qui n'est pas dans le dictionnaire initial.

 4.     Quelle est la structure de données que vous avez implémentée dans votre projet, pourquoi ?

La structure implémentée est un Patricia Trie compilé. Cette structure permet une bonne économie de noeuds par rapport à un trie classique, tout en restant par construction une bonne structure pour appliquer une distance de Damerau-Levenshtein. Les différentes complexités sont indépendantes du nombre de mots insérés, tout en permettant une économie potentielle de place par rapport au dictionnaire initial.

 5.     Proposez un réglage automatique de la distance pour un programme qui prend juste une chaîne de caractères en entrée, donner le processus d’évaluation ainsi que les résultats

On peut utiliser pour commencer une simple gaussienne, voire même des GMMs. En effet, avec des moyennes et des écarts-types sur la longueur des chaines, on peut, à l'aide seuils de probabilité arbitraires ou donnés en arguments supplémentaires:
- déterminer à partir de quand augmenter la distance devient inintéressant.
- déterminer à partir de quand une distance devient suffisante pour espérer un résultat.

 6.     Comment comptez vous améliorer les performances de votre programme ?

Plusieurs pistes à explorer:
- ordonner les noeuds: actuellement, les noeuds sont organisés de façon relativement arbitraire selon les entrées du dictionnaire. On pourrait les trier de façon à optimiser des parcours en BFS, en DFS, ou tout autre organisation logique, et observer l'effet sur les performances.
- mmap: la structure est chargée immédiatement en mémoire au lancement de l'executable. On pourrait se contenter d'accéder aux pages mémoires nécessaires en jouant sur des offsets.
- supprimer les répétitions: les différentes chaines de caractères stockées dans les noeuds se répètent énormément. On pourrait stocker ces chaines dans un tableau, et garder des offsets dans les noeuds, et ainsi économiser beaucoup de mémoire, contre toutefois un peu plus de temps à la création de la structure. Cela permettrait également de ne plus enregistrer/lire sur disque noeud par noeud, puisque toutes les tailles sont connues facilement.

 7.     Que manque-t-il à votre correcteur orthographique pour qu’il soit à l’état de l’art ?


