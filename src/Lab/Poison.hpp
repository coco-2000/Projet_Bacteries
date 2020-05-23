#pragma once
#include "Nutriment.hpp"
#include "../Interface/Drawable.hpp"

class Poison : public Nutriment
{
public:
    Poison(Vec2d const& position);

    Poison(const Poison& other);

    static double getPoisonCounter();

    Quantity eatenBy(const Bacterium& bacterie) override;

    Quantity eatenBy(const SwarmBacterium& bacterie) override;

    Quantity eatenBy(const SimpleBacterium& bacterie) override;

    Quantity eatenBy(const TwitchingBacterium& bacterie) override;

    Quantity eatenBy(const PoisonBacterium& bacterie) override;

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
