#pragma once
#include "Bacterium.hpp"
#include "../Utility/DiffEqSolver.hpp"

class SimpleBacterium : public Bacterium
{
public:
    SimpleBacterium(const Vec2d& position);

    j::Value const& getConfig() const;

    void move(sf::Time dt);

    Vec2d getSpeedVector() const;

    SimpleBacterium* clone() const;


private :
    MRU equation;

    //void graphisme_particulier(sf::RenderTarget& target, sf::Time dt = 0) const;
};
