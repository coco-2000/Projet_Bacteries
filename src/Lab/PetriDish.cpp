#include "PetriDish.hpp"
#include "CircularBody.hpp"

PetriDish::PetriDish(Vec2d position, double radius)
    : CircularBody (position, radius)
{}

bool PetriDish::addBacterium(Bacterium* bacterie)
{
    lesBacteries.push_back(bacterie);
}

bool PetriDish::addNutriment(Nutriment* nutriment)
{
    lesNutriments.push_back(nutriment);
}

void PetriDish::reset()
{
    for (auto& bacterie : lesBacteries)
    {
        delete bacterie;
        bacterie = nullptr;
    }
    for (auto& nutriment : lesNutriments)
    {
        delete nutriment;
        nutriment = nullptr;
    }
}

PetriDish::~PetriDish()
{
    reset();
}

void PetriDish::update(sf::Time dt)
{
    //faire evoluer les bacteries
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    //dessiner
}

