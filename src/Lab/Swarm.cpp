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
        if(element == bacterie)
        {
            element = nullptr;
        }
    }
    groupe.erase(std::remove(groupe.begin(), groupe.end(), nullptr),
                       groupe.end());
    setLeader();
}

Vec2d Swarm::getLeaderPosition() const
{
     return leader->getPosition();
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

    leader = nullptr;
}

void Swarm::setLeader()
{
    if(groupe.empty())
    {
        leader = nullptr;
    }
    else if(groupe.size() == 1)
    {
        leader = groupe.front();
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

bool Swarm::IsLeader(const SwarmBacterium* bacterie)
{
    return bacterie == leader;
}


