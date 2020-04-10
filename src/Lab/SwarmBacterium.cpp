#include "SwarmBacterium.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "../Utility/DiffEqSolver.hpp"

SwarmBacterium::SwarmBacterium(const Vec2d& position, Swarm* groupe)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),
                        getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(),
                        getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"]), groupe(groupe)
{
    groupe->addBacterium(this);
}

SwarmBacterium::SwarmBacterium(SwarmBacterium const& autre)
    : Bacterium(autre), groupe(autre.groupe)
{
    groupe->addBacterium(this);
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
    DiffEqResult deplacement(stepDiffEq(getPosition(), getSpeedVector(), dt, *groupe));

    const Vec2d new_position(deplacement.position);
    setDirection(deplacement.speed / deplacement.speed.length());

    if((new_position - getPosition()).lengthSquared() >= 0.001)
    {
        consumeEnergy((new_position - getPosition()).length() * getStepEnergyReleased());
        setPosition(new_position);
    }

    groupe->LeaderDirection();
}

void SwarmBacterium::mutate()
{
    couleur.mutate();
}

SwarmBacterium::~SwarmBacterium()
{
    groupe = nullptr;
}

void SwarmBacterium::drawOn(sf::RenderTarget &target) const
{
    Bacterium::drawOn(target);
}

Vec2d SwarmBacterium::getSpeedVector() const
{
    return direction * getConfig()["speed"]["initial"].toDouble();
}


