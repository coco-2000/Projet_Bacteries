#include "Nutriment.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include "Config.hpp"
#include "../Utility/Vec2d.hpp"

#include<algorithm>

Nutriment::Nutriment(Quantity quantity, const Vec2d& position)
    : CircularBody(position, quantity),
      dist((0.95/2)*getApp().getLabSize().x - distance(getApp().getCentre(),position)),
      quantity_(quantity)
{};

Quantity Nutriment::takeQuantity(Quantity prelevement)
{
        testPrelevement(prelevement);
        setQuantity(quantity_ - prelevement);
        return prelevement;
}

Quantity Nutriment:: testPrelevement(Quantity& prelevement) const
{
    if(prelevement >= quantity_) {prelevement = quantity_;}
    return prelevement;
}

void Nutriment::setQuantity(Quantity quantity)
{
    quantity_ = std::max(quantity,0.0);
    //quantity >= 0 ? quantity_ = quantity : quantity_ = 0.0;
    setRadius(quantity_);
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

    if(isDebugOn())
    {
        auto const text = buildText(std::to_string(static_cast<int>(quantity_)),
                                    decalage({10,10}),
                                    getAppFont(),
                                    TAILLE_FONTE,
                                    sf::Color::Black, 0);
        target.draw(text);
    }
}

void Nutriment::update(sf::Time dt)
{
    const double growth =  getConfig()["growth"]["speed"].toDouble()* static_cast<double>(dt.asSeconds());
    if (quantity_ <= 2 * getConfig()["quantity"]["max"].toDouble() and quantity_ + growth <= dist)
    {
        setQuantity(quantity_ + growth);
    }
}

bool Nutriment::ConditionTemperature(double temperature) const
{
    return (getConfig()["growth"]["min temperature"].toDouble() <= temperature) and
            (getConfig()["growth"]["max temperature"].toDouble() >= temperature);
}

bool Nutriment::isEmpty() const
{
    return (quantity_ <= 0);
}

Quantity Nutriment::getQuantity() const
{
    return quantity_;
}

