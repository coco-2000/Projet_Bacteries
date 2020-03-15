# pragma once
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "CircularBody.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class PetriDish : public CircularBody
{
public:
    PetriDish           (Vec2d position, double radius);
    PetriDish           (PetriDish const&) = delete;

    bool addBacterium   (Bacterium* bacterie);
    bool addNutriment   (Nutriment* nutriment);

    void update         (sf::Time dt);
    void drawOn         (sf::RenderTarget& targetWindow) const;

    PetriDish& operator=(PetriDish const&) = delete;

    void reset();
    ~PetriDish();


private :
    std::vector<Bacterium*> lesBacteries;
    std::vector<Nutriment*> lesNutriments;
};


