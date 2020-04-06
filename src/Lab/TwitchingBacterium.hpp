#pragma once

#include "Bacterium.hpp"

class TwitchingBacterium : public Bacterium
{
public :


protected :
    j::Value const& getConfig() const override;
    void move(sf::Time dt) override; //à définir
    Bacterium* clone() const override;
};
