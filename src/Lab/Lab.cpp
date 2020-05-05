#include "Lab.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "SimpleBacterium.hpp"

Lab::Lab()
    : petri(getApp().getCentre(), (0.95/2)*getApp().getLabSize().x)
{}

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


template<typename T>
struct property {
    const std::string name;
    std::function<bool(T)> selector;
    std::function<double(int, double)> finisher;
    std::function<double(T, double, std::string)> accumulator;

};

std::unordered_map<std::string, double> Lab::fetchData(const std::string &graphName) const
{

    static const auto mean       = [](int i, double d) -> double{return d/i;};
    //static const auto count      = [](int i, double d) -> double{return i;};
    static const auto sumVal     = [](int i, double d) -> double{return d;};

    static const auto sumB       = [](Bacterium& b, double d, std::string s) -> double{return (b.getParam_mutables().at(s).get() + d);};
    static const auto sumN       = [](Nutriment& n, double d, std::string s) -> double{return (n.getQuantity() + d);};

    static const auto with       = [](std::string s) -> std::function<bool (Bacterium&)>
    { [&](Bacterium& b){ auto m = b.getParam_mutables();
                        return (m.find(s) != m.end());};};
    static const auto all        = [](Nutriment& b) -> bool{return true;};
    //{s::GENERAL, { s::SIMPLE_BACTERIA, s::TWITCHING_BACTERIA, s::SWARM_BACTERIA, s::NUTRIMENT_SOURCES,s::DISH_TEMPERATURE}},
    //{s::NUTRIMENT_QUANTITY, {sumPropertyN(s::NUTRIMENT_QUANTITY)}},
    static const auto meanPropertyB = [](std::string name) ->property<Bacterium&>{return {name, with(name), mean, sumB};};
    static const auto sumPropertyN  = [](std::string name) ->property<Nutriment&>{return {name, all, sumVal, sumN};};

    static const std::unordered_map<std::string, std::vector<property<Bacterium&>>> namesB = {
    {s::SIMPLE_BACTERIA, { meanPropertyB(s::WORSE), meanPropertyB(s::BETTER)}},
    {s::TWITCHING_BACTERIA, { meanPropertyB(s::TENTACLE_LENGTH), meanPropertyB(s::TENTACLE_SPEED)}},
    {s::BACTERIA, {meanPropertyB(s::SPEED)}}};

    static const std::unordered_map<std::string, std::vector<property<Nutriment&>>> nameN = {
    {s::NUTRIMENT_QUANTITY, {sumPropertyN(s::NUTRIMENT_QUANTITY)}}};

    static const std::pair<std::string, std::unordered_map<std::string, std::function<double()>> nameG = {
    //{s::GENERAL, { s::SIMPLE_BACTERIA, s::TWITCHING_BACTERIA, s::SWARM_BACTERIA, s::NUTRIMENT_SOURCES,s::DISH_TEMPERATURE}},
    };


}

Lab::~Lab()
{
    reset();
}

namespace stat {

    namespace accumulator {

    }

    namespace finisher {

    }

    namespace selector {

    }
}

