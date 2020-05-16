#include "Swarm.hpp"
#include "../Application.hpp"
#include "../Utility/MutableColor.hpp"
#include <string>
#include "../Utility/Utility.hpp"
#include <SFML/Graphics.hpp>
#include "SwarmBacterium.hpp"


Swarm::Swarm(const std::string& identificateur, const std::vector <SwarmBacterium*>& groupe)
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
    return getConfig()[id]["color"];
}

void Swarm::addBacterium(SwarmBacterium* bacterie)
{
    group.push_back(bacterie);

    if(leader == nullptr)
    {
        setLeader();
    }
}

void Swarm::supprBacterium(SwarmBacterium* bacterie)
{
    for(auto& element : group)
    {
        if(element == bacterie)
        {
            element = nullptr;
            break;
        }
    }
    group.erase(std::remove(group.begin(), group.end(), nullptr),
                       group.end());

    if(bacterie == leader)
    {
        setLeader();
    }
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
        SwarmBacterium* temp(group.front());
        for(auto& bacterie : group)
        {
            if (getAppEnv().getPositionScore(bacterie->getPosition())
                > getAppEnv().getPositionScore(temp->getPosition()))
            {
                temp = bacterie;
            }
        }
        leader = temp;
        temp = nullptr;
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
