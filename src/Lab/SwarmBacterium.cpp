#include "SwarmBacterium.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "../Utility/Utility.hpp"
#include <SFML/Graphics.hpp>
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Poison.hpp"

unsigned int SwarmBacterium::swarmCounter(0);

SwarmBacterium::SwarmBacterium(const Vec2d& position, Swarm* groupe)
    : Bacterium(position, Vec2d::fromRandomAngle(),
                uniform(getShortConfig().swarmbact_min_radius, getShortConfig().swarmbact_max_radius),
                uniform(getShortConfig().swarmbact_min_energy, getShortConfig().swarmbact_max_energy),
                (*groupe).getColor()), group(groupe)
{
    groupe->addBacterium(this);
    ++swarmCounter;
}

SwarmBacterium::SwarmBacterium(SwarmBacterium const& autre)
    : Bacterium(autre), group(autre.group)
{
    group->addBacterium(this);
    ++ swarmCounter;
}

SwarmBacterium* SwarmBacterium::clone() const
{
    return new SwarmBacterium(*this);
}

j::Value const& SwarmBacterium::getConfig() const
{
    return getAppConfig()["swarm bacterium"];
}

void SwarmBacterium::move(sf::Time dt)
{
    Vec2d new_position(getPosition());

    if(isLost())
    {
        new_position = stepDiffEq(getPosition(), getSpeedVector(), dt, *this).position;

        timeSwitching += dt;
        double lambda(getConfig()["lambda basculement"].toDouble());
        const double proba_basculement =  lambda!= 0 ? 1 - exp(- timeSwitching.asSeconds() / lambda) : 1;

        if(bernoulli(proba_basculement) == 1)
        {
         strategy1();
         timeSwitching = sf::Time::Zero;
        }
    }
    else
    {
        const DiffEqResult deplacement(stepDiffEq(getPosition(), getSpeedVector(), dt, *group));
        new_position = deplacement.position;
        speed = deplacement.speed.length();
        setDirection(deplacement.speed.normalised());
    }

    const auto deltaPos = new_position - getPosition();

    if(deltaPos.lengthSquared() >= 0.001)
    {
        consumeEnergy(deltaPos.length() * getStepEnergy());
        CircularBody::move(deltaPos);
    }

    if(group->IsLeader(this))
    {
        strategy2();
    }
}

Vec2d SwarmBacterium::f(Vec2d position, Vec2d speed) const
{
    return {0,0};
}

void SwarmBacterium::drawOn(sf::RenderTarget &target) const
{
    Bacterium::drawOn(target);

    if(isDebugOn() and group->IsLeader(this))
    {
        //on a ici décidé que l'epaisseur de l'anneau serait 5
        const auto anneau = buildAnnulus(getPosition(),
                                         getRadius(),
                                         sf::Color::Red,
                                         5);
        target.draw(anneau);
    }
}

Vec2d SwarmBacterium::getSpeedVector() const
{
    if(isLost())
        return getDirection() * (speed + getShortConfig().swarmbact_speed)/2;
    else
        return getDirection() * getShortConfig().swarmbact_speed;
}

unsigned int SwarmBacterium::getSwarmCounter()
{
    return swarmCounter;
}

Quantity SwarmBacterium::eatableQuantity(NutrimentA& nutriment) const
{
    return nutriment.eatenBy(*this);
}

Quantity SwarmBacterium::eatableQuantity(NutrimentB& nutriment) const
{
    return nutriment.eatenBy(*this);
}

Quantity SwarmBacterium::eatableQuantity(Poison& poison) const
{
    return poison.eatenBy(*this);
}

double SwarmBacterium::getScoreCoefficient(const NutrimentA& nutriment) const
{
    return nutriment.getScoreCoefficient(*this);
}

double SwarmBacterium::getScoreCoefficient(const NutrimentB& nutriment) const
{
    return nutriment.getScoreCoefficient(*this);
}

double SwarmBacterium::getScoreCoefficient(const Poison& poison) const
{
    return poison.getScoreCoefficient(*this);
}

SwarmBacterium::~SwarmBacterium()
{
    --swarmCounter;
    group->supprBacterium(this);
}
