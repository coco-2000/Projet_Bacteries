#include "Lab.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"
#include "../Utility/Vec2d.hpp"

Lab::Lab()
    : petri(getApp().getCentre(), (0.95/2)*getApp().getLabSize().x)
{
    namesGraph = {
        {s::GENERAL,                [&]() { return petri.getPropertyGeneral();}             },
        {s::SIMPLE_BACTERIA,        [&]() { return petri.getPropertySimpleBacteria();}      },
        {s::TWITCHING_BACTERIA,     [&]() { return petri.getPropertyTwitchingBacteria();}   },
        {s::BACTERIA,               [&]() { return petri.getPropertyBacteria();}            },
        {s::BACTERIA_DIVISION,      [&]() { return petri.getPropertyBacteriaDivision();}    },
        {s::NUTRIMENT_QUANTITY,     [&]() { return petri.getPropertyNutrimentQuantity();}   },
        {s::NUTRIMENT,              [&]() { return petri.getPropertyNutriment();}           },
    };
}

bool Lab::contains(const CircularBody& body) const
{
    return (petri > body);
}

bool Lab::doesCollideWithDish(CircularBody const& body) const
{
    /*
     * Comme l'assiete de petri constitue la limite de l'espace dans lequel se deplacent les
     * CircularBody, le fait de ne plus etre contenu dans une PetriDish équivaut à en sortir
     */
    return !contains(body);
}

bool Lab::doesCollideWithObstacle(CircularBody const& body) const
{
    return  petri.doesCollideWithObstacle(body);
}

double Lab::minimumDistToObstacle(const Vec2d& position) const
{
    return petri.minimumDistToObstacle(position);
}

Nutriment* Lab::getNutrimentColliding(CircularBody const& body) const
{
    return petri.getNutrimentColliding(body);
}

void Lab::update(sf::Time dt)
{
    petri.update(dt);
    nutrimentGenerator.update(dt);
}

void Lab::drawOn(sf::RenderTarget& targetWindow) const
{
    petri.drawOn(targetWindow);
}

void Lab::reset()
{
    petri.reset();
    nutrimentGenerator.reset();
}

bool Lab::addNutriment(Nutriment* nutriment)
{
    return petri.addNutriment(nutriment);
}

bool Lab::addBacterium(Bacterium* bacterie)
{
    return petri.addBacterium(bacterie);
}

bool Lab::addObstacle(Obstacle* obstacle)
{
    return petri.addObstacle(obstacle);
}

void Lab::increaseTemperature()
{
    petri.increaseTemperature();
}

void Lab::decreaseTemperature()
{
    petri.decreaseTemperature();
}

double Lab::getTemperature() const
{
    return petri.getTemperature();
}

void Lab::initTemp()
{
    petri.initTemperature();
}

double Lab::getPositionScore(const Vec2d& position, const Bacterium& bacterie) const
{
    return petri.getPositionScore(position, bacterie);
}

void Lab::increaseGradientExponent()
{
    petri.increaseGradientExponent();
}

void Lab::decreaseGradientExponent()
{
    petri.decreaseGradientExponent();
}

double Lab::getGradientExponent() const
{
    return petri.getGradientExponent();
}

void Lab::initGradient()
{
    return petri.initGradient();
}

void Lab::addAnnex(Bacterium* clone)
{
    petri.addAnnex(clone);
}

void Lab::addSwarm(Swarm* groupe)
{
    petri.addSwarm(groupe);
}

Swarm* Lab::getSwarmWithId(const std::string& id) const
{
    return petri.getSwarmWithId(id);
}

std::unordered_map<std::string, double> Lab::fetchData(const std::string &graphName) const
{
    return namesGraph.at(graphName)(); //at jettera une exception si graphName n'est pas dans la map
}

void Lab::deleteObstacle(const Vec2d& position)
{
    petri.deleteObstacle(position);
}

void Lab::createWall(const Vec2d& position1, const Vec2d& position2)
{
   petri.createWall(position1, position2);
}

Vec2d Lab::getLastObstaclePos() const
{
    return petri.getLastObstaclePos();
}

double Lab::getDistToPetri(const Vec2d& position) const
{
    return (petri.getRadius() - distance(petri.getPosition(), position));
}

Vec2d Lab::getMiddleDirectionVector(const Vec2d& position) const
{
    return (petri.getPosition() - position).normalised();
}

Lab::~Lab()
{
    reset();
}

void Lab::resetControls()
{
    initTemp();
    initGradient();
}



