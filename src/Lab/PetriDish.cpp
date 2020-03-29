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
    if (contains(*bacterie))
    {
        lesBacteries.push_back(bacterie);
    }

    return contains(*bacterie);
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

Temperature PetriDish::getTemperature() const
{
    return temperature;
}


void PetriDish::update(sf::Time dt)
{
    update_nutriments(dt);
    update_bacteries(dt);
}

void PetriDish::update_bacteries (sf::Time dt)
{
    for(auto& bacterie : lesBacteries)
    {
        if(bacterie->en_vie())
        {
            bacterie->update(dt);
        }
        else
        {
            delete bacterie;
            bacterie = nullptr;
        }
    }
    lesBacteries.erase(std::remove(lesBacteries.begin(), lesBacteries.end(), nullptr), lesBacteries.end());
}

void PetriDish::update_nutriments (sf::Time dt)
{
    for(auto& nutriment : lesNutriments)
    {
        if (!nutriment->isEmpty())
        {
            if(nutriment->ConditionTemperature(temperature))
            {
                nutriment->update(dt);
            }
        }
        else
        {
            delete nutriment;
            nutriment = nullptr;
        }
    }
    lesNutriments.erase(std::remove(lesNutriments.begin(), lesNutriments.end(), nullptr), lesNutriments.end());
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    //on a ici décidé que l'epaisseur de l'anneau serait 5
    auto border = buildAnnulus(position, radius, sf::Color::Black, 5);
    targetWindow.draw(border);

    for(auto nutriment : lesNutriments)
    {
        nutriment->drawOn(targetWindow);
    }

    for(auto bacterie : lesBacteries)
    {
        bacterie->drawOn(targetWindow);
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

Nutriment* PetriDish::getNutrimentColliding(CircularBody const& body) const
{
    for (auto nutriment : lesNutriments)
    {
        if (*nutriment & body)
        {
            return nutriment;
        }
    }

    return nullptr;
}

PetriDish::~PetriDish()
{
    reset();
}


