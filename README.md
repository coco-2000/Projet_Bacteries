# Projet_Bacteries
Projet SVBA2

auteur : Emma Boehly Constance de Trogoff

Debut du projet : 09/03/2020

=====================================================================
## DESCRIPTION DU PROJET
Le programme permet de visualiser par des techniques de simulation, l'évolution de population de bactéries de différent types.

Dans le cadre de notre projet, nous étudions quatre types de bactéries.
Ces dernières se différencient par leur mode de déplacement, leur couleur, leurs paramètres mutables ou leurs intéractions avec l'environnement.

Les bactéries évoluent dans une assiette de pétri et peuvent rebondir sur les parois ou les obstacles se trouvant sur leur chemin.
Elles se déplacent à la recherche de nutriments. Pour se faire elles emploient différents modes de déplacement.
Par exemple, certaines utilisent des tentacules pour se transporter vers les sources de nourriture et d'autres se
déplacent simplement à l'aide d'un basculement.

Il existe 2 types de nutriments différents. Les nutriments apparaissent de manière aléatoire dans l'asiette de petri, et croissent avec la température.
Ils constituent un apport nutritif différent selon les bacéries, et peuvent même en empoisonner certaines.
Ainsi grâce aux nutriments, les bactéries gagnent de l'énergie et lorque celle-ci est suffisante, elles peuvent se diviser
Les bactéries sont dotées de certains paramètres pouvant muter comme par exemple la vitesse, la couleur ou la longueur d'un tentacule.
Ainsi lors de la division, la bactérie clonée herite des caractéristiques de la bactérie d'origine à l'exception de celles qui auront muté.

Pour survivre malgré la compétition qui sévi entre elles, les bactéries adoptent des stratégies différentes; certaines sont dotées de comportements de groupe et suivent avec confiance un leader,
tandis que d'autres déposent des poisons afin de tuer les concurrents.

Etudier les bactéries au cours des simulations permet de dégager les conditions optimales de survie et de développement.
Ceci est notament permi grâce à des graphes représentant l'évolution de certains paramètres au cours du temps.

##COMPILATION ET EXÉCUTION:

Ce projet utilise  [Cmake](https://cmake.org/) pour compiler

* en ligne de commande :
    - dans le dossier build: cmake ../src
    - make nom_cible pour la génération de la cible

* Dans QTCreator:
       - mise en place du projet : ouvrir le fichier src/CmakeLists.txt
       - choisir la cible à exécuter

##CIBLES PRINCIPALES:

* Finalapplication -> correspond à l'application finale.
* CircularBodyTest -> permet de tester les fonctionnalités liées à la détection de collision
* nutrimentTest -> permet de tester graphiquement la génération automatiques des nutriments dans l'assiette de Petri
* mutableTest -> Vérifie si les méthodes permettant la création de MutableNumber respecte bien les conditions demandées
* simpleBactTest -> permet de tester graphiquement le comportement des bactéries simples
* gripTest -> permet de tester l'affichege des tentacules des twitchingbacterium
* twitchingTest -> permet de tester graphiquement le comportement des bactéries à tentacule
* swarmTest -> permet de tester graphiquement le comportement des bactéries à comportement de groupe
* vec2dTest -> Vérifie si les méthodes de Vec2d réalise bien les bonnes tâches

## FICHIERS DE CONFIGURATION

Le fichier de configuration à utiliser pour application est app.json

Dans le fichier app.json nous avons dû ajouter les paramètres suivants :
- Ajout de la classe Poison parmi les nutriments avec les mêmes paramètres que les autres classes de nutriments
    (ajout de la texture poison dans le dossier res)
- Ajout de la classe PoisonBacterium parmi les bactéries avec les mêmes paramètres qu'une SimpleBacterium
    + le delai entre 2 dépôt de poison
- Pour toutes les classes de bactéries : ajout de paramètres relatifs au mode perdue (lost) tel que la durée du mode perdue,
    le facteur de diminution de la consommation d'énergie (bactéries se mettent en mode réserve), le facteur lambda qui paramètrise
    la probabilité de basculer pour les bactéries perdues
- Ajout de la classe Obstacle avec comme paramètres : le rayon des obstables, le gradient pour le calcul du score et la texture

## COMMANDES

Les commandes pour l'utilisation d'une cible particulières sont données
dans un panneau d'aide à droite de la fenêtre de simulation

### MODIFICATION DE CONCEPTION

Nous avons modifié le calcul du gradient sur l'assiette de Petri en ajoutant un coefficient au score calculé pour chaque nutriment.
Pour cela nous avons reproduit l'implémentation de l'impact différencié des nutriments ce qui fait que selon son type et celui du nutriment
considéré, le comportement de la bactérie sera différent. Ainsi les bactéries auront tendance à être repoussées par les nutriments toxiques pour elles
et attirées par les nutriments nutritifs (hormis les poisons pour lesquelles nous avons fait le choix de ne pas les prendre ne compte dans les calculs)

Afin d'éviter que certaines twitchingbacterium restent immortelles si la vitesse de leur tentacule a muté pour une valeur nulle,
nous avons fait en sorte qu'une twitching bacterium perde constamment un petit peu d'énergie.

### EXTENSIONS

Nous avons développé deux extensions.
Premièrement, nous avons ajouté la possibilité de créer des obstacles circulaires sur lesquels les bactéries rebondissent.
Nous avons donc modifié la cible finalApplication afin de pouvoir créer des obstacles avec la touche O.
Pour faciliter la manipulation de ces obstacles, nous avons également implémenté un moyen de les supprimer à l'aide de la touche E.
Lorsqu'un obstacle est ajouté, les bactéries et les nutriments se trouvant dans son rayon meurent immédiatement
car elles sont écrasées. De plus les nutriments ne peuvent pas croitre au dela d'un obstacle.

Afin de permettre la création de zones autonomes dans l'assiette où des bactéries pourraient vivre en autonomie, nous avons également permis l'ajout
de murs constitués d'une droite d'obstacles. Ceci est observable lors de l'execution avec la touche W.
Un mur est créé entre la position du dernier obstacle ajouté et la position indiquée par le curseur. Pour qu'un mur puisse être créé,
il faut qu'un 1er obstacle le soit.
Afin d'éviter que les bactéries ne soient systématiquement attirées par les nutriments se trouvant de l'autre côté du mur,
nous avons fait en sorte que les bactéries ne désirent pas se rapprocher d'un mur en créant une légère répulsion émanant de ce dernier.
De plus, lorsqu'une bactérie touche un obstacle ou un mur, cette dernière se trouve sonnée par le choc. Par réflexe, elle commence par fuir l'obstacle
puis prend des positions aléatoires le temps de retrouver ses esprits. Nous avons également implémenté le même comportement pour une collision avec le
bord de l'assiette pour plus de cohérence.

Deuxièmement, nous avons introduit un autre type de bactérie : des bactéries à poison. Leurs dessin et mode de déplacement étant similaires à ceux des bactéries simple
nous avons fait crée un superclasse SwimmingBacterium dont hérite les bactéries simples et les bactéries à poison et qui rassemble les méthodes communes aux 2 sous-classes.
Les bactéries à poison déposent de petits nutriments de type poison pouvant etre consommés par les autres bactéries, ce qui diminuent considérablement
leur énergie. La bactérie à poison dispose donc d'une attaque qui lui permet d'interagir indirectement avec les autres bactéries.
Nous avons fais le choix de ne pas comptabiliser les poisons dans le calcul du gradient ce qui fait que les bactéries ne sont ni attirées ni repoussées par celui-ci.
La cible finalApplication a également été modifiée pour permettre l'ajout d'une bactérie à poison si l'on appuie sur la touche P.

De plus, nous avons ajouté/modifié des graphes.
Nous avons tout d'abord rajouté au graphe général le décompte des bactéries à poison.
puis, afin de mieux pouvoir se rendre compte de l'impact des nutriments selon leur type,
nous avons décidé créer un graphe qui compte séparément chacune des instances des sous classes des nutriments.
De plus, il est difficile de s'apercevoir, en regardant simplement la simulation, du nombre de fois qu'une bactérie se divise.
Nous avons donc créé un graphe qui comptabilise le nombre de divisions moyennes d'une bactérie à un instant donné de la simulation.

