#pragma once
#include "Bacterium.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/DiffEqSolver.hpp"


class Swarm;

class SwarmBacterium : public Bacterium
{
public:
    SwarmBacterium(const Vec2d& position, Swarm* groupe);

    SwarmBacterium(SwarmBacterium const&);

    void mutate() override;

    void drawOn(sf::RenderTarget &target) const override;

    ~SwarmBacterium();



private:
    Swarm* groupe;


    void move(sf::Time dt) override;

    SwarmBacterium* clone() const override;

    j::Value const& getConfig() const override;

};
