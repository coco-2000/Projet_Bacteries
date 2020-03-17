#include "Nutriment.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"

constexpr unsigned int TAILLE_OBJ_GRAPHIQUE(6);

Nutriment::Nutriment(Quantity quantity, const Vec2d& position)
    : CircularBody(position, quantity), quantity_(quantity) {};

Quantity Nutriment::takeQuantity(Quantity prelevement)
{
    if(prelevement < quantity_)
    {
        quantity_ -= prelevement;
        return prelevement;
    }
    else
    {
        prelevement -= quantity_;
        quantity_ = 0.0;
        return prelevement;
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
}

j::Value const& Nutriment::getConfig() const
{
    return getAppConfig()["nutriments"];
}
