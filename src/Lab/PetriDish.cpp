#include "PetriDish.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "PoisonBacterium.hpp"
#include "../Utility/Utility.hpp"
#include "CircularBody.hpp"
#include <vector>
#include "Application.hpp"
#include <algorithm>
#include <cmath>
#include<limits>

typedef std::unordered_map<std::string, double> GraphData;

PetriDish::PetriDish(Vec2d position, double radius)
    : CircularBody (position, radius)
{
    initTemperature();
    initGradient();
    initAnnex();
}

double PetriDish::minimumDistToObstacle(const Vec2d &position) const
{
    if(lesObstacles.empty())
        return std::numeric_limits<double>::max();
    Obstacle* nearestObstacle = (*std::min_element(lesObstacles.begin(), lesObstacles.end(),
                                  [position](Obstacle* o,Obstacle* p)
                                  {
                                       return distance(position, p->getPosition()) > distance(position, o->getPosition());
                                  }
                             ));
    return distance(position, nearestObstacle->getPosition()) - nearestObstacle->getRadius();
}

void PetriDish::deleteObstacle(const Vec2d &position)
{

}


bool PetriDish::addBacterium(Bacterium* bacterie)
{
    bool addable = contains(*bacterie) and !doesCollideWithObstacle(*bacterie);
    if (addable)
    {
        lesBacteries.push_back(bacterie);
    }
    else
    {
        delete bacterie;
        bacterie = nullptr;
    }

    return addable;
}


bool PetriDish::addNutriment(Nutriment* nutriment)
{
    bool addable = contains(*nutriment) and !doesCollideWithObstacle(*nutriment);
    if (addable)
    {
        lesNutriments.push_back(nutriment);
    }
    else
    {
        delete nutriment;
        nutriment = nullptr;
    }

    return addable;
}

bool PetriDish::addObstacle(Obstacle *obstacle)
{
    bool addable = contains(*obstacle);
    if (addable)
    {
        lesObstacles.push_back(obstacle);
        deleteUnderObstacle();
    }
    else
    {
        delete obstacle;
        obstacle = nullptr;
    }

    return addable;
}

void PetriDish::deleteUnderObstacle()
{
    for (auto& bacterie : lesBacteries)
    {
        if(doesCollideWithObstacle(*bacterie))
        {
            delete bacterie;
            bacterie = nullptr;
        }
    }
    lesBacteries.erase(std::remove(lesBacteries.begin(), lesBacteries.end(), nullptr),
                       lesBacteries.end());
    for (auto& nutriment : lesNutriments)
    {
        if(doesCollideWithObstacle(*nutriment))
        {
            delete nutriment;
            nutriment = nullptr;
        }
    }
    lesNutriments.erase(std::remove(lesNutriments.begin(), lesNutriments.end(), nullptr), lesNutriments.end());
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

    for(auto& obstacle : lesObstacles)
    {
        delete obstacle;
        obstacle = nullptr;
    }
    lesObstacles.clear();

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
            bacterie->setScore(getPositionScore(bacterie->getPosition(), *bacterie));
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

    for(const auto& obstacle : lesObstacles)
    {
        obstacle->drawOn(targetWindow);
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


double PetriDish::getPositionScore(const Vec2d& position, const Bacterium& bacterie) const
{
    double somme(0);

    if(!bacterie.isLost())
    {
        for(const auto& nutriment : lesNutriments)
        {
           somme += (nutriment->getRadius() / pow(distance(position, nutriment->getPosition()), power)) *
                    nutriment->getPositionScore(bacterie);;
        }
    }

    for(const auto&  obstacle : lesObstacles)
    {
         somme -= obstacle->getRadius()/ pow(distance(position, obstacle->getPosition()), power*1.7);
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

bool PetriDish::doesCollideWithObstacle(const CircularBody &body) const
{
    for (auto& obstacle : lesObstacles)
    {
        if(obstacle->isColliding(body) or obstacle->contains(body))
        {
            return true;
        }
    }
   return false;
}

double PetriDish::getMeanBacteria(const std::string &s) const
{
    double value(0.0);
    int sum(0);

    for (const auto& bacterie : lesBacteries) {
        auto p_mutable = bacterie->getparamMutables();
        if(p_mutable.find(s) != p_mutable.end())
        {
            ++ sum;
            value   += bacterie->getparamMutables().at(s).get();
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
        {s::POISON_BACTERIA, PoisonBacterium::getPoisonCounter()},
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
