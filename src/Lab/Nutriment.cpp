#include "Nutriment.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include "Config.hpp"


Nutriment::Nutriment(Quantity quantity, const Vec2d& position)
    : CircularBody(position, quantity), quantity_(quantity) {};

Quantity Nutriment::takeQuantity(Quantity prelevement)
{
        TestPrelevement(prelevement);
        setQuantity(quantity_ - prelevement);
        return prelevement;
}

void Nutriment:: TestPrelevement(Quantity& prelevement)
{
    if(prelevement > quantity_)
    {
        prelevement -= quantity_;
    }
}

void Nutriment::setQuantity(Quantity quantity)
{
    if(quantity >= 0)
    {
        quantity_ = quantity;
    }
    else
    {
        quantity_ = 0.0;
    }

    radius = quantity_;
}

void Nutriment::drawOn(sf::RenderTarget& target) const
{
    auto nutrimentSprite = buildSprite(position, TAILLE_OBJ_GRAPHIQUE, getAppTexture(getConfig()["texture"].toString()));
         // adapte la taille du Sprite au rayon du nutriment:
         nutrimentSprite.setScale(2 * radius / getAppTexture(getConfig()["texture"].toString()).getSize().x, 2 * radius / getAppTexture(getConfig()["texture"].toString()).getSize().y);
        target.draw(nutrimentSprite);
        DisplayQuantity(target);
}

j::Value const& Nutriment::getConfig() const
{
    return getAppConfig()["nutriments"];
}

void Nutriment::DisplayQuantity(sf::RenderTarget& target) const
{
    if(isDebugOn())
    {
        auto const text = buildText(std::to_string(quantity_), decalage({10,10}), getAppFont(), TAILLE_FONTE, sf::Color::Black, 0);
        target.draw(text);
    }
}

void update(sf::Time dt)
{
    auto growth = getConfig()["growth"]["speed"] * dt.asSeconds();
}
