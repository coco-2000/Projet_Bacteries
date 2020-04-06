#pragma once

#include "Bacterium.hpp"
#include "../Utility/Grip.hpp"

class TwitchingBacterium : public Bacterium
{
public :
    TwitchingBacterium(const Vec2d& position);
    void drawOn(sf::RenderTarget& target) const override;

protected :
    Grip grapin;

    j::Value const& getConfig() const override;
    void move(sf::Time dt) override {} //à définir
    Bacterium* clone() const override;
};
