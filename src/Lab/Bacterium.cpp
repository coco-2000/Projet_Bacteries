#include "Bacterium.hpp"
#include "../Utility/Utility.hpp"
#include "Application.hpp"
#include "CircularBody.hpp"
#include "Nutriment.hpp"

Bacterium::Bacterium(const Vec2d& position, const Vec2d& direction, double radius, Quantity energy,
                     const MutableColor& color, const std::map<std::string, MutableNumber>& paramMutables,
                     bool abstinence)

    : CircularBody(position, radius), color(color), direction(direction), energy(energy),
      paramMutables(paramMutables), abstinence(abstinence), lost(false)
{
    angle = direction.angle();
}


void Bacterium::divide()
{
    if(energy >= getEnergy())
    {
        energy /= 2;
        Bacterium* copy(clone());
        copy->mutate();
        copy->shiftClone({10,-10}); //pour que l'on puisse tout de suite voir s'il y a eu division
        getAppEnv().addAnnex(copy);
        direction = Vec2d::fromAngle(getAngle() + M_PI/2);
    }
}
void Bacterium::shiftClone(const Vec2d& v)
{
    CircularBody::move(v);
}

void Bacterium::mutate()
{
    color.mutate();

    for(auto& param : paramMutables)
    {
        param.second.mutate();
    }
}

bool Bacterium::alive() const
{
    return energy > 0;
}

Quantity Bacterium::getEnergy() const
{
    return getConfig()["energy"]["division"].toDouble();
}

sf::Time Bacterium::getDelay() const
{
    return sf::seconds(getConfig()["meal"]["delay"].toDouble());
}

sf::Time Bacterium::getMaxTimeLost() const
{
    return sf::seconds(getConfig()["lost"]["time"].toDouble());
}

sf::Time Bacterium::getTimeSwitch() const
{
    return timeSwitch;
}

void Bacterium::setTimeSwitch(sf::Time newTime)
{
    timeSwitch = newTime;
}

double Bacterium::getLostEnergyFactor() const
{
    return getConfig()["lost"]["energy factor"].toDouble();
}

double Bacterium::getLostLambdaSwitch() const
{
    return getConfig()["lost"]["lambda switch"].toDouble();
}

Quantity Bacterium::getStepEnergy() const
{
    double stepEnergy(getConfig()["energy"]["consumption factor"].toDouble());
    return lost ? getLostEnergyFactor()*stepEnergy : stepEnergy;
}

Quantity Bacterium::getMaxEatableQuantity() const
{
    return getConfig()["meal"]["max"].toDouble();
}

void Bacterium::drawOn(sf::RenderTarget& target) const
{
    target.draw(buildCircle(getPosition(), getRadius(), color.get()));
    displayEnergy(target);
}

void Bacterium::displayEnergy(sf::RenderTarget& target) const
{
    constexpr unsigned int TAILLE_FONTE(15); // taille de fonte

    if(isDebugOn())
    {
        target.draw(buildText(std::to_string(static_cast<int>(energy)),
                              shift({10,10}),
                              getAppFont(),
                              TAILLE_FONTE,
                              sf::Color::Red, 0));
    }
}

void Bacterium::update(sf::Time dt)
{
    move(dt);
    collision();
    rotationAngle(dt);
    consumeNutriment(dt);
    divide();

    if(lost)
        manageLost(dt);
}

void Bacterium::collision()
{
    lost = true;
    if (getAppEnv().doesCollideWithObstacle(*this))
        strategy2();

    else if(getAppEnv().doesCollideWithDish(*this))
        direction = - direction;
}

void Bacterium::consumeNutriment(sf::Time dt)
{
    Nutriment* nutriment_ptr = getAppEnv().getNutrimentColliding(*this);

    if(nutriment_ptr != nullptr and consumeCounter >= getDelay() and !abstinence)
    {
        consumeCounter = sf::Time::Zero;
        eat(*nutriment_ptr);
        nutriment_ptr = nullptr;

        lost = false;
        timeLost = sf::Time::Zero;
    }
    else
    {
      consumeCounter += dt;
    }
}

void Bacterium::manageLost(sf::Time dt)
{
    if (timeLost >= getMaxTimeLost())
    {
        lost = false;
        timeLost = sf::Time::Zero;
    }
    else
        timeLost += dt;
}

void Bacterium::consumeEnergy(Quantity qt)
{
    energy -= qt;
}

void Bacterium::setScore(double score)
{
    if(score > 0)
    {
        oldScore = score;
    }
}

void Bacterium::addProperty(const std::string& key, const MutableNumber& value)
{
    if(paramMutables.find(key) != paramMutables.end())
    {
        throw std::invalid_argument("ajout d'une propriété associée à une clé déjà existante");
    }
    else
    {
        paramMutables.at(key) = value;
    }
}

MutableNumber Bacterium::getProperty(const std::string& key) const
{
    if(paramMutables.find(key) == paramMutables.end())
    {
        throw std::out_of_range("recherche de la valeur d'une clé invalide ");
    }
    else
    {
        return paramMutables.find(key)->second;
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

double Bacterium::helperPositionScore (const Vec2d& offset, const Bacterium& bacterie) const
{
    return getAppEnv().getPositionScore(getPosition() + offset, bacterie);
}

std::map<std::string, MutableNumber> Bacterium::getparamMutables() const
{
    return paramMutables;
}

double Bacterium::getAngle() const
{
    return angle;
}

sf::Color Bacterium::getColor() const
{
    return color.get();
}

Vec2d Bacterium::getDirection() const
{
    return direction;
}

void Bacterium::setDirection(const Vec2d& newDir)
{
    direction = newDir;
}

void Bacterium::setLost(bool islost)
{
   lost = islost;
}

double Bacterium::getOldScore() const
{
    return oldScore;
}

bool Bacterium::isLost() const
{
    return lost;
}

void Bacterium::eat(Nutriment& nutriment)
{
  Quantity eaten(nutriment.eatenBy(*this));
  energy += eaten;
}

void Bacterium::lostTrySwitch(sf::Time dt)
{
    timeSwitch += dt;
    double lambda(getLostLambdaSwitch());
    const double proba_basculement = lambda != 0 ? 1 - exp(-timeSwitch.asSeconds() / lambda) : 1;

    if(bernoulli(proba_basculement))
     {
         strategy1();
         timeSwitch = sf::Time::Zero;
     }
}

void Bacterium::strategy1()
{
    setDirection(Vec2d::fromRandomAngle());
}

void Bacterium::strategy2()
{
    constexpr int N(20); // nb de directions aléatoires à générer

    for(int i(0); i < N; ++i)
    {
        const Vec2d newDir (Vec2d::fromRandomAngle());
        double newScore = helperPositionScore (newDir, *this);

        if(newScore > helperPositionScore(getDirection(), *this))
        {
            setDirection(newDir);
        }
    }
}
