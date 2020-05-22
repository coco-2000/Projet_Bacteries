#pragma once
#include "Nutriment.hpp"
#include "../Interface/Drawable.hpp"

class Poison : public Nutriment
{
public:
    Poison(Vec2d const& position);

    Poison(const Poison& other);

    void drawOn(sf::RenderTarget& target) const override;

    static double getPoisonCounter();

    Quantity eatenBy(Bacterium& bacterie) override;

    Quantity eatenBy(SwarmBacterium& bacterie) override;

    Quantity eatenBy(SimpleBacterium& bacterie) override;

    Quantity eatenBy(TwitchingBacterium& bacterie) override;

    Quantity eatenBy(PoisonBacterium& bacterie) override;

    double getScoreCoefficient(const Bacterium& bacterie) const override;

    double getScoreCoefficient(const SimpleBacterium& bacterie) const override;

    double getScoreCoefficient(const SwarmBacterium& bacterie) const override;

    double getScoreCoefficient(const TwitchingBacterium& bacterie) const override;

    double getScoreCoefficient(const PoisonBacterium& bacterie) const override;

    ~Poison();

private :
    static double poisonCounter;

    j::Value const& getConfig() const override;
};
