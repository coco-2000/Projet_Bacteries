#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"

class NutrimentGenerator : public Updatable
{
public:

    /**
     * @brief NutrimentGenerator constructeur initialise le compteur à 0
     */
    NutrimentGenerator();

    /**
     * @brief update faitévoluer le compteur à chaque écoulement de pas de temps,
     * permet la créatio alétoire de sources de nutriment
     * @param dt : pas de temps
     */
    void update(sf::Time dt);

    /**
     * @brief reset initialise le compteur à 0
     */
    void reset();


private:
    sf::Time compteur;
};
