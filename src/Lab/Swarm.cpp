#include "Swarm.hpp"
#include "../Application.hpp"
#include "../Utility/MutableColor.hpp"
#include <string>
#include "../Utility/Utility.hpp"
#include <SFML/Graphics.hpp>
#include "SwarmBacterium.hpp"


Swarm::Swarm(std::string identificateur, const std::vector <SwarmBacterium*>& groupe)
    : id(identificateur), group(groupe), color(getColor())
{
    setLeader();
}

void Swarm::update(sf::Time dt)
{
    setLeader();
}

MutableColor Swarm::getColor() const
{
    return getAppConfig()["swarms"][id]["color"];
}

void Swarm::addBacterium(SwarmBacterium* bacterie)
{
    group.push_back(bacterie);
    setLeader();
}

void Swarm::supprBacterium(SwarmBacterium* bacterie)
{
    for(auto& element : group)
    {
        if(element == bacterie)
        {
            element = nullptr;
        }
    }
    group.erase(std::remove(group.begin(), group.end(), nullptr),
                       group.end());
    setLeader();
}

Vec2d Swarm::getLeaderPosition() const
{
     return leader->getPosition();
}

std::string Swarm::getId() const
{
    return id;
}

void Swarm::setLeader()
{
    if(group.empty())
    {
        leader = nullptr;
    }
    else if(group.size() == 1)
    {
        leader = group.front();
    }
    else
    {
        for(auto& bacterie : group)
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
        return (getConfig()[id]["force factor"].toDouble()) * (getLeaderPosition() - position);
}

bool Swarm::IsLeader(const SwarmBacterium* bacterie) const
{
    return bacterie == leader;
}

Swarm::~Swarm()
{
    for(auto& element : group)
    {
        element = nullptr;
    }

    leader = nullptr;
}
