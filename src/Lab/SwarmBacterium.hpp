#pragma once

#include "Bacterium.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/DiffEqSolver.hpp"


class Swarm;

class SwarmBacterium : public Bacterium
{
public:

    /**
     * @brief SwarmBacterium Constructeur
     * Incrémente le compteur d'instances
     * @param position Position de la nouvelle instance à créer
     * @param groupe Groupe de Swarm auquel la nouvelle instance appartient
     */
    SwarmBacterium(const Vec2d& position, Swarm* group);

    /**
     * @brief SwarmBacterium Constructeur de copie
     * Incrémente le compteur d'instances
     * @param autre Instance à copier
     */
    SwarmBacterium(SwarmBacterium const& autre);

    /**
     * @brief mutate Méthode de mutation (de la couleur)
     */
    //void mutate() override;

    /**
     * @brief drawOn Dessine une SwarmBacterium et l'anneau si l'instance est leader du groupe
     * @param target Fenetre dans laquelle le dessin se fait
     */
    void drawOn(sf::RenderTarget &target) const override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie à comportement de groupe)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentA& nutriment) override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie à comportement de groupe)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    Quantity eatableQuantity(Poison& poison) override;

    double getScoreCoefficient(const NutrimentA& nutriment) const override;

    double getScoreCoefficient(const NutrimentB& nutriment) const override;

    double getScoreCoefficient(const Poison& poison) const override;

    /**
    * @brief Destructeur
    * Détruit le pointeur vers le groupe auquel la bactérie appartient (sans détruire le Swarm lui-même)
    * Décrémente le compteur d'instances
    */
    ~SwarmBacterium() override;

    /**
     * @brief getSwarmCounter compte le nombre total d'instances de SwarmBacterium présentes dans
     * l'assiette de Pétri
     * @return le nombre total d'instances
     */
    static unsigned int getSwarmCounter();

private:
    Swarm* group;
    static unsigned int swarmCounter;

    /**
     * @brief move Déplace une bactérie
     * @param dt Pas de temps depuis le dernier déplacement de l'instance courante
     */
    void move(sf::Time dt) override;

    /**
     * @brief clone Effectue la copie d'une instance avec tous ses attributs
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */
    SwarmBacterium* clone() const override;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries swarms
     * @return La valeur associée à getAppConfig()["swarm bacterium"]
     */
    j::Value const& getConfig() const override;

    /**
     * @brief getSpeedVector Calcul le vecteur de vitesse de l'instance courante
     * @return La vitesse courante de l'instance
     */
    Vec2d getSpeedVector() const;

    /**
     * @brief moveLeader Déplace la bactérie leader du groupe
     */
    void moveLeader();

};
