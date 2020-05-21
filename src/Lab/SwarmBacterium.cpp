#include "SwarmBacterium.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "../Utility/Utility.hpp"
#include <SFML/Graphics.hpp>
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Poison.hpp"

double SwarmBacterium::swarmCounter(0);

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
    constexpr int nb_vecteur(20); // nb de directions aléatoires à générer

    for(int i(0); i < nb_vecteur; ++i)
    {
        Vec2d new_dir(Vec2d::fromRandomAngle());

        if(helperPositionScore(new_dir, *this) > helperPositionScore(getDirection(), *this))
        {
            setDirection(new_dir);
        }
    }
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
    return getDirection() * getShortConfig().swarmbact_speed;
}

double SwarmBacterium::getSwarmCounter()
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

Quantity SwarmBacterium::eatableQuantity(Poison& poison)
{
    return poison.eatenBy(*this);
}

double SwarmBacterium::getPositionScore(const NutrimentA& nutriment) const
{
    return nutriment.getPositionScore(*this);
}

double SwarmBacterium::getPositionScore(const NutrimentB& nutriment) const
{
    return nutriment.getPositionScore(*this);
}

double SwarmBacterium::getPositionScore(const Poison& poison) const
{
    return poison.getPositionScore(*this);
}

SwarmBacterium::~SwarmBacterium()
{
    --swarmCounter;
    group->supprBacterium(this);
}
