# Projet_Bacteries
Projet SVBA2

auteur : Emma Boehly Constance de Trogoff

Debut du projet : 09/03/2020

.at pour les maps jette une exception si la clé n'existe pas contraire à []
- faut il controler la valeur dans Stats::setActive ?
- opérateur d'affectation supprimé dans bactérium ok ?
- SwarmBacterium mutate
- ou mettre les typedefs
- Pensez à utiliser des variables temporaires pour stocker les résultats de long calculs.
- Pensez à utiliser des méthodes vous donnant les informations (constantes) provenant des fichiers JSON.
- Améliorez les commentaires de `Lab/TwitchingBacterium.hpp` pour les méthodes gérant la transition d'états.

Rendu de : Groupe 1

# FEEDBACK suite au rendu intermediaire du 22.04.2020


## Avancement du projet

Dernière étape abordée: **Etape 4**
État des parties précédentes (selon le journal):
- Un bug dans `NutrimentTest` reste présent. à revoir avec lui

## Commentaires et mise en page

- Améliorez les commentaires de `Lab/TwitchingBacterium.hpp` pour les méthodes gérant la transition d'états.
- Utilisez *soit* le `snake_case` (e.g. `ma_fonction`) *soit* le `camelCase` (`maFonction`) pour les fonctions/méthodes
et noms de paramètres et attributs, et réservez le `PascalCase` (e.g. `MaClasse`) pour les noms de classe.

- revoir les const

## Review du code

### Tests
- `mutableTest`: l'ordre des arguments dans le constructeur de `MutableNumber` est incorrect.

### Conception et encapsulation
- Pensez à ne **pas** mettre les attributs d'une superclasse en *protected* s'ils ne sont *pas* nécessaires à une
sous-classe (e.g. `CircularBody::position` ou `Bacterium::angle`). Si vous avez besoin accéder à ou modifier des
attributs privés, donnez uniquement accès à un getter/setter (public ou protégé, cela dépendra).
ok

### Autres

- Pensez à utiliser des variables temporaires pour stocker les résultats de long calculs.
- Pensez à utiliser des méthodes vous donnant les informations (constantes) provenant des fichiers JSON.
- Lorsque le type de retour d'un getter ou le type d'un argument de fonction ou méthode n'est pas un type primitif,
e.g. autre qu'un `int`, un `double`, un `float`, un `bool` ou un `char`, utilisez des références constantes pour éviter
une copie inutile (mais uniquement si cela est pertinent et adéquat, e.g. `Swarm::getId()`).

- Pensez à utiliser une boucle `for(const auto &...)` lorsqu'il est possible (et non pas simplement `for(auto ...)`).
N'utilisez les références non-constantes que lorsque vous le devez. ok

- Dans `PetriDish::update()`, vous devriez utiliser le vecteur `annex` *avant* d'updater vos bactéries afin d'éviter un
décalage dans les updates. ok

- Faites attention aux cas de division par zéro (e.g. `SimpleBacterium::tentative_basculement()`). ok

## Conseils pour les semaines restantes

Dans l'ensemble, le projet est correct. Il faudra cependant faire attention à l'encapsulation et à l'utilisation de
mot-clé `const`, que cela soit pour les méthodes ou pour les types.
