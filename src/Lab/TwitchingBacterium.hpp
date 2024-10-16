#pragma once

#include "Bacterium.hpp"
#include "Grip.hpp"

/**
 * @brief The Etat enum Les différents états dans lesquels la bactérie se trouve
 * au cours de son fonctionnement
 * l'état IDLE correspond à un tentacule au repos
 * WAIT_TO_DEPLOY correspond à l'état dans lequel le tentacule se prépare au dépoloiement
 * DEPLOY correspond à l'état dans lequel le tentacule se déploie
 * ATTRACT correspond à l'état dans lequel le tentacule attire la bactérie vers la nourriture
 * RETRACT correspond à l'etat dans lequel le tentacule se rétracte
 * EAT correspond à l'état dans lequel la bactérie consomme de la nourriture
 */
enum Etat {IDLE, WAIT_TO_DEPLOY, DEPLOY, ATTRACT, RETRACT, EAT};

class TwitchingBacterium : public Bacterium
{
public :
    /**
     * @brief TwitchingBacterium Constructeur
     * Incrémente le compteur d'instances de twitching bacterium
     * @param position Coordonnées de la position de l'instance à créer
     */
    TwitchingBacterium(const Vec2d& position);

    /**
     * @brief TwitchingBacterium Constructeur de copie
     * incrémente le compteur d'instances de TwitchingBacterium
     * @param other TwitchingBacterium à copier
     */
    TwitchingBacterium(const TwitchingBacterium& other);

    /**
     * @brief drawOn Dessine la bactérie avec son grapin
     * @param target Cible pour l'affichage
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief moveGrip Déplace le grapin
     * @param delta Vecteur de déplacement du grapin
     */
    void moveGrip(const Vec2d& delta);

    /**
     * @brief eatableQuantity Calcule la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie à tentacule)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentA& nutriment) const override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie à tentacule)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentB& nutriment) const override;

    /**
     * @brief eatableQuantity Calcule l'énergie oté à la bactérie par le poison et consomme le poison
     * (appelle la méthode eatenBy de poison qui prend pour argument une bactérie à tentacule)
     *  @param poison qui est consommé par la bactérie
     * @return L'énergie otée à la bactérie
     */
    Quantity eatableQuantity(Poison& poison) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment de type A pour une bactérie à tentacule
     * (appelle la méthode getScoreCoefficient du nutrimentA qui prend pour argument une bactérie à tentacule)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const NutrimentA& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment de type B pour une bactérie à tentacule
     * (appelle la méthode getScoreCoefficient du nutrimentB qui prend pour argument une bactérie à tentacule)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const NutrimentB& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du poison pour une bactérie à tentacule
     * @param poison qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const Poison& poison) const override;

    /**
     * @brief ~TwitchingBacterium Destructeur
     * Décrémente le compteur d'instances
     */
    virtual ~TwitchingBacterium() override;

    /**
     * @brief getTwitchCounter
     * @return Le nombre d'instance de TwitchingBacterium présente dans l'assiette de Pétri
     */
    static unsigned int getTwitchCounter();

private :
    Grip grip;
    Etat state;
    static unsigned int twitchCounter;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bactéries à tentacule
     * @return la valeur associée à getAppConfig()["twitching bacterium"] du fichier json
     */
    j::Value const& getConfig() const override;

    /**
     * @brief move déplacement de la simple bacterium selon l'etat dans lequel elle se trouve
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     */
    void move(sf::Time dt) override;

    /**
     * @brief clone Effectue la copie d'une instance avec tous ses attributs
     * la bacterie clonée a son tentacule rétracté
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */
    Bacterium* clone() const override;

    /**
     * @brief getStepEnergy
     * @return le facteur de déperdition d'énergie associé au déplacement de la bactérie à tentacule
     */
    Quantity getStepEnergy() const override;

    /**
     * @brief getTentacleEnergy
     * @return le facteur de déperdition d'énergie associé à l'extension du tentacule
     */
    Quantity getTentacleEnergy() const;

    Quantity getFatigueEnergy() const;

    /**
     * @brief tentacleInit rétracte le tentacule et retour de la bactérie à l'état initial
     */
    void tentacleInit();

    /**
     * @brief WaitToDeploy choisi une nouvelle direction en vu du deploiement de la tentacule
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     */
    void waitToDeploy(sf::Time dt);

    /**
     * @brief deploy déploi le tentacule dans la direction choisie
     * Changement d'état de la bactérie si le tentacule rencontre une source de nutriment,
     * si il rencontre un obstacle, le bord de la pétri ou si la tentacule à atteint sa taille maximale
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     * @param nutrimentPtr la source de nutriment que le tentacule pourrait rencontrer
     */
    void deploy(sf::Time dt, const Nutriment* nutrimentPtr);

    /**
     * @brief attract permet au tentacule d'attirer la bacterie vers une source de nutriment
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     * @param nutrimentPtr source de nutriment vers laquelle la bacterie se déplace
     */
    void attract(sf::Time dt, const Nutriment* nutrimentPtr);

    /**
     * @brief retract permet au tentacule de la bactérie de se rétracter
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     */
    void retract(sf::Time dt);

    /**
     * @brief eat gère le changement d'état si la bactérie ne peut plus consommer de nutriment
     * @param nutrimentPtr la source de nutriment que la bactérie est entrain de consommer
     */
    void eat(const Nutriment* nutrimentPtr);

    /**
     * @brief gripToward gère le déplacement du grapin selon sa vitesse ainsi que la consommation
     * d'énergie associée à son mouvement
     * @param direction dans laquelle le grapin se déplace
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     */
    void gripToward (const Vec2d& direction, sf::Time dt);

    /**
     * @brief shiftClone décale la bactérie clonée pour la différencier de la bactérie d'origine
     * @param v vecteur avec lequel la bactérie est décalée
     */
    void shiftClone(const Vec2d& v) override;

};
