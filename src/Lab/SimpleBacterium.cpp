#include "SimpleBacterium.hpp"
#include "../Random/Random.hpp"
#include "../Utility/Vec2d.hpp"

#include "Application.hpp"
#include "../Utility/DiffEqSolver.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/Constants.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"

double SimpleBacterium::simpleCounter(0);

SimpleBacterium::SimpleBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(), getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(), getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"],
                {{"speed", MutableNumber::positive(getConfig()["speed"])},
                 {"tumble better prob", MutableNumber::positive(getConfig()["tumble"]["better"])},
                 {"tumble worse prob", MutableNumber::positive(getConfig()["tumble"]["worse"])}}),
       t(uniform(0.0, M_PI))

{
    ++simpleCounter;
}

SimpleBacterium::SimpleBacterium(Quantity energie, Vec2d position, Vec2d direction,
                double radius, const MutableColor& couleur,
                std::map<std::string, MutableNumber> param_mutables,
                bool abstinence)
    : Bacterium(energie, position, direction, radius, couleur,
                param_mutables, abstinence)
{}

SimpleBacterium::SimpleBacterium(const SimpleBacterium& other)
    : Bacterium (other), t(uniform(0.0, M_PI))
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

void SimpleBacterium::move(sf::Time dt)
{
    const Vec2d new_position(stepDiffEq(position, getSpeedVector(), dt, *this).position);
    const auto deltaPos = new_position - position;

    if(deltaPos.lengthSquared() >= 0.001)
    {
        consumeEnergy(deltaPos.length() * getStepEnergy());
        CircularBody::move(deltaPos);
    }

    constexpr int COEFF_T = 3;
    t += COEFF_T * dt.asSeconds();

    tps_basculement += dt;
    tentative_basculement();
}

Vec2d SimpleBacterium::getSpeedVector() const
{
    return direction * getProperty("speed").get();
}

void SimpleBacterium::drawOn(sf::RenderTarget& target) const
{
    constexpr int nb_point(30);            
    sf::VertexArray set_of_points = sf::VertexArray(sf::LinesStrip);
      // ajout de points à l'ensemble:

    set_of_points.append({{0,0}, couleur.get()});

    for(int i(1); i < nb_point; ++i)
    {
        set_of_points.append({{static_cast<float>(-i * (getRadius() / 10.0)),
                               static_cast<float>(getRadius() * sin(t) * sin(2 * i / 10.0))},
                               couleur.get()});
    }

     auto transform = sf::Transform(); // déclare une matrice de transformation
     // ici ensemble d'opérations comme des translations ou rotations faites sur transform:
     transform.translate(getPosition());
     transform.rotate(angle / DEG_TO_RAD);
     target.draw(set_of_points, transform);

     Bacterium::drawOn(target);
}

void SimpleBacterium::tentative_basculement()
{
    double lambda(getProperty("tumble worse prob").get());

    if(getAppEnv().getPositionScore(getPosition()) >= ancien_score)
    {
        lambda = getProperty("tumble better prob").get();
    }

    const double proba_basculement = 1 - exp(- tps_basculement.asSeconds() / lambda);

     if(bernoulli(proba_basculement) == 1)
     {
         switchDirection();
         tps_basculement = sf::Time::Zero;
     }
}

void SimpleBacterium::switchDirection()
{
    if(getConfig()["tumble"]["algo"] == "single random vector")
    {
        strategy1();
    }
    else if(getConfig()["tumble"]["algo"] == "best of N")
    {
        strategy2();
    }
}

void SimpleBacterium::strategy1()
{
    direction = Vec2d::fromRandomAngle();
}

void SimpleBacterium::strategy2()
{
    constexpr int N(20); // nb de directions aléatoires à générer

    for(int i(0); i < N; ++i)
    {
        const Vec2d new_dir (Vec2d::fromRandomAngle());

        if(helperPositionScore (new_dir) > helperPositionScore(direction))
        {
            direction = new_dir;
        }
    }
}

Vec2d SimpleBacterium::f(Vec2d position, Vec2d speed) const
{
    return {0, 0};
}

double SimpleBacterium::getSimpleCounter()
{
    return simpleCounter;
}

SimpleBacterium::~SimpleBacterium()
{
    --simpleCounter;
}

Quantity SimpleBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity SimpleBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return nutriment.eatenBy(*this);
}

