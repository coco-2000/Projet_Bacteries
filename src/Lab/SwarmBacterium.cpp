#include "SwarmBacterium.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "../Utility/Utility.hpp"
#include <SFML/Graphics.hpp>
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"

unsigned int SwarmBacterium::swarmCounter(0);

SwarmBacterium::SwarmBacterium(const Vec2d& position, Swarm* groupe)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),
                        getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(),
                        getConfig()["radius"]["max"].toDouble()),
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
    const DiffEqResult deplacement(stepDiffEq(getPosition(), getSpeedVector(), dt, *group));

    const Vec2d new_position(deplacement.position);
    setDirection(deplacement.speed.normalised());

    const auto deltaPos = new_position - getPosition();

    if(deltaPos.lengthSquared() >= 0.001)
    {
        consumeEnergy(deltaPos.length() * getStepEnergy());
        CircularBody::move(deltaPos);
    }

    if(group->IsLeader(this))
    {
        moveLeader();
    }
}

void SwarmBacterium::moveLeader()
{
    strategy2();
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
    return getDirection() * getConfig()["speed"]["initial"].toDouble();
}

unsigned int SwarmBacterium::getSwarmCounter()
{
    return swarmCounter;
}

Quantity SwarmBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity SwarmBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return nutriment.eatenBy(*this);
}

SwarmBacterium::~SwarmBacterium()
{
    --swarmCounter;
    group->supprBacterium(this);
}
