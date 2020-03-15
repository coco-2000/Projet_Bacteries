# pragma once
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class PetriDish : public CircularBody
{
public:
    PetriDish(PetriDish const&) = delete;
    bool addBacterium(Bacterium*);
    bool addNutriment(Nutriment*);
    void update(sf::Time dt);
    //drawOn(sf::RenderTarget& targetWindow);

    PetriDish& operator=(PetriDish const&) = delete;

private :
    std::vector<Bacterium*> Bacteries;
    std::vector<Nutriment*> Nutriments;
};

//ne pas oublier le destructeur
