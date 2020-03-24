#include "Nutriment.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include "Config.hpp"
#include "../Utility/Vec2d.hpp"


Nutriment::Nutriment(Quantity quantity, const Vec2d& position)
    : CircularBody(position, quantity),
      dist(ratio_rayon*getApp().getLabSize().x - distance(getApp().getCentre(),
                                                          position)),
      quantity_(quantity)
{};

Quantity Nutriment::takeQuantity(Quantity prelevement)
{
        TestPrelevement(prelevement);
        setQuantity(quantity_ - prelevement);
        return prelevement;
}

void Nutriment:: TestPrelevement(Quantity& prelevement)
{
    if(prelevement > quantity_) prelevement -= quantity_;
}

void Nutriment::setQuantity(Quantity quantity)
{
    quantity >= 0 ? quantity_ = quantity : quantity_ = 0.0;
    setRadius(quantity_);
}

void Nutriment::drawOn(sf::RenderTarget& target) const
{
    unsigned int TAILLE_OBJ_GRAPHIQUE(6); //taille de l'objet graphique

    auto texture = getConfig()["texture"].toString();
    auto nutrimentSprite = buildSprite(position,
                                       TAILLE_OBJ_GRAPHIQUE,
                                       getAppTexture(texture));
         // adapte la taille du Sprite au rayon du nutriment:
         nutrimentSprite.setScale(2 * radius/getAppTexture(texture).getSize().x,
                                  2 * radius / getAppTexture(texture).getSize().y);
        target.draw(nutrimentSprite);
        DisplayQuantity(target);
}

void Nutriment::DisplayQuantity(sf::RenderTarget& target) const
{
    unsigned int TAILLE_FONTE(15); // taille de fonte

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
    auto growth =  getConfig()["growth"]["speed"].toDouble()
            * static_cast<double>(dt.asSeconds());
    if (quantity_ <= 2 * getConfig()["quantity"]["max"].toDouble() &&
            quantity_ + growth <= dist)
    {
        setQuantity(quantity_ + growth);
    }
}

bool Nutriment::ConditionTemperature(double temperature)
{
    return (getConfig()["growth"]["min temperature"].toDouble() <= temperature) and
            (getConfig()["growth"]["max temperature"].toDouble() >= temperature);
}


