#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Utility/MutableColor.hpp"
#include <SFML/Graphics.hpp>
#include "Utility/Types.hpp"
#include <string>

class Bacterium : public CircularBody, public Drawable, public Updatable
{
public :

    /**
     * @brief Bacterium Constructeur
     * @param energie niveau d'énergie intiale de la bacterie
     * @param position Coordonnées de la position intiale de la bacterie
     * @param direction Direction du déplacement initiale de la bacterie
     * @param radius Rayon initiale de la bactérie
     * @param couleur couleur initiale de la bacterie
     * @param param_mutables ensemble de paramètres numériques mutables
     * @param abstinence si la bacterie consomme des nutriments ou non
     */
    Bacterium(Quantity energie, Vec2d position, Vec2d direction,
              double radius, const MutableColor& couleur,
              std::map<std::string, MutableNumber>param_mutables = {},
              bool abstinence = 0);

    /**
     * @brief en_vie savoir si la bacterie a suffisamment d'energie pour etre en vie
     * @return vrai si l'energie est suffisante
     */
    bool en_vie();

    /**
     * @brief drawOn dessiner la bacterie
     * @param target la fenetre dans laquelle on affiche la bacterie
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief update gère le déplacement des bacteries,
     * les collisions avec le bord de l'assiette de petri
     * la consommation des nutriments par les bacteries
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief setDirection Manipulateur de direction
     * @param direction Vecteur à assigner à la direction de l'instance courante
     */
    void setDirection(Vec2d direction);

    /**
     * @brief addProperty Ajoute à l'ensemble des paramètres mutables numériques de la bactérie une valeur numérique mutable donnée
     * @param key Clé (=nom) du paramètre mutable à ajouter
     * @param valeur Valeur associée à la clé, sous forme de MutableNumber
     */
    void addProperty(const std::string& key, const MutableNumber& valeur);

    /**
     * @brief getProperty Accesseur d'un paramètre mutable
     * @param key Clé (=nom) du paramètre mutable à renvoyer
     * @return La valeur, sous forme de MutableNumber, du paramètre associé à la clé
     */
    MutableNumber getProperty(const std::string& key) const;

    /**
     * @brief setScore Manipulateur du score
     * @param score Score à assigner à l'attribut ancien_score
     *              (score avant mise à jour) de l'instance courante
     */
    void setScore(double score);


protected :
    MutableColor couleur;
    double angle;
    Vec2d direction;
    Quantity energie;
    std::map<std::string, MutableNumber> param_mutables;
    bool abstinence;

    sf::Time compteur;
    double ancien_score;


    /**
     * @brief DisplayEnergy Affiche la quantité d'énergie de la bacterie (si mode debugging activé)
     * @param target Cible pour l'affichage
     */
    void DisplayEnergy(sf::RenderTarget& target) const;

    /**
     * @brief collisionPetri gère les collisions des bacteries
     * avec l'assiette de petri
     */
    void collisionPetri(sf::Time dt);


    /**
     * @brief move Méthode virtuelle pure de déplacement des bactéries
     *        (à redéfinir dans les sous-classes)
     * @param dt Pas de temps depuis le dernier déplacement de l'instance courante
     */
    virtual void move(sf::Time dt) = 0;

    /**
     * @brief clone réalise une copie polymorphique de la bacterie. Méthode virtuelle pure
     * @return Un pointeur sur la nouvelle bactérie issue de l'instance courante
     */
    virtual Bacterium* clone() const = 0;

    /**
     * @brief divide Méthode de division commune à toutes les bactéries
     * Si les conditions de division sont remplies, créé une nouvelle bactérie clonée,
     * divise par 2 l'énergie de la bactérie d'origine et de celle clonée,
     * inverse la direction de déplacement de la bactérie d'origine et effectue des mutations
     * sur la bacterie clonée
     */
    void divide();

    /**
     * @brief tentative_basculement Décide si la bactérie doit basculer ou non
     * ici le corps de la méthode est vide pour que les tests puissent s'effectuer correctement
     */
    virtual void tentative_basculement() {}

    /**
     * @brief mutate Méthode de mutation d'une bactérie
     */
    void mutate();

    /**
     * @brief copie Méthode virtuelle pure effectuant la copie d'une instance avec
     *              tous ses attributs
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */

    /**
     * @brief getEnergyReleased
     * @return l'énergie dépensée à chaque pas de déplacement
     */
    Quantity getEnergyReleased() const;

    /**
     * @brief getEnergy
     * @return l'énergie minimale nécessaire à la division
     */
    Quantity getEnergy() const;

    /**
     * @brief getDelay
     * @return le temps d'attente entre deux consommations de nutriments pour la bactérie
     */
    sf::Time getDelay() const;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries
     * Il s'agit d'une méthode virtuelle pure
     * @return la valeur associée à getAppConfig()["bacterium"]
     */
    virtual j::Value const& getConfig() const = 0;

    /**
     * @brief consumeEnergy décrémenter le niveau d'énergie
     * @param qt la quantité pour laquelle l'énergie est décrémentée
     */
    void consumeEnergy(Quantity qt);

    /**
     * @brief consumeNutriment gère la consommation des bacteries
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void consumeNutriment(sf::Time dt);


};
