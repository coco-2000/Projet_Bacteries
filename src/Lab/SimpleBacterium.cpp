#include "SimpleBacterium.hpp"
#include "Application.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Poison.hpp"
#include "SwimmingBacterium.hpp"

unsigned int SimpleBacterium::simpleCounter(0);

SimpleBacterium::SimpleBacterium(const Vec2d& position)
    : SwimmingBacterium(position, Vec2d::fromRandomAngle(), uniform(getShortConfig().simplebact_min_radius, getShortConfig().simplebact_max_radius),
                        uniform(getShortConfig().simplebact_min_energy, getShortConfig().simplebact_max_energy), getConfig()["color"],
{ {"speed", MutableNumber::positive(getConfig()["speed"])},
    {"tumble better prob", MutableNumber::positive(getConfig()["tumble"]["better"])},
    {"tumble worse prob", MutableNumber::positive(getConfig()["tumble"]["worse"])}
})
{
    ++simpleCounter;
}


SimpleBacterium::SimpleBacterium(const SimpleBacterium& other)
    : SwimmingBacterium(other)
{
    ++simpleCounter;
}

SimpleBacterium* SimpleBacterium::clone() const
{
    return new SimpleBacterium(*this);
}

j::Value const& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}

unsigned int SimpleBacterium::getSimpleCounter()
{
    return simpleCounter;
}

Quantity SimpleBacterium::eatableQuantity(NutrimentA& nutriment) const
{
    return nutriment.eatenBy(*this);
}

Quantity SimpleBacterium::eatableQuantity(NutrimentB& nutriment) const
{
    return nutriment.eatenBy(*this);
}

Quantity SimpleBacterium::eatableQuantity(Poison& poison) const
{
    return poison.eatenBy(*this);
}

double SimpleBacterium::getScoreCoefficient(const NutrimentA& nutriment) const
{
    return nutriment.getScoreCoefficient(*this);
}

double SimpleBacterium::getScoreCoefficient(const NutrimentB& nutriment) const
{
    return nutriment.getScoreCoefficient(*this);
}

double SimpleBacterium::getScoreCoefficient(const Poison& poison) const
{
    return poison.getScoreCoefficient(*this);
}

SimpleBacterium::~SimpleBacterium()
{
    --simpleCounter;
}
