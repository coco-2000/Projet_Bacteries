#include "Swarm.hpp"
#include "../Application.hpp"
#include "../Utility/MutableColor.hpp"
#include <string>
#include "../Utility/Utility.hpp"
#include <SFML/Graphics.hpp>
#include "SwarmBacterium.hpp"


Swarm::Swarm(std::string identificateur, const std::vector <SwarmBacterium*>& groupe)
    : identificateur(identificateur), groupe(groupe), couleur(getColor())
{
    setLeader();
}

void Swarm::update(sf::Time dt)
{
    setLeader();
}

MutableColor Swarm::getColor() const
{
    return getAppConfig()["swarms"][identificateur]["color"];
}

void Swarm::addBacterium(SwarmBacterium* bacterie)
{
    groupe.push_back(bacterie);
    setLeader();
}

void Swarm::supprBacterium(SwarmBacterium* bacterie)
{
    for(auto& element : groupe)
    {
        if (element == bacterie)
        {
            //delete element;
            element = nullptr;
        }
    }
    setLeader();
}

Vec2d Swarm::getLeaderPosition() const
{
     return leader->getPosition();
}

void Swarm::drawOn(sf::RenderTarget& target) const
{
    if(isDebugOn() and leader != nullptr)
    {
        //on a ici décidé que l'epaisseur de l'anneau serait 5
        const auto anneau = buildAnnulus(getLeaderPosition(),
                                         leader->getRadius(),
                                         sf::Color::Red,
                                         5);
        target.draw(anneau);
    }
}

std::string Swarm::getId() const
{
    return identificateur;
}

Swarm::~Swarm()
{
    for(auto& element : groupe)
    {
        element = nullptr;
    }
}

void Swarm::setLeader()
{
    if(groupe.size() == 0)
    {
        leader = nullptr;
    }
    else if(groupe.size() == 1)
    {
        leader = groupe[0];
    }
    else
    {
        for(auto& bacterie : groupe)
        {
            if (getAppEnv().getPositionScore((*bacterie).getPosition())
                > getAppEnv().getPositionScore(getLeaderPosition()))
            {
                leader = bacterie;
            }
        }
    }
}

j::Value Swarm::getConfig() const
{
    return getAppConfig()["swarms"];
}

Vec2d Swarm::f(Vec2d position, Vec2d speed) const
{
    return (getConfig()[identificateur]["force factor"].toDouble()) * (getLeaderPosition() - position);
}

void Swarm::updateLeaderDirection()
{
    if(leader != nullptr)
    {
        constexpr int nb_vecteur(20); // nb de directions aléatoires à générer

        for(int i(0); i < nb_vecteur; ++i)
        {
            Vec2d new_dir(Vec2d::fromRandomAngle());

            if(leader->helperPositionScore(new_dir) > leader->helperPositionScore())
            {
                leader->setDirection(new_dir);
            }
        }
    }
}


