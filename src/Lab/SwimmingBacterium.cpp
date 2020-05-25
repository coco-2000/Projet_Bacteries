#include "SwimmingBacterium.hpp"
#include "Application.hpp"

SwimmingBacterium::SwimmingBacterium(const Vec2d& position, const Vec2d& direction, double radius,
                                       Quantity energy, const MutableColor& color,
                                       const std::map<std::string, MutableNumber>& paramMutables,
                                       bool abstinence)
   : Bacterium(position, direction, radius, energy, color, paramMutables, abstinence), timeFlagellum(uniform(0.0, M_PI))
{}

SwimmingBacterium::SwimmingBacterium(const SwimmingBacterium& other)
    : Bacterium (other), timeFlagellum(uniform(0.0, M_PI))
{}

void SwimmingBacterium::move(sf::Time dt)
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

    trySwitch(dt);
}

Vec2d SwimmingBacterium::getSpeedVector() const
{
    return getDirection() * getProperty("speed").get();
}

void SwimmingBacterium::drawOn(sf::RenderTarget& target) const
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

void SwimmingBacterium::trySwitch(sf::Time dt)
{
    if(isLost())
    {
        lostTrySwitch(dt);
    }
    else
    {
        double lambda(getProperty("tumble worse prob").get());

        if(getAppEnv().getPositionScore(getPosition(), *this) >= getOldScore())
            lambda = getProperty("tumble better prob").get();

        setTimeSwitch(getTimeSwitch() + dt);
        const double switchProba = lambda != 0 ? 1 - exp(- getTimeSwitch().asSeconds() / lambda) : 1;

        if(bernoulli(switchProba) == 1)
         {
             switchDirection();
             setTimeSwitch(sf::Time::Zero);
         }
    }
}

void SwimmingBacterium::switchDirection()
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

Vec2d SwimmingBacterium::f(Vec2d position, Vec2d speed) const
{
    return {0, 0};
}

void SwimmingBacterium::setLost(bool isLost)
{
    Bacterium::setLost(isLost);
    setTimeSwitch(sf::Time::Zero);
}

