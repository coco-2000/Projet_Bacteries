#include "Bacterium.hpp"
#include "../Utility/Utility.hpp"
#include "Application.hpp"
#include "CircularBody.hpp"

Bacterium::Bacterium(Quantity energie, Vec2d position, Vec2d direction,
                     double radius, const MutableColor& couleur, bool abstinence,
                     std::map<std::string, MutableNumber> param_mutables)

    : CircularBody(position, radius), couleur(couleur), energie(energie), abstinence(abstinence),
      param_mutables(param_mutables)
{
    setDirection(direction);
}

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

void Bacterium::tentative_basculement()
{
    double lambda(0.05);

    if(getAppEnv().getPositionScore(getPosition()) >= ancien_score)
    {
        lambda = 5;
    }
     proba_basculement = 1 - exp(- tps_basculement.asSeconds() / lambda);

     if(bernoulli(proba_basculement) == 1)
     {
         basculement();
         tps_basculement = sf::Time::Zero;
     }
}

void Bacterium::basculement()
{
    if(getConfig()["tumble"]["algo"] == "single random vector")
    {
        strategie1();
    }
    else if(getConfig()["tumble"]["algo"] == "best of N")
    {
        strategie2();
    }
}

void Bacterium::setScore(double score)
{
    if(score > 0)
    {
        ancien_score = score;
    }
}

void Bacterium::strategie1()
{
    direction = Vec2d::fromRandomAngle();

}

void Bacterium::strategie2()
{
    int N(20); // nb de directions aléatoires à générer

    for(int i(0); i < N; ++i)
    {
        Vec2d new_dir (Vec2d::fromRandomAngle());

        if(getAppEnv().getPositionScore(getPosition() + new_dir)
           > getAppEnv().getPositionScore(getPosition() + direction))
        {
            setDirection(new_dir);
        }
    }
}
