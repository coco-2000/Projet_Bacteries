#include "TwitchingBacterium.hpp"
#include "Application.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.hpp"

Grip::Grip(const Vec2d& position, double radius) : CircularBody(position, radius) {}

TwitchingBacterium::TwitchingBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(), getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(), getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"],
                {{"tentacle speed", MutableNumber::positive(getConfig()["tentacle"]["speed"])},
                {"tentacle length", MutableNumber::positive(getConfig()["tentacle"]["length"])}}),
      grapin(position, radius/4)

{}

j::Value const& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

Bacterium* TwitchingBacterium::clone() const
{
    TwitchingBacterium* twitching = new TwitchingBacterium(*this);

    //Pour avoir le grapin à nouveau à la même position que la bacterie
    twitching->moveGrip(getPosition()-twitching->grapin.getPosition());

    return twitching;
}

void TwitchingBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);
    const auto line = buildLine(position, grapin.getPosition(), couleur.get(), 1);
    target.draw(line);
    const auto circle = buildCircle(grapin.getPosition(), grapin.getRadius(), couleur.get());
    target.draw(circle);
}

Quantity TwitchingBacterium::getStepEnergy() const
{
    return getConfig()["energy"]["consumption factor"]["move"].toDouble();
}

Quantity TwitchingBacterium::getTentacleEnergy() const
{
    return getConfig()["energy"]["consumption factor"]["tentacle"].toDouble();
}

void TwitchingBacterium::moveGrip(const Vec2d &position)
{
    grapin.move(position);
}







