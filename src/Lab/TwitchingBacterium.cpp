#include "TwitchingBacterium.hpp"
#include "Application.hpp"
#include <SFML/Graphics.hpp>

Grip::Grip(const Vec2d& position, double radius) : CircularBody(position, radius) {}

TwitchingBacterium::TwitchingBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(), getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(), getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"],
                {{"tentacle speed", MutableNumber::positive(getConfig()["tentacle"]["speed"])},
                {"tentacle lenght", MutableNumber::positive(getConfig()["tentacle"]["lenght"])}}),
      grapin(position, radius/4)

{}

j::Value const& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

Bacterium* TwitchingBacterium::clone() const
{
    return new TwitchingBacterium(*this);
}

void TwitchingBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);
    //target.draw(buildCircle(grapin.getPosition(), grapin.getRadius(), sf::Color::Black);
}
