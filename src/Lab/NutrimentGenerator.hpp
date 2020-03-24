#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"

class NutrimentGenerator : public Updatable
{
public:
    NutrimentGenerator();
    void update(sf::Time dt);
    void reset();
private:
    sf::Time compteur;
};
