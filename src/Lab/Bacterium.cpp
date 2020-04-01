#include "Bacterium.hpp"
#include "../Utility/Utility.hpp"
#include "Application.hpp"
#include "CircularBody.hpp"

Bacterium::Bacterium(Quantity energie, Vec2d position, Vec2d direction,
                     double radius, const MutableColor& couleur,
                     std::map<std::string, MutableNumber> param_mutables,
                     bool abstinence)

    : CircularBody(position, radius), couleur(couleur), energie(energie),
      param_mutables(param_mutables), abstinence(abstinence)
{
    setDirection(direction);
}

/*Bacterium::Bacterium(const Bacterium& autre)
    : CircularBody(autre), couleur(autre.couleur), energie(autre.energie),
      param_mutables(autre.param_mutables), abstinence(autre.abstinence)
{
    setDirection(autre.direction);
}*/

Bacterium* Bacterium::clone()
{
    if(energie >= getEnergy())
    {
        Bacterium* copie((*this).copie());
        copie->energie /= 2;
        copie->mutate();

        energie /= 2;
        setDirection(-direction);

        return copie;
    }
    else
    {
        return nullptr;
    }
}

void Bacterium::mutate()
{
    couleur.mutate();

    for(auto& param : param_mutables)
    {
        param.second.mutate();
    }
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

void Bacterium::setDirection(Vec2d dir)
{
    direction = dir;
    angle = direction.angle();
}

void Bacterium::drawOn(sf::RenderTarget& target) const
{
    target.draw(buildCircle(position, radius, couleur.get()));
    graphisme_particulier(target);
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
    tps_basculement += dt;
    move(dt);
    tentative_basculement();
    collisionPetri(dt);
    consumeNutriment(dt);
    getAppEnv().ajout_annexe(Bacterium::clone());
}

void Bacterium::collisionPetri(sf::Time dt)
{
    if (getAppEnv().doesCollideWithDish(*this))
    {
        direction = -direction;

        auto const angleDiff = angleDelta(direction.angle(), angle); // calcule la différence entre le nouvel
                                                                          // angle de direction et l'ancien
        auto dalpha = PI * dt.asSeconds();    // calcule dα
        dalpha = std::min(dalpha, std::abs(angleDiff)); // on ne peut tourner plus que de angleDiff

        dalpha = std::copysign(dalpha, angleDiff); // on tourne dans la direction indiquée par angleDiff
        angle += dalpha; // angle de rotation mis à jour
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



void Bacterium::setScore(double score)
{
    if(score > 0)
    {
        ancien_score = score;
    }
}

void Bacterium::addProperty(const std::string& key, MutableNumber valeur)
{
    if(param_mutables.find(key) != param_mutables.end())
    {
        throw std::invalid_argument("ajout d'une propriété associée à une clé déjà existante");
    }
    else
    {
        param_mutables[key] = valeur;
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

