#include "PetriDish.hpp"
#include "../Utility/Utility.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"


PetriDish::PetriDish(Vec2d position, double radius)
    : CircularBody (position, radius)
{
    init_temperature();
}


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
    lesBacteries.clear();

    for (auto& nutriment : lesNutriments)
    {
        delete nutriment;
        nutriment = nullptr;
    }
    lesNutriments.clear();

    init_temperature();
}

PetriDish::~PetriDish()
{
    reset();
}

Temperature PetriDish::getTemperature() const
{
    return temperature;
}


void PetriDish::update(sf::Time dt)
{
    for(auto& nutriment : lesNutriments)
    {
        if(nutriment->ConditionTemperature(temperature))
            {
                nutriment->update(dt);
            }
    }
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

void PetriDish::increaseTemperature()
{
    temperature += getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
}

void PetriDish::decreaseTemperature()
{
    temperature -= getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
}

void PetriDish::init_temperature()
{
    temperature = getAppConfig()["petri dish"]["temperature"]["default"].toDouble();
}




