#pragma once

#include "Bacterium.hpp"
#include "Grip.hpp"
//#include "Nutriment.hpp"

enum Etat {IDLE, WAIT_TO_DEPLOY, DEPLOY, ATTRACT, RETRACT, EAT};

class TwitchingBacterium : public Bacterium
{
public :
    /**
     * @brief TwitchingBacterium Constructeur
     * Incrémente le compteur d'instances
     * @param position Coordonnées de la position de l'instance à créer
     */
    TwitchingBacterium(const Vec2d& position);

    /**
     * @brief TwitchingBacterium Constructeur de copie
     * Incrémente le compteur d'instances
     * @param other TwitchingBacterium à copier
     */
    TwitchingBacterium(const TwitchingBacterium& other);

    /**
     * @brief drawOn dessiner la bactérie avec son grapin
     * @param target Cible pour l'affichage
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief moveGrip déplacement du grapin
     * @param delta vecteur avec lequel le grapin est déplacé
     */
    void moveGrip(const Vec2d& delta);

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie à tentacule)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentA& nutriment) override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie à tentacule)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    /**
     * @brief ~TwitchingBacterium Destructeur
     * Décrémente le compteur d'instances
     */
    virtual ~TwitchingBacterium() override;

    /**
     * @brief getTwitchCounter compte le nombre total de Twitching Bacterium présentes dans l'assiette
     * de Pétri
     * @return le nombre total d'instances
     */
    static double getTwitchCounter();



protected :
    Grip grip;
    Etat state;
    static double twitchCounter;

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

    /**
     * @brief tentacle_init rétracte le tentacule et retour de la bactérie à l'état initial
     */
    void tentacleInit();

    /**
     * @brief Wait_to_deploy_state etat dans lequel le tentacule de la bactérie se prépare au déploiement.
     * Choix de la direction
     */
    void waitToDeployState();

    /**
     * @brief deploy_state etat dans lequel le tentacule se déploie.
     * Changement d'état de la bactérie si le tentacule rencontre une source de nutriment
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     * @param nutriment_ptr la source de nutriment que le tentacule pourrait rencontrer
     */
    void deployState(sf::Time dt, const Nutriment* nutriment_ptr);

    /**
     * @brief attract_state Etat dans lequel le tentacule attire la bacterie vers la nourriture
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     * @param nutriment_ptr source de nutriment vers laquelle la bacterie se déplace
     */
    void attractState(sf::Time dt, const Nutriment* nutriment_ptr);

    /**
     * @brief retract_state État dans lequel la bactérie rétracte le tentacule
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     */
    void retractState(sf::Time dt);

    /**
     * @brief eat_state état durant lequel la bactérie est entrain de consommer des nutriments
     * Gère le changement d'état si la bactérie ne peut plus consommer de nutriment
     * @param nutriment_ptr la source de nutriment que la bactérie est entrain de consommer
     */
    void eatState(const Nutriment* nutriment_ptr);

    /**
     * @brief grapinToward gère le déplacement du grapin selon sa vitesse ainsi que la consommation
     * d'énergie associée à son mouvement
     * @param dir direction dans laquelle le grapin se déplace
     * @param dt Pas de temps apres lequel la simulation est mise à jour
     */
    void gripToward (const Vec2d& dir, sf::Time dt);

    /**
     * @brief shift_clone décale la bactérie clonée pour la différencier de la bactérie d'origine
     * @param v vecteur avec lequel la bactérie est décalée
     */
    void shiftClone(const Vec2d& v) override;

};
