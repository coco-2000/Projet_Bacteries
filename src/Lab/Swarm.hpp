#pragma once
#include <vector>
#include "../Utility/MutableColor.hpp"
#include <string>
#include "../Interface/Updatable.hpp"
#include "SwarmBacterium.hpp"

class Swarm : public Updatable, public DiffEqFunction
{
public:
    Swarm(std::string identificateur, const std::vector <SwarmBacterium*>& groupe = {});

    MutableColor getColor(std::string id) const;

    void addBacterium(SwarmBacterium* bacterie);
    void supprBacterium(SwarmBacterium* bacterie);

    Vec2d getLeaderPosition() const;
    SwarmBacterium* getLeader() const;

    std::string getId() const;
    void update(sf::Time dt);

    void drawOn(sf::RenderTarget& target) const;

    void LeaderDirection();

    ~Swarm();
private:
    std::string identificateur;
    std::vector <SwarmBacterium*> groupe;
    SwarmBacterium* leader;
    MutableColor couleur;

    void setLeader();
    Vec2d f(Vec2d position, Vec2d speed) const;
    j::Value getConfig() const;

};

