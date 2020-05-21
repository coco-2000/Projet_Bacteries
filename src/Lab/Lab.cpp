#include "Lab.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "Lab.hpp"

Lab::Lab()
    : petri(getApp().getCentre(), (0.95/2)*getApp().getLabSize().x)
{
    namesGraph = {
        {s::GENERAL,                [&]() { return petri.getPropertyGeneral();}              },
        {s::SIMPLE_BACTERIA,        [&]() { return petri.getPropertySimpleBacteria();}      },
        {s::TWITCHING_BACTERIA,     [&]() { return petri.getPropertyTwitchingBacteria();}   },
        {s::BACTERIA,               [&]() { return petri.getPropertyBacteria();}            },
        {s::NUTRIMENT_QUANTITY,     [&]() { return petri.getPropertyNutrimentQuantity();}    }};
}

bool Lab::contains(const CircularBody& corps) const
{
    return (petri > corps);
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

double Lab::minimumDistToObstacle(const Vec2d &position) const
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

void Lab::addNutriment(Nutriment *nutriment)
{
    petri.addNutriment(nutriment);
}

void Lab::addBacterium(Bacterium* bacterie)
{
    petri.addBacterium(bacterie);
}

void Lab::addObstacle(Obstacle *obstacle)
{
    petri.addObstacle(obstacle);
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

double Lab::getPositionScore(const Vec2d& position) const
{
    return petri.getPositionScore(position);
}

void Lab::increaseGradientExponent()
{
    petri.increaseGradientExponent();
}

void Lab::decreaseGradientExponent()
{
    petri.decreaseGradientExponent();
}

double Lab::getGradientExponent()
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

Lab::~Lab()
{
    reset();
}

void Lab::resetControls()
{
    initTemp();
    initGradient();
}

