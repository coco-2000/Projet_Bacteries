#include "SwarmBacterium.hpp"
#include "Application.hpp"
#include "Swarm.hpp"

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
