#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"

class NutrimentGenerator : public Updatable
{
public:

    /**
     * @brief NutrimentGenerator Constructeur : initialise le compteur à 0
     */
    NutrimentGenerator();

    /**
     * @brief update Met à jour le compteur à chaque écoulement de pas de temps et permet la création alétoire de sources de nutriment
     * @param dt Pas de temps après lequel la bactérie est mise à jour
     */
    void update(sf::Time dt);

    /**
     * @brief reset initialise le compteur à 0
     */
    void reset();


private:
    sf::Time compteur;
};
