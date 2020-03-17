#pragma once
#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>

class Lab
{
public:

     Lab();
     void update(sf::Time dt);
     void drawOn(sf::RenderTarget& targetWindow) const;
     void reset();

private :

    PetriDish petri;
    bool contains(const CircularBody&) const;
};
