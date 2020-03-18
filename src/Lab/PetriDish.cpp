#include "PetriDish.hpp"
#include "../Utility/Utility.hpp"
#include "CircularBody.hpp"
#include "Config.hpp"


PetriDish::PetriDish(Vec2d position, double radius)
    : CircularBody (position, radius)
{}


bool PetriDish::addBacterium(Bacterium* bacterie)
{
    bool conditions = true;

    if (conditions)
        lesBacteries.push_back(bacterie);

    return conditions;
}


bool PetriDish::addNutriment(Nutriment* nutriment)
{
    if (contains(*nutriment))
    {
        lesNutriments.push_back(nutriment);
    }

    return contains(*nutriment);
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
    auto border = buildAnnulus(position, radius, sf::Color::Black, epaisseur_anneau);
    targetWindow.draw(border);

    for(auto nutriment : lesNutriments)
    {
        nutriment->drawOn(targetWindow);
    }
}

