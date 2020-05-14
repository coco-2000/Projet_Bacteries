#include "Bacterium.hpp"
#include "../Utility/Utility.hpp"
#include "Application.hpp"
#include "CircularBody.hpp"
#include "Nutriment.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"

Bacterium::Bacterium(Quantity energie, const Vec2d& position, const Vec2d& direction,
                     double radius, const MutableColor& couleur,
                     const std::map<std::string, MutableNumber>& param_mutables,
                     bool abstinence)

    : CircularBody(position, radius), couleur(couleur), direction(direction), energie(energie),
      param_mutables(param_mutables), abstinence(abstinence)
{
    angle = direction.angle();
}


void Bacterium::divide()
{
    if(energie >= getEnergy())
    {
        energie /= 2;
        Bacterium* copie(clone());
        copie->mutate();
        copie->shift_clone({10,-10}); //pour que l'on puisse tout de suite voir s'il y a eu division
        getAppEnv().addAnnex(copie);
        direction = Vec2d::fromAngle(M_PI/2);
    }
}
void Bacterium::shift_clone(const Vec2d& v)
{
    CircularBody::move(v);
}

void Bacterium::mutate()
{
    couleur.mutate();

    for(auto& param : param_mutables)
    {
        param.second.mutate();
    }
}

bool Bacterium::alive() const
{
    return energie > 0;
}

Quantity Bacterium::getEnergy() const
{
    return getConfig()["energy"]["division"].toDouble();
}

sf::Time Bacterium::getDelay() const
{
    return sf::seconds(getConfig()["meal"]["delay"].toDouble());
}

Quantity Bacterium::getStepEnergy() const
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
    constexpr unsigned int TAILLE_FONTE(15); // taille de fonte

    if(isDebugOn())
    {
        target.draw(buildText(std::to_string(static_cast<int>(energie)),
                              decalage({10,10}),
                              getAppFont(),
                              TAILLE_FONTE,
                              sf::Color::Red, 0));
    }
}

void Bacterium::update(sf::Time dt)
{
    move(dt);
    collisionPetri();
    rotationAngle(dt);
    consumeNutriment(dt);
    divide();
}

void Bacterium::collisionPetri()
{
    if (getAppEnv().doesCollideWithDish(*this))
    {
        direction = -direction;
    }
}

void Bacterium::collisionObstacle()
{
    if (getAppEnv().doesCollideWithObstacle(*this))
    {
        direction = -direction;
    }
}

void Bacterium::consumeNutriment(sf::Time dt)
{
    Nutriment* nutriment_ptr = getAppEnv().getNutrimentColliding(*this);

    if(nutriment_ptr != nullptr and compteur >= getDelay() and !abstinence)
    {
        compteur = sf::Time::Zero;
        eat(*nutriment_ptr);
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

void Bacterium::setScore(double score)
{
    if(score > 0)
    {
        ancien_score = score;
    }
}

void Bacterium::addProperty(const std::string& key, const MutableNumber& valeur)
{
    if(param_mutables.find(key) != param_mutables.end())
    {
        throw std::invalid_argument("ajout d'une propriété associée à une clé déjà existante");
    }
    else
    {
        param_mutables.at(key) = valeur;
    }
}

MutableNumber Bacterium::getProperty(const std::string& key) const
{
    if(param_mutables.find(key) == param_mutables.end())
    {
        throw std::out_of_range("recherche de la valeur d'une clé invalide ");
    }
    else
    {
        return param_mutables.find(key)->second;
    }
}

void Bacterium::rotationAngle(sf::Time dt)
{
    auto const angleDiff = angleDelta(direction.angle(), angle); // calcule la différence entre le nouvel
                                                                      // angle de direction et l'ancien
    auto dalpha = PI * dt.asSeconds();    // calcule dα
    dalpha = std::min(dalpha, std::abs(angleDiff)); // on ne peut tourner plus que de angleDiff

    dalpha = std::copysign(dalpha, angleDiff); // on tourne dans la direction indiquée par angleDiff
    angle += dalpha; // angle de rotation mis à jour
}

double Bacterium::helperPositionScore (const Vec2d& offset) const
{
    return getAppEnv().getPositionScore(getPosition() + offset);
}


std::map<std::string, MutableNumber> Bacterium::getParam_mutables() const
{
    return param_mutables;
}

Quantity Bacterium::getMaxEatableQuantity() const
{
    return getConfig()["meal"]["max"].toDouble();
}

void Bacterium::eat(Nutriment& nutriment)
{
  Quantity eaten(nutriment.eatenBy(*this));
  energie += eaten;
}
