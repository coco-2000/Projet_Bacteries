#include "Poison.hpp"
#include "Application.hpp"
#include "../Utility/Utility.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"

double Poison::poisonCounter(0);

Poison::Poison(Vec2d const& position)
    : Nutriment(uniform(getShortConfig().poison_min_qty,
                        getShortConfig().poison_max_qty),
                position)
{
    ++poisonCounter;
}

Poison::Poison(const Poison& other)
    : Nutriment(other)
{
    ++poisonCounter;
}

j::Value const& Poison::getConfig() const
{
    return getAppConfig()["nutriments"]["poison"];
}

void Poison::drawOn(sf::RenderTarget& target) const
{
    target.draw(buildCircle(getPosition(), getRadius(), sf::Color::Black));
}

double Poison::getPoisonCounter()
{
    return poisonCounter;
}

Quantity Poison::eatenBy(Bacterium& bacterie)
{
    return bacterie.eatableQuantity(*this);
}

Quantity Poison::eatenBy(SwarmBacterium& bacterie)
{
    setQuantity(0);
    return - bacterie.getMaxEatableQuantity() / getShortConfig().poison_resistance_factor;
}

Quantity Poison::eatenBy(SimpleBacterium& bacterie)
{
    return - getShortConfig().poison_toxic_factor * takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity Poison::eatenBy(TwitchingBacterium& bacterie)
{
    return - getShortConfig().poison_toxic_factor * takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity Poison::eatenBy(PoisonBacterium& bacterie)
{
    return 0;
}

double Poison::getScoreCoefficient(const Bacterium& bacterie) const
{
    return bacterie.getScoreCoefficient(*this);
}

double Poison::getScoreCoefficient(const SimpleBacterium& bacterie) const
{
    return 0;
}

double Poison::getScoreCoefficient(const SwarmBacterium& bacterie) const
{
    return 0;
}

double Poison::getScoreCoefficient(const TwitchingBacterium& bacterie) const
{
    return 0;
}

double Poison::getScoreCoefficient(const PoisonBacterium& bacterie) const
{
    return 0;
}

Poison::~Poison()
{
    --poisonCounter;
}
