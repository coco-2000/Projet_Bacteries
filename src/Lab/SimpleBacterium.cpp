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
                getConfig()["color"]),
                t(uniform(0.0, M_PI))
{}



j::Value const& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}

void SimpleBacterium::move(sf::Time dt)
{
    Vec2d new_position(stepDiffEq(getPosition(),
                                  getSpeedVector(),
                                  dt,
                                  equation).position);
    consumeEnergy((new_position - getPosition()).length() * getEnergyReleased());
    setPosition(new_position);
    t += 3 * dt.asSeconds();
}

Vec2d SimpleBacterium::getSpeedVector() const
{
    double agrandissement(20.0);
    return direction * agrandissement;
}

SimpleBacterium* SimpleBacterium::clone() const
{
    return nullptr;
}

void SimpleBacterium::graphisme_particulier(sf::RenderTarget& target) const
{
    int nb_point(30);

    auto set_of_points = sf::VertexArray(sf::TrianglesStrip);
      // ajout de points à l'ensemble:
    set_of_points.append({{0,0}, sf::Color::Black});

    for(int i(1); i < nb_point; ++i)
    {
        set_of_points.append({{static_cast<float>(-i * (getRadius() / 10.0)),
                               static_cast<float>(getRadius() * sin(t) * sin(2 * i / 10.0))},
                              sf::Color::Black});
    }

    auto transform = sf::Transform(); // déclare une matrice de transformation
     // ici ensemble d'opérations comme des translations ou rotations faites sur transform:
     transform.translate(getPosition());
     transform.rotate(angle / DEG_TO_RAD);
     target.draw(set_of_points, transform);
}
