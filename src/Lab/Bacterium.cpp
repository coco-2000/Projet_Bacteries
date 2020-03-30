#include "Bacterium.hpp"
#include "../Utility/Utility.hpp"
#include "Application.hpp"
#include "CircularBody.hpp"

Bacterium::Bacterium(Quantity energie, Vec2d position, Vec2d direction,
                     double radius, const MutableColor& couleur, bool abstinence,
                     std::map<std::string, MutableNumber> param_mutables)

    : CircularBody(position, radius), couleur(couleur), direction(direction),
      energie(energie), abstinence(abstinence), param_mutables(param_mutables)
{}

Bacterium* Bacterium::clone() const
{
    return nullptr;
}

bool Bacterium::en_vie()
{
    return !(energie<=0);
}

Quantity Bacterium::getEnergy() const
{
    return getConfig()["energy"]["division"].toDouble();
}

sf::Time Bacterium::getDelay() const
{
    return sf::seconds(getConfig()["meal"]["delay"].toDouble());
}

Quantity Bacterium::getEnergyReleased() const
{
    return getConfig()["energy"]["consumption factor"].toDouble();
}

void Bacterium::drawOn(sf::RenderTarget& target) const
{
    target.draw(buildCircle(position, radius, couleur.get()));

    DisplayEnergy(target);
}

void Bacterium::DisplayEnergy(sf::RenderTarget& target) const
{
    unsigned int TAILLE_FONTE(15); // taille de fonte

    if(isDebugOn())
    {
        auto const text = buildText(std::to_string(static_cast<int>(energie)),
                                    decalage({10,10}),
                                    getAppFont(),
                                    TAILLE_FONTE,
                                    sf::Color::Red, 0);
        target.draw(text);
    }
}

void Bacterium::update(sf::Time dt)
{
    move(dt);
    collisionPetri();
    consumeNutriment(dt);
}

void Bacterium::collisionPetri()
{
    if (getAppEnv().doesCollideWithDish(*this))
    {
        direction = -direction;
    }
}

void Bacterium::consumeNutriment(sf::Time dt)
{
    Nutriment* nutriment_ptr = getAppEnv().getNutrimentColliding(*this);

    if(nutriment_ptr != nullptr and !abstinence and compteur >= getDelay())
    {
        compteur = sf::Time::Zero;
        double quantite_consommee = getConfig()["meal"]["max"].toDouble();
        nutriment_ptr->takeQuantity(quantite_consommee);
        nutriment_ptr = nullptr;
    }
    else
    {
      compteur += dt;
    }
}

void Bacterium::consumeEnergy(Quantity qt)
{
    energie -= qt;
}
