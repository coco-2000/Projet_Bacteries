#include "SimpleBacterium.hpp"
#include "../Random/Random.hpp"
#include "../Utility/Vec2d.hpp"

#include "Application.hpp"
#include "../Utility/DiffEqSolver.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/Constants.hpp"
#include "PoisonBacterium.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Poison.hpp"

unsigned int SimpleBacterium::simpleCounter(0);

SimpleBacterium::SimpleBacterium(const Vec2d& position)
    : Bacterium(position, Vec2d::fromRandomAngle(), uniform(getShortConfig().simplebact_min_radius, getShortConfig().simplebact_max_radius),
                uniform(getShortConfig().simplebact_min_energy, getShortConfig().simplebact_max_energy), getConfig()["color"],
                {{"speed", MutableNumber::positive(getConfig()["speed"])},
                 {"tumble better prob", MutableNumber::positive(getConfig()["tumble"]["better"])},
                 {"tumble worse prob", MutableNumber::positive(getConfig()["tumble"]["worse"])}}),
       timeFlagellum(uniform(0.0, M_PI))
{ ++simpleCounter; }

SimpleBacterium::SimpleBacterium(const Vec2d& position, const Vec2d& direction, double radius,
                                 Quantity energy, const MutableColor& color,
                                 const std::map<std::string, MutableNumber>& paramMutables,
                                 bool abstinence)
   : Bacterium(position, direction, radius, energy, color, paramMutables, abstinence), timeFlagellum(uniform(0.0, M_PI))
{ ++simpleCounter; }

SimpleBacterium::SimpleBacterium(const SimpleBacterium& other)
    : Bacterium (other), timeFlagellum(uniform(0.0, M_PI))
{ ++simpleCounter; }

SimpleBacterium* SimpleBacterium::clone() const
{
    return new SimpleBacterium(*this);
}

j::Value const& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}

void SimpleBacterium::move(sf::Time dt)
{
    const Vec2d new_position(stepDiffEq(getPosition(), getSpeedVector(), dt, *this).position);
    const auto deltaPos = new_position - getPosition();

    if(deltaPos.lengthSquared() >= 0.001)
    {
        consumeEnergy(deltaPos.length() * getStepEnergy());
        CircularBody::move(deltaPos);
    }

    constexpr int COEFF_T = 3;
    timeFlagellum += COEFF_T * dt.asSeconds();

    timeSwitching += dt;
    trySwitch();
}

Vec2d SimpleBacterium::getSpeedVector() const
{
    return getDirection() * getProperty("speed").get();
}

void SimpleBacterium::drawOn(sf::RenderTarget& target) const
{
    constexpr int nbPoint(30);
    sf::VertexArray setOfPoints = sf::VertexArray(sf::LinesStrip);
      // ajout de points à l'ensemble:

    setOfPoints.append({{0,0}, getColor()});

    for(int i(1); i < nbPoint; ++i)
    {
        setOfPoints.append({{static_cast<float>(-i * (getRadius() / 10.0)),
                             static_cast<float>(getRadius() * sin(timeFlagellum) * sin(2 * i / 10.0))},
                            getColor()});
    }

     auto transform = sf::Transform(); // déclare une matrice de transformation
     // ici ensemble d'opérations comme des translations ou rotations faites sur transform:
     transform.translate(getPosition());
     transform.rotate(getAngle() / DEG_TO_RAD);
     target.draw(setOfPoints, transform);

     Bacterium::drawOn(target);
}

void SimpleBacterium::trySwitch()
{
    double lambda(getProperty("tumble worse prob").get());

    if(getAppEnv().getPositionScore(getPosition(), *this) >= getOldScore())
    {
        lambda = getProperty("tumble better prob").get();
    }

    const double switchProba = lambda != 0 ? 1 - exp(- timeSwitching.asSeconds() / lambda) : 1;

     if(bernoulli(switchProba) == 1)
     {
         switchDirection();
         timeSwitching = sf::Time::Zero;
     }
}

void SimpleBacterium::switchDirection()
{
    if(getShortConfig().simplebact_tumble_algo == "single random vector")
    {
        strategy1();
    }
   if(getShortConfig().simplebact_tumble_algo == "best of N")
    {
        strategy2();
    }
}

Vec2d SimpleBacterium::f(Vec2d position, Vec2d speed) const
{
    return {0, 0};
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
{ --simpleCounter; }
