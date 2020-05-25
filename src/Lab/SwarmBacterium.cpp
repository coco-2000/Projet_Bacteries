#include "SwarmBacterium.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "../Utility/Utility.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Poison.hpp"

unsigned int SwarmBacterium::swarmCounter(0);

SwarmBacterium::SwarmBacterium(const Vec2d& position, Swarm* group)
    : Bacterium(position, Vec2d::fromRandomAngle(),
                uniform(getShortConfig().swarmbact_min_radius, getShortConfig().swarmbact_max_radius),
                uniform(getShortConfig().swarmbact_min_energy, getShortConfig().swarmbact_max_energy),
                (*group).getColor()), group(group)
{
    group->addBacterium(this);
    ++swarmCounter;
}

SwarmBacterium::SwarmBacterium(SwarmBacterium const& other)
    : Bacterium(other), group(other.group)
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
    Vec2d newPosition(getPosition());

    if(isLost())
    {
        newPosition = stepDiffEq(getPosition(), getSpeedVector(), dt, *this).position;
        lostTrySwitch(dt);
    }
    else
    {
        const DiffEqResult shifting(stepDiffEq(getPosition(), getSpeedVector(), dt, *group));
        newPosition = shifting.position;
        speed = shifting.speed.length();
        setDirection(shifting.speed.normalised());
    }

    const auto deltaPos = newPosition - getPosition();

    if(deltaPos.lengthSquared() >= 0.001)
    {
        consumeEnergy(deltaPos.length() * getStepEnergy());
        CircularBody::move(deltaPos);
    }

    if(group->IsLeader(this) and !isLost())
        strategy2();
}

Vec2d SwarmBacterium::f(Vec2d position, Vec2d speed) const
{
    return {0,0};
}

void SwarmBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);

    if(isDebugOn() and group->IsLeader(this))
    {
        //on a ici décidé que l'epaisseur de l'anneau serait 5
        const auto anneau = buildAnnulus(getPosition(), getRadius(),
                                         sf::Color::Red, 5);
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
