#include "Nutriment.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"

Nutriment::Nutriment(Quantity quantity, const Vec2d& position)
    : CircularBody(position, quantity),
      quantity(quantity)
{};

Quantity Nutriment::takeQuantity(Quantity taking)
{
    taking = std::min(quantity, taking);
    setQuantity(quantity - taking);
    return taking;
}

void Nutriment::setQuantity(Quantity qt)
{
    quantity = std::max(qt,0.0);
    setRadius(qt);
}

void Nutriment::drawOn(sf::RenderTarget& target) const
{
    constexpr unsigned int TAILLE_OBJ_GRAPHIQUE(6); //taille de l'objet graphique

    const auto texture = getConfig()["texture"].toString();
    auto nutrimentSprite = buildSprite(getPosition(), TAILLE_OBJ_GRAPHIQUE, getAppTexture(texture));
    // adapte la taille du Sprite au rayon du nutriment:
    nutrimentSprite.setScale(2 * getRadius() / getAppTexture(texture).getSize().x,
                             2 * getRadius() / getAppTexture(texture).getSize().y);
    target.draw(nutrimentSprite);
    displayQuantity(target);
}

void Nutriment::displayQuantity(sf::RenderTarget& target) const
{
    constexpr unsigned int TAILLE_FONTE(15); // taille de fonte

    if(isDebugOn()) {
        auto const text = buildText(std::to_string(static_cast<int>(quantity)),
                                    shift({10,10}),
                                    getAppFont(),
                                    TAILLE_FONTE,
                                    sf::Color::Black, 0);
        target.draw(text);
    }
}

void Nutriment::update(sf::Time dt)
{
    const double growth =  getGrowthSpeed()* static_cast<double>(dt.asSeconds());
    if (quantity <= 2 * getMaxQuantity() and quantity + growth <= getAppEnv().getDistToPetri(getPosition())
        and quantity + growth <= getAppEnv().minimumDistToObstacle(getPosition())) {
        setQuantity(quantity + growth);
    }
}

double Nutriment::getGrowthSpeed() const
{
    return getConfig()["growth"]["speed"].toDouble();
}

double Nutriment::getMaxQuantity() const
{
    return getConfig()["quantity"]["max"].toDouble();
}


bool Nutriment::temperatureCondition(double temperature) const
{
    return (getConfig()["growth"]["min temperature"].toDouble() <= temperature) and
           (getConfig()["growth"]["max temperature"].toDouble() >= temperature);
}

bool Nutriment::isEmpty() const
{
    return (quantity <= 0);
}

Quantity Nutriment::getQuantity() const
{
    return quantity;
}

