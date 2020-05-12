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
    init_temperature();
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

    return contained;
}


bool PetriDish::addNutriment(Nutriment* nutriment)
{
    bool contained = contains(*nutriment);
    if (contained)
    {
        lesNutriments.push_back(nutriment);
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
    if(!annexe.empty())
    {
        append(annexe, lesBacteries);
        initAnnex();
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

double PetriDish::getMeanBacterium(const std::string &s) const
{
    double value(0.0);
    int sum(0);

    for (const auto& bacterie : lesBacteries) {
        auto p_mutable = bacterie->getParam_mutables();
        if(p_mutable.find(s) != p_mutable.end())
        {
            sum     += 1;
            value   += bacterie->getParam_mutables().at(s).get();
        }
    }
    return sum != 0 ? value/sum : -1; //vérifier si la syntaxe est juste
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
        {s::DISH_TEMPERATURE, temperature}
        };
}

GraphData PetriDish::getPropertyNutrimentQuantity() const
{
    return {{s::NUTRIMENT_QUANTITY, getTotalNutriment()}};
}

GraphData PetriDish::getPropertySimpleBacterium() const
{
    return {{s::BETTER, getMeanBacterium(s::BETTER)},
            {s::WORSE, getMeanBacterium(s::WORSE)}};
}

GraphData PetriDish::getPropertyTwitchingBacterium() const
{
    return {
        {s::TENTACLE_LENGTH, getMeanBacterium(s::TENTACLE_LENGTH)},
        {s::TENTACLE_SPEED, getMeanBacterium(s::TENTACLE_SPEED)}};
}

GraphData PetriDish::getPropertyBacterium() const
{
    return {{s::SPEED, getMeanBacterium(s::SPEED)}};
}

PetriDish::~PetriDish()
{
    reset();
}
