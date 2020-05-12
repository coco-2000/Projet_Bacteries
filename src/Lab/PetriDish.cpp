#include "PetriDish.hpp"
#include "../Utility/Utility.hpp"
#include "CircularBody.hpp"
#include <vector>
#include "Application.hpp"


PetriDish::PetriDish(Vec2d position, double radius)
    : CircularBody (position, radius)
{
    init_temperature();
    initGradient();
    initAnnex();
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

    for(auto& swarm : lesSwarms)
    {
        delete swarm;
        swarm = nullptr;
    }
    lesSwarms.clear();

    init_temperature();
}

double PetriDish::getTemperature() const
{
    return temperature;
}

void PetriDish::update(sf::Time dt)
{
    update_nutriments(dt);
    update_bacteries(dt);
    update_swarms(dt);
}


void PetriDish::update_bacteries (sf::Time dt)
{
    append(annexe, lesBacteries);
    initAnnex();

    for(auto& bacterie : lesBacteries)
    {
        if(bacterie->alive())
        {
            bacterie->setScore(getPositionScore(bacterie->getPosition()));
            bacterie->update(dt);
        }
        else
        {
            delete bacterie;
            bacterie = nullptr;
        }
    }

    lesBacteries.erase(std::remove(lesBacteries.begin(), lesBacteries.end(), nullptr),
                       lesBacteries.end());

}

void PetriDish::update_nutriments (sf::Time dt)
{
    for(auto& nutriment : lesNutriments)
    {
        if (!(nutriment->isEmpty()))
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

void PetriDish::update_swarms(sf::Time dt)
{
    for(auto& swarms : lesSwarms)
    {
        swarms->update(dt);
    }
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    //on a ici décidé que l'epaisseur de l'anneau serait 5
    const auto border = buildAnnulus(position, radius, sf::Color::Black, 5);
    targetWindow.draw(border);

    for(const auto& nutriment : lesNutriments)
    {
        nutriment->drawOn(targetWindow);
    }

    for(const auto& bacterie : lesBacteries)
    {
        bacterie->drawOn(targetWindow);
    }
}

j::Value const& PetriDish::getConfig() const
{
    return getAppConfig()["petri dish"];
}

void PetriDish::increaseTemperature()
{
    temperature += getConfig()["temperature"]["delta"].toDouble();
}

void PetriDish::decreaseTemperature()
{
    temperature -= getConfig()["temperature"]["delta"].toDouble();
}

void PetriDish::init_temperature()
{
    temperature = getConfig()["temperature"]["default"].toDouble();
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

double PetriDish::getPositionScore(const Vec2d& position) const
{
    double somme(0);

    for(auto& nutriment : lesNutriments)
    {
        somme += nutriment->getRadius() / pow(distance(position, nutriment->getPosition()), puissance);
    }

    return somme;
}

void PetriDish::increaseGradientExponent()
{
    puissance += getConfig()["gradient"]["exponent"]["delta"].toDouble();
}

void PetriDish::decreaseGradientExponent()
{
    puissance -= getConfig()["gradient"]["exponent"]["delta"].toDouble();
}

double PetriDish::getGradientExponent() const
{
    return puissance;
}

void PetriDish::initGradient()
{
    puissance = (getConfig()["gradient"]["exponent"]["max"].toDouble()
               + getConfig()["gradient"]["exponent"]["min"].toDouble())
              / 2;
}

void PetriDish::initAnnex()
{
    annexe.clear();
}

void PetriDish::addAnnex(Bacterium* clone)
{
    annexe.push_back(clone);
}

void PetriDish::addSwarm(Swarm* groupe)
{
    lesSwarms.push_back(groupe);
}

Swarm* PetriDish::getSwarmWithId(std::string id) const
{
    for(auto& swarm : lesSwarms)
    {
        if(swarm->getId() == id)
        {
            return swarm;
        }
    }
    return nullptr;
}

PetriDish::~PetriDish()
{
    reset();
}

std::vector<Bacterium *> PetriDish::getLesBacteries() const
{
    return lesBacteries;
}

std::vector<Nutriment *> PetriDish::getLesNutriments() const
{
    return lesNutriments;
}

