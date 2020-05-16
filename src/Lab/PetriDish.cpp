#include "PetriDish.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "../Utility/Utility.hpp"
#include "CircularBody.hpp"
#include <vector>
#include "Application.hpp"

typedef std::unordered_map<std::string, double> GraphData;

PetriDish::PetriDish(Vec2d position, double radius)
    : CircularBody (position, radius)
{
    initTemperature();
    initGradient();
    initAnnex();
}


bool PetriDish::addBacterium(Bacterium* bacterie)
{
    bool contained = contains(*bacterie);
    if (contained)
    {
        lesBacteries.push_back(bacterie);
    }
    else
    {
        delete bacterie;
        bacterie = nullptr;
    }

    return contained;
}


bool PetriDish::addNutriment(Nutriment* nutriment)
{
    bool contained = contains(*nutriment);
    if (contained)
    {
        lesNutriments.push_back(nutriment);
    }
    else
    {
        delete nutriment;
        nutriment = nullptr;
    }

    return contained;
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

    initTemperature();
}

double PetriDish::getTemperature() const
{
    return temperature;
}

void PetriDish::update(sf::Time dt)
{
    updateNutriments(dt);
    updateSwarms(dt);
    updateBacteries(dt);
}


void PetriDish::updateBacteries (sf::Time dt)
{
    append(annex, lesBacteries);
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

void PetriDish::updateNutriments (sf::Time dt)
{
    for(auto& nutriment : lesNutriments)
    {
        if (!(nutriment->isEmpty()))
        {
            if(nutriment->conditionTemperature(temperature))
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

void PetriDish::updateSwarms(sf::Time dt)
{
    for(auto& swarms : lesSwarms)
    {
        swarms->update(dt);
    }
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    //on a ici décidé que l'epaisseur de l'anneau serait 5
    const auto border = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5);
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

void PetriDish::initTemperature()
{
    temperature = getConfig()["temperature"]["default"].toDouble();
}

Nutriment* PetriDish::getNutrimentColliding(CircularBody const& body) const
{
    for (const auto& nutriment : lesNutriments)
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

    for(const auto& nutriment : lesNutriments)
    {
        somme += nutriment->getRadius() / pow(distance(position, nutriment->getPosition()), power);
    }

    return somme;
}

void PetriDish::increaseGradientExponent()
{
    power += getConfig()["gradient"]["exponent"]["delta"].toDouble();
}

void PetriDish::decreaseGradientExponent()
{
    power -= getConfig()["gradient"]["exponent"]["delta"].toDouble();
}

double PetriDish::getGradientExponent() const
{
    return power;
}

void PetriDish::initGradient()
{
    power = (getConfig()["gradient"]["exponent"]["max"].toDouble()
               + getConfig()["gradient"]["exponent"]["min"].toDouble())
              / 2;
}

void PetriDish::initAnnex()
{
    annex.clear();
}

void PetriDish::addAnnex(Bacterium* clone)
{
    annex.push_back(clone);
}

void PetriDish::addSwarm(Swarm* groupe)
{
    lesSwarms.push_back(groupe);
}

Swarm* PetriDish::getSwarmWithId(std::string id) const
{
    for(const auto& swarm : lesSwarms)
    {
        if(swarm->getId() == id)
        {
            return swarm;
        }
    }
    return nullptr;
}

double PetriDish::getMeanBacteria(const std::string &s) const
{
    double value(0.0);
    int sum(0);

    for (const auto& bacterie : lesBacteries) {
        auto p_mutable = bacterie->getParam_mutables();
        if(p_mutable.find(s) != p_mutable.end())
        {
            ++ sum;
            value   += bacterie->getParam_mutables().at(s).get();
        }
    }
    return sum != 0 ? value/sum : -1;
}

double PetriDish::getTotalNutriment() const

{
    double value(0.0);
    for (const auto& nutriment : lesNutriments)
    {
        value += nutriment->getQuantity();
    }

    return value;
}


GraphData PetriDish::getPropertyGeneral() const
{
    return {
        {s::SIMPLE_BACTERIA, SimpleBacterium::getSimpleCounter()},
        {s::TWITCHING_BACTERIA, TwitchingBacterium::getTwitchCounter()},
        {s::SWARM_BACTERIA, SwarmBacterium::getSwarmCounter()},
        {s::NUTRIMENT_SOURCES, lesNutriments.size()},
        {s::DISH_TEMPERATURE, getTemperature()}
        };
}

GraphData PetriDish::getPropertyNutrimentQuantity() const
{
    return {{s::NUTRIMENT_QUANTITY, getTotalNutriment()}};
}

GraphData PetriDish::getPropertySimpleBacteria() const
{
    return {{s::BETTER, getMeanBacteria(s::BETTER)},
            {s::WORSE, getMeanBacteria(s::WORSE)}};
}

GraphData PetriDish::getPropertyTwitchingBacteria() const
{
    return {
        {s::TENTACLE_LENGTH, getMeanBacteria(s::TENTACLE_LENGTH)},
        {s::TENTACLE_SPEED, getMeanBacteria(s::TENTACLE_SPEED)}};
}

GraphData PetriDish::getPropertyBacteria() const
{
    return {{s::SPEED, getMeanBacteria(s::SPEED)}};
}

PetriDish::~PetriDish()
{
    reset();
}
