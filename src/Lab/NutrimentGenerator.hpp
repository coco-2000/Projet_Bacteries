#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"

class NutrimentGenerator : public Updatable
{
public:
    void update(sf::Time dt);
    void reset();
private:
    sf::Time compteur;
};
