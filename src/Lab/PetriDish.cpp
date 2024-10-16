#include "PetriDish.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "PoisonBacterium.hpp"
#include "Poison.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "../Utility/Utility.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"

typedef std::unordered_map<std::string, double> GraphData;

PetriDish::PetriDish(const Vec2d &position, double radius)
    : CircularBody (position, radius)
{
    initTemperature();
    initGradient();
    initAnnex();
}

double PetriDish::minimumDistToObstacle(const Vec2d& position) const
{
    if(obstacles.empty())
        return std::numeric_limits<double>::max();

    Obstacle* nearestObstacle = (*std::min_element(obstacles.begin(), obstacles.end(),
    [position](Obstacle* o, Obstacle* p) {
        return distance(position, p->getPosition()) > distance(position, o->getPosition());
    }));
    return distance(position, nearestObstacle->getPosition()) - nearestObstacle->getRadius();
}

void PetriDish::deleteObstacle(const Vec2d &position)
{
    for (auto& obstacle : obstacles) {
        if(distance(position, obstacle->getPosition())< obstacle->getRadius()) {
            delete obstacle;
            obstacle = nullptr;
        }
    }
    obstacles.erase(std::remove(obstacles.begin(), obstacles.end(), nullptr), obstacles.end());
}


bool PetriDish::addBacterium(Bacterium* bacterie)
{
    bool addable = contains(*bacterie) and !doesCollideWithObstacle(*bacterie);
    if (addable) {
        bacteries.push_back(bacterie);
    } else {
        delete bacterie;
        bacterie = nullptr;
    }

    return addable;
}


bool PetriDish::addNutriment(Nutriment* nutriment)
{
    bool addable = contains(*nutriment) and !doesCollideWithObstacle(*nutriment);
    if (addable) {
        nutriments.push_back(nutriment);
    } else {
        delete nutriment;
        nutriment = nullptr;
    }

    return addable;
}

bool PetriDish::addObstacle(Obstacle* obstacle)
{
    bool addable = contains(*obstacle);
    if (addable) {
        obstacles.push_back(obstacle);
        deleteUnderObstacle(obstacle);
    } else {
        delete obstacle;
        obstacle = nullptr;
    }

    return addable;
}

void PetriDish::createWall(const Vec2d& position1, const Vec2d& position2)
{
    Vec2d direction = (position2 - position1).normalised();
    double dist(distance(position1, position2));
    double radius = getShortConfig().obstacle_radius;
    Vec2d pos(position1);
    bool addable = true;
    int nbObstacles = (dist - radius) / (2 * radius);

    for (int i(0); i<=nbObstacles and addable; ++i) {
        pos += 2 * radius * direction;
        addable = addObstacle(new Obstacle(pos));
    }
}

void PetriDish::deleteUnderObstacle(Obstacle *obstacle)
{
    for (auto& bacterie : bacteries) {
        if(*obstacle & *bacterie) {
            delete bacterie;
            bacterie = nullptr;
        }
    }
    bacteries.erase(std::remove(bacteries.begin(), bacteries.end(), nullptr),
                    bacteries.end());

    for (auto& nutriment : nutriments) {
        if(*obstacle & *nutriment) {
            delete nutriment;
            nutriment = nullptr;
        }
    }
    nutriments.erase(std::remove(nutriments.begin(), nutriments.end(), nullptr), nutriments.end());
}

void PetriDish::reset()
{
    for (auto& bacterie : bacteries) {
        delete bacterie;
        bacterie = nullptr;
    }
    bacteries.clear();

    for (auto& nutriment : nutriments) {
        delete nutriment;
        nutriment = nullptr;
    }
    nutriments.clear();

    for(auto& swarm : swarms) {
        delete swarm;
        swarm = nullptr;
    }
    swarms.clear();

    for(auto& obstacle : obstacles) {
        delete obstacle;
        obstacle = nullptr;
    }
    obstacles.clear();

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

void PetriDish::updateBacteries(sf::Time dt)
{
    append(annex, bacteries);
    initAnnex();

    for(auto& bacterie : bacteries) {
        if(bacterie->alive()) {
            bacterie->setScore(getPositionScore(bacterie->getPosition(), *bacterie));
            bacterie->update(dt);
        } else {
            delete bacterie;
            bacterie = nullptr;
        }
    }
    bacteries.erase(std::remove(bacteries.begin(), bacteries.end(), nullptr),
                    bacteries.end());
}

void PetriDish::updateNutriments (sf::Time dt)
{
    for(auto& nutriment : nutriments) {
        if (!nutriment->isEmpty()) {
            if(nutriment->temperatureCondition(temperature)) {
                nutriment->update(dt);
            }
        } else {
            delete nutriment;
            nutriment = nullptr;
        }
    }
    nutriments.erase(std::remove(nutriments.begin(), nutriments.end(), nullptr), nutriments.end());
}

void PetriDish::updateSwarms(sf::Time dt)
{
    for(auto& swarms : swarms) {
        swarms->update(dt);
    }
}

void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    //on a ici décidé que l'epaisseur de l'anneau serait 5
    const auto border = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5);
    targetWindow.draw(border);

    for(const auto& nutriment : nutriments) {
        nutriment->drawOn(targetWindow);
    }

    for(const auto& bacterie : bacteries) {
        bacterie->drawOn(targetWindow);
    }

    for(const auto& obstacle : obstacles) {
        obstacle->drawOn(targetWindow);
    }
}

const j::Value& PetriDish::getConfig() const
{
    return getAppConfig()["petri dish"];
}

void PetriDish::increaseTemperature()
{
    temperature += getShortConfig().petridish_delta_temperature;
}

void PetriDish::decreaseTemperature()
{
    temperature -= getShortConfig().petridish_delta_temperature;
}

void PetriDish::initTemperature()
{
    temperature = getShortConfig().petridish_default_temperature;
}

Nutriment* PetriDish::getNutrimentColliding(CircularBody const& body) const
{
    for (const auto& nutriment : nutriments) {
        if (*nutriment & body) {
            return nutriment;
        }
    }
    return nullptr;
}


double PetriDish::getPositionScore(const Vec2d& position, const Bacterium& bacterie) const
{
    double sum(0);

    if(!bacterie.isLost()) {
        for(const auto& nutriment : nutriments) {
            sum += nutriment->getScoreCoefficient(bacterie) * (nutriment->getRadius() / pow(distance(position, nutriment->getPosition()), power));
        }
    }

    for(const auto&  obstacle : obstacles) {
        sum -= obstacle->getRadius()/ pow(distance(position, obstacle->getPosition()), power * getShortConfig().obstacle_gradient_factor);
    }

    return sum;
}

void PetriDish::increaseGradientExponent()
{
    power += getShortConfig().petridish_delta_gradient;
}

void PetriDish::decreaseGradientExponent()
{
    power -= getShortConfig().petridish_delta_gradient;
}

double PetriDish::getGradientExponent() const
{
    return power;
}

void PetriDish::initGradient()
{
    power = (getShortConfig().petridish_max_gradient
             + getShortConfig().petridish_min_gradient)
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

void PetriDish::addSwarm(Swarm* swarm)
{
    swarms.push_back(swarm);
}

Swarm *PetriDish::getSwarmWithId(const std::string& id) const
{
    for(const auto& swarm : swarms) {
        if(swarm->getId() == id) {
            return swarm;
        }
    }
    return nullptr;
}

bool PetriDish::doesCollideWithObstacle(const CircularBody& body) const
{
    for (const auto& obstacle : obstacles) {
        if(*obstacle & body) {
            return true;
        }
    }
    return false;
}

Vec2d PetriDish::getLastObstaclePos() const
{
    return obstacles.empty() ? Vec2d(0, 0) : obstacles.back()->getPosition();
}

double PetriDish::getAverageMutableParam(const std::string &s) const
{
    double value(0.0);
    double sum(0);
    for (const auto& bacterie : bacteries) {
        auto pMutable = bacterie->getparamMutables();
        if(pMutable.find(s) != pMutable.end()) {
            ++sum;
            value += bacterie->getparamMutables().at(s).get();
        }
    }
    return sum != 0 ? ( value/sum) : -1.;
}

double PetriDish::getTotalNutriment() const
{
    double value(0.0);
    for (const auto& nutriment : nutriments) {
        value += nutriment->getQuantity();
    }
    return value;
}

double PetriDish::getAverageDivisionBacteria() const
{
    double average(0);
    for(const auto& bacteria : bacteries) {
        average += bacteria->getDivideCounter();
    }
    int size(bacteries.size());
    return size !=0 ? average /= bacteries.size() : -1;
}

GraphData PetriDish::getPropertyGeneral() const
{
    return {
        {s::SIMPLE_BACTERIA, SimpleBacterium::getSimpleCounter()},
        {s::TWITCHING_BACTERIA, TwitchingBacterium::getTwitchCounter()},
        {s::SWARM_BACTERIA, SwarmBacterium::getSwarmCounter()},
        {s::POISON_BACTERIA, PoisonBacterium::getPoisonCounter()},
        {s::NUTRIMENT_SOURCES, nutriments.size()},
        {s::DISH_TEMPERATURE, getTemperature()}
    };
}

GraphData PetriDish::getPropertyNutrimentQuantity() const
{
    return {{s::NUTRIMENT_QUANTITY, getTotalNutriment()}};
}

GraphData PetriDish::getPropertySimpleBacteria() const
{
    return {{s::BETTER, getAverageMutableParam(s::BETTER)},
        {s::WORSE, (double)getAverageMutableParam(s::WORSE)}};
}

GraphData PetriDish::getPropertyTwitchingBacteria() const
{
    return {
        {s::TENTACLE_LENGTH, getAverageMutableParam(s::TENTACLE_LENGTH)},
        {s::TENTACLE_SPEED, getAverageMutableParam(s::TENTACLE_SPEED)}};
}

GraphData PetriDish::getPropertyBacteria() const
{
    return {{s::SPEED, getAverageMutableParam(s::SPEED)}};
}

GraphData PetriDish::getPropertyBacteriaDivision() const
{
    return {{s::MEAN_DIVISION, getAverageDivisionBacteria()}};
}

GraphData PetriDish::getPropertyNutriment() const
{
    return {
        {s::NUTRIMENT_SOURCES, nutriments.size()},
        {s::NUTRIMENT_A, NutrimentA::getNutriACounter()},
        {s::NUTRIMENT_B, NutrimentB::getNutriBCounter()},
        {s::POISON, Poison::getPoisonCounter()}
    };
}

PetriDish::~PetriDish()
{
    reset();
}
