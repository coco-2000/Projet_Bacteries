#include "SimpleBacterium.hpp"
#include "../Random/Random.hpp"
#include "../Utility/Vec2d.hpp"
#include "Application.hpp"
#include "../Utility/DiffEqSolver.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/Constants.hpp"


SimpleBacterium::SimpleBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(), getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(), getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"],
                {{"speed", MutableNumber::positive(getConfig()["speed"])},
                 {"tumble better", MutableNumber::positive(getConfig()["tumble"]["better"])},
                 {"tumble worse", MutableNumber::positive(getConfig()["tumble"]["worse"])}}),
       t(uniform(0.0, M_PI))
{}

SimpleBacterium::SimpleBacterium(Quantity energie, Vec2d position, Vec2d direction,
                double radius, const MutableColor& couleur,
                std::map<std::string, MutableNumber> param_mutables,
                bool abstinence)
    : Bacterium(energie, position, direction, radius, couleur,
                param_mutables, abstinence)
{}

/**
SimpleBacterium* SimpleBacterium::clone()
{
    SimpleBacterium div(energie, getPosition(), direction, radius,
                               couleur, param_mutables, abstinence);
    div.energie /= 2;
    div.mutate();

    return new SimpleBacterium(div);
}
**/

SimpleBacterium* SimpleBacterium::clone()
{
    return new SimpleBacterium(*this);
}

j::Value const& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}

void SimpleBacterium::move(sf::Time dt)
{
    tps_basculement += dt;
    Vec2d new_position(stepDiffEq(getPosition(), getSpeedVector(), dt,equation).position);

    if((new_position - getPosition()).lengthSquared() >= 0.001)
    {
        consumeEnergy((new_position - getPosition()).length() * getEnergyReleased());
        setPosition(new_position);
    }

    t += 3 * dt.asSeconds();
}

Vec2d SimpleBacterium::getSpeedVector() const
{
    return direction * getProperty("speed").get();
}

void SimpleBacterium::graphisme_particulier(sf::RenderTarget& target) const
{
    int nb_point(30);

    auto set_of_points = sf::VertexArray(sf::LinesStrip);
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
}

void SimpleBacterium::tentative_basculement()
{
    double lambda(getProperty("tumble worse").get());

    if(getAppEnv().getPositionScore(getPosition()) >= ancien_score)
    {
        lambda = getProperty("tumble better").get();
    }

    double proba_basculement = 1 - exp(- tps_basculement.asSeconds() / lambda);

     if(bernoulli(proba_basculement) == 1)
     {
         basculement();
         tps_basculement = sf::Time::Zero;
     }
}

void SimpleBacterium::basculement()
{
    if(getConfig()["tumble"]["algo"] == "single random vector")
    {
        strategie1();
    }
    else if(getConfig()["tumble"]["algo"] == "best of N")
    {
        strategie2();
    }
}

void SimpleBacterium::strategie1()
{
    direction = Vec2d::fromRandomAngle();
}

void SimpleBacterium::strategie2()
{
    int N(20); // nb de directions aléatoires à générer

    for(int i(0); i < N; ++i)
    {
        Vec2d new_dir (Vec2d::fromRandomAngle());

        if(getAppEnv().getPositionScore(getPosition() + new_dir)
           > getAppEnv().getPositionScore(getPosition() + direction))
        {
            setDirection(new_dir);
        }
    }
}
