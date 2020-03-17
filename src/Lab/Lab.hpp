# pragma once
#include "PetriDish.hpp"

class Lab
{
public:

     Lab(const PetriDish& Petri, const Application& application);
     void update(sf::Time dt);
     void drawOn(sf::RenderTarget& targetWindow) const;

private :
    PetriDish* Petri;





    bool contains(const CircularBody&);
};
