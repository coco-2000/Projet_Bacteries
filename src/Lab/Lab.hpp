# pragma once
#include "PetriDish.hpp"

class Lab
{
public:
     void update(sf::Time dt);
     void drawOn(sf::RenderTarget& targetWindow) const;
private :
    PetriDish Petri;
};
