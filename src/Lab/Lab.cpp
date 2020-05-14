#include "Lab.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "Lab.hpp"

typedef std::function<std::unordered_map<std::string, double>()> Result;

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

Nutriment* Lab::getNutrimentColliding(CircularBody const& body) const
{
    return petri.getNutrimentColliding(body);
}

void Lab::update(sf::Time dt)
{
    petri.update(dt);
    generateur_nutriment.update(dt);
}

void Lab::drawOn(sf::RenderTarget& targetWindow) const
{
    petri.drawOn(targetWindow);
}

void Lab::reset()
{
    petri.reset();
    generateur_nutriment.reset();
}

void Lab::addNutriment(Nutriment *nutriment)
{
    petri.addNutriment(nutriment);
}

void Lab::addBacterium(Bacterium* bacterie)
{
    petri.addBacterium(bacterie);
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
    petri.init_temperature();
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
    return namesGraph.at(graphName)();
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

