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
     * @param position Position de la nouvelle instance à créer
     * @param groupe Groupe de Swarm auquel la nouvelle instance appartient
     */
    SwarmBacterium(const Vec2d& position, Swarm* group);

    /**
     * @brief SwarmBacterium Constructeur de copie
     * @param autre Instance à copier
     */
    SwarmBacterium(SwarmBacterium const& autre);

    /**
     * @brief mutate Méthode de mutation (de la couleur)
     */
    void mutate() override;

    /**
     * @brief drawOn Dessine une SwarmBacterium et l'anneau si l'instance est leader du groupe
     * @param target Fenetre dans laquelle le dessin se fait
     */
    void drawOn(sf::RenderTarget &target) const override;

    static double getSwarmCounter();

    /**
    * @brief Destructeur
    * Détruit le pointeur vers le groupe auquel la bactérie appartient (sans détruire le Swarm lui-même)
    */
    ~SwarmBacterium() override;

private:
    Swarm* group;
    static double swarmBcounter;

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

    virtual std::vector<Property>getRecordProperty() const override;
};
