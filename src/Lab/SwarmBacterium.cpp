#include "SwarmBacterium.hpp"
#include "Application.hpp"
#include "Swarm.hpp"
#include "../Utility/Utility.hpp"
#include <SFML/Graphics.hpp>

SwarmBacterium::SwarmBacterium(const Vec2d& position, Swarm* groupe)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),
                        getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(),
                        getConfig()["radius"]["max"].toDouble()),
                (*groupe).getColor()), groupe(groupe)
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
    const DiffEqResult deplacement(stepDiffEq(position, getSpeedVector(), dt, *groupe));

    const Vec2d new_position(deplacement.position);
    direction = deplacement.speed.normalised();

    const auto deltaPos = new_position - position;

    if(deltaPos.lengthSquared() >= 0.001)
    {
        consumeEnergy(deltaPos.length() * getStepEnergy());
        position = new_position;
    }

    if(groupe->IsLeader(this))
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
            setDirection(new_dir);
        }
    }
}

void SwarmBacterium::mutate()
{
    couleur.mutate();
}

SwarmBacterium::~SwarmBacterium()
{
    groupe->supprBacterium(this);
}

void SwarmBacterium::drawOn(sf::RenderTarget &target) const
{
    Bacterium::drawOn(target);

    if(isDebugOn() and groupe->IsLeader(this))
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
