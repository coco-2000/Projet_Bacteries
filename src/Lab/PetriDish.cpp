#include "PetriDish.hpp"
#include "../Utility/Utility.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"


PetriDish::PetriDish(Vec2d position, double radius)
    : CircularBody (position, radius), temperature(getAppConfig()["petri dish"]["temperature"]["default"].toDouble())
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
    lesBacteries = std::vector<Bacterium*>();

    for (auto& nutriment : lesNutriments)
    {
        delete nutriment;
        nutriment = nullptr;
    }
    lesNutriments = std::vector<Nutriment*>();
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

    bool ConditionCroissance = (getAppConfig()["nutriments"]["growth"]["min temperature"].toDouble() <= temperature) and
            (getAppConfig()["nutriments"]["growth"]["max temperature"].toDouble() >= temperature);

    if (ConditionCroissance)
    {
        for(auto nutriment : lesNutriments)
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
