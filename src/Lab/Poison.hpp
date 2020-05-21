#pragma once
#include "Nutriment.hpp"
#include "../Interface/Drawable.hpp"

class Poison : public Nutriment
{
public:
    Poison(Vec2d const& position);

    void drawOn(sf::RenderTarget& target) const override;

    Quantity eatenBy(Bacterium& bacterie) override;

    Quantity eatenBy(SwarmBacterium& bacterie) override;

    Quantity eatenBy(SimpleBacterium& bacterie) override;

    Quantity eatenBy(TwitchingBacterium& bacterie) override;

    Quantity eatenBy(PoisonBacterium& bacterie) override;

    double getPositionScore(const Bacterium& bacterie) const override;

    double getPositionScore(const SimpleBacterium& bacterie) const override;

    double getPositionScore(const SwarmBacterium& bacterie) const override;

    double getPositionScore(const TwitchingBacterium& bacterie) const override;

    double getPositionScore(const PoisonBacterium& bacterie) const override;

private :
    j::Value const& getConfig() const override;
};
