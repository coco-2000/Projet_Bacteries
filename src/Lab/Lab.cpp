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


std::unordered_map<std::string, double> Lab::fetchData(const std::string &graphName) const
{

    static const auto mean       = [](int i, double d) -> double{return d/i;};
    static const auto sumVal     = [](int i, double d) -> double{return d;};

    static const auto sumB       = [](const Bacterium& b, double d, const std::string& s) -> double{return (b.getParam_mutables().at(s).get() + d);};
    static const auto sumN       = [](const Nutriment& n, double d, const std::string& s) -> double{return (n.getQuantity() + d);};

    static const auto with       = [](const std::string& s) -> std::function<bool (const Bacterium&)>
    { return [&](const Bacterium& b){ auto m = b.getParam_mutables();
                        return (m.find(s) != m.end());};};

    static const auto all        = [](const Nutriment& b) -> bool{return true;};

    static const auto meanPropertyB = [](const std::string& name) ->property<Bacterium&>{return {name, with(name), mean, sumB};};
    static const auto sumPropertyN  = [](const std::string& name) ->property<Nutriment&>{return {name, all, sumVal, sumN};};

    static const std::unordered_map<std::string, std::vector<property<Bacterium&>>> namesB = {
    {s::SIMPLE_BACTERIA, { meanPropertyB(s::WORSE), meanPropertyB(s::BETTER)}},
    {s::TWITCHING_BACTERIA, { meanPropertyB(s::TENTACLE_LENGTH), meanPropertyB(s::TENTACLE_SPEED)}},
    {s::BACTERIA, {meanPropertyB(s::SPEED)}}};

    static const std::unordered_map<std::string, std::vector<property<Nutriment&>>> namesN = {
    {s::NUTRIMENT_QUANTITY, {sumPropertyN(s::NUTRIMENT_QUANTITY)}}};

    static const std::map<std::string, std::vector<counting_property>> nameG = {
        {s::GENERAL, { {s::SIMPLE_BACTERIA,     SimpleBacterium::getSimpleCounter},
                       {s::TWITCHING_BACTERIA,  TwitchingBacterium::getTwitchCounter},
                       {s::SWARM_BACTERIA,      SwarmBacterium::getSwarmCounter},
                       {s::NUTRIMENT_SOURCES,   Nutriment::getNutCounter},
                       {s::DISH_TEMPERATURE,    [&]()-> double{return getTemperature();}} }
        }};

    std::unordered_map<std::string, double> result;

    if (graphName == s::GENERAL)
    {
        for (const auto& serie : nameG.at(graphName))
        {
            result[serie.name] = serie.counter();
        }
    }
    else if (graphName.find("bacteria") != std::string::npos)
    {
        for(const auto& serie : namesB.at(graphName))
        {
           result[serie.name] = getProperty(serie, petri.getLesBacteries());
        }
    }

    else if (graphName.find("nutriment") != std::string::npos)
    {
        for(const auto& serie : namesN.at(graphName) )
        {
            result[serie.name] = getProperty(serie,petri.getLesNutriments());
        }
    }

    return result;
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

