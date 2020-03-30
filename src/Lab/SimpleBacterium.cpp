#include "SimpleBacterium.hpp"
#include "../Random/Random.hpp"
#include "../Utility/Vec2d.hpp"
#include "Application.hpp"
#include "../Utility/DiffEqSolver.hpp"

SimpleBacterium::SimpleBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(), getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(), getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"])
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

}

Vec2d SimpleBacterium::getSpeedVector() const
{
    double agrandissement(5.0);
    return direction * agrandissement;
}

SimpleBacterium* SimpleBacterium::clone() const
{
    return nullptr;
}
