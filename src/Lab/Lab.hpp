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

    bool contains(const CircularBody&);
    PetriDish petri;
};
