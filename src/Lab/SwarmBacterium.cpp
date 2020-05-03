#include "SwarmBacterium.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "../Utility/Utility.hpp"
#include <SFML/Graphics.hpp>
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"

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
}

SwarmBacterium::SwarmBacterium(SwarmBacterium const& autre)
    : Bacterium(autre), group(autre.group)
{
    group->addBacterium(this);
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
    const DiffEqResult deplacement(stepDiffEq(position, getSpeedVector(), dt, *group));

    const Vec2d new_position(deplacement.position);
    direction = deplacement.speed.normalised();

    const auto deltaPos = new_position - position;

    if(deltaPos.lengthSquared() >= 0.001)
    {
        consumeEnergy(deltaPos.length() * getStepEnergy());
        position = new_position;
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

        if(helperPositionScore(new_dir) > helperPositionScore(direction))
        {
            direction = new_dir;
        }
    }
}

void SwarmBacterium::mutate()
{
    couleur.mutate();
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
    return direction * getConfig()["speed"]["initial"].toDouble();
}

SwarmBacterium::~SwarmBacterium()
{
    group->supprBacterium(this);
}

Quantity SwarmBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity SwarmBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return nutriment.eatenBy(*this);
}
