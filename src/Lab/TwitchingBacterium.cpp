#include "TwitchingBacterium.hpp"
#include "Application.hpp"
#include "../Utility/Utility.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Poison.hpp"

unsigned int TwitchingBacterium::twitchCounter(0);

TwitchingBacterium::TwitchingBacterium(const Vec2d& position)
    : Bacterium(position, Vec2d::fromRandomAngle(),
                uniform(getShortConfig().twitchingbact_min_radius, getShortConfig().twitchingbact_max_radius),
                uniform(getShortConfig().twitchingbact_min_energy, getShortConfig().twitchingbact_max_energy),
                getConfig()["color"],
{ {"tentacle speed", MutableNumber::positive(getConfig()["tentacle"]["speed"])},
    {"tentacle length", MutableNumber::positive(getConfig()["tentacle"]["length"])}
}),
grip(position, getRadius()/4),
state(IDLE)

{
    ++twitchCounter;
}

TwitchingBacterium::TwitchingBacterium(const TwitchingBacterium& other)
    : Bacterium(other), grip(getPosition(), getRadius()/4), state(IDLE)
{
    ++twitchCounter;
}

j::Value const& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

Bacterium* TwitchingBacterium::clone() const
{
    TwitchingBacterium* twitching = new TwitchingBacterium(*this);
    twitching->tentacleInit();

    return twitching;
}

void TwitchingBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);
    const auto line = buildLine(getPosition(), grip.getPosition(), getColor(), 1);
    target.draw(line);
    const auto circle = buildCircle(grip.getPosition(), grip.getRadius(), getColor());
    target.draw(circle);
}

Quantity TwitchingBacterium::getStepEnergy() const
{
    double stepEnergy(getShortConfig().twitchingbact_consumption_factor_move);
    return isLost() ? getLostEnergyFactor()*stepEnergy : stepEnergy;
}

Quantity TwitchingBacterium::getTentacleEnergy() const
{
    double tentacleEnergy(getShortConfig().twitchingbact_consumption_factor_tentacle);
    return isLost() ? getLostEnergyFactor()*tentacleEnergy : tentacleEnergy;
}

Quantity TwitchingBacterium::getFatigueEnergy() const
{
    return getShortConfig().twitchingbact_consumption_factor_fatigue ;
}

void TwitchingBacterium::moveGrip(const Vec2d& delta)
{
    grip.move(delta);
}

void TwitchingBacterium::move(sf::Time dt)
{
    const Nutriment* nutrimentPtr = getAppEnv().getNutrimentColliding(grip);

    switch(state) {
    case IDLE :
        state = WAIT_TO_DEPLOY;
        break;
    case WAIT_TO_DEPLOY :
        waitToDeploy(dt);
        break;
    case DEPLOY :
        deploy(dt, nutrimentPtr);
        break;
    case ATTRACT :
        attract(dt, nutrimentPtr);
        break;
    case RETRACT :
        retract (dt);
        break;
    case EAT :
        eat(nutrimentPtr);
        break;
    }

    nutrimentPtr = nullptr;
}

void TwitchingBacterium::waitToDeploy(sf::Time dt)
{
    if(isLost())
        lostTrySwitch(dt);
    else
        strategy2();

    state = DEPLOY;
}

void TwitchingBacterium::deploy(sf::Time dt, const Nutriment* nutrimentPtr)
{
    gripToward(getDirection(), dt);

    //pour empêcher que les bactéries avec une vitesse de tentacule nulle restent immortelles
    consumeEnergy(getFatigueEnergy());

    if(nutrimentPtr != nullptr)
        state = ATTRACT;

    else if((grip.getPosition() - getPosition()).length() >= getProperty("tentacle length").get()
            or getAppEnv().doesCollideWithDish(grip) or getAppEnv().doesCollideWithObstacle(grip)) {
        state = RETRACT;
        if(getAppEnv().doesCollideWithObstacle(grip))
            setLost(true);
    }
}

void TwitchingBacterium::attract(sf::Time dt, const Nutriment* nutrimentPtr)
{

    const double distTentacule = getProperty("tentacle speed").get()*dt.asSeconds();
    const Vec2d deltaPos((grip.getPosition() - getPosition()) * distTentacule * getShortConfig().twitchingbact_speed_factor);

    CircularBody::move(deltaPos);
    consumeEnergy(deltaPos.length() * getStepEnergy());

    if (nutrimentPtr == nullptr)
        state = RETRACT;
    else if (*nutrimentPtr & *this)
        state = EAT;
}

void TwitchingBacterium::tentacleInit()
{
    moveGrip(getPosition() - grip.getPosition());
    state = IDLE;
}

void TwitchingBacterium::retract(sf::Time dt)
{
    if(*this > grip)
        tentacleInit();
    else
        gripToward((getPosition() - grip.getPosition()).normalised(), dt);
}

void TwitchingBacterium::gripToward(const Vec2d& direction, sf::Time dt)
{
    setDirection(direction);
    const double distTentacle = getProperty("tentacle speed").get()*dt.asSeconds();
    moveGrip(direction * distTentacle);
    consumeEnergy(getTentacleEnergy() * distTentacle);
}

void TwitchingBacterium::eat(const Nutriment* nutrimentPtr)
{
    if ((nutrimentPtr == nullptr) or (!(*nutrimentPtr & *this)))
        state = IDLE;
}

void TwitchingBacterium::shiftClone(const Vec2d& v)
{
    Bacterium::shiftClone(v);
    moveGrip(v);
}

Quantity TwitchingBacterium::eatableQuantity(NutrimentA& nutriment) const
{
    return nutriment.eatenBy(*this);
}

Quantity TwitchingBacterium::eatableQuantity(NutrimentB& nutriment) const
{
    return nutriment.eatenBy(*this);
}

Quantity TwitchingBacterium::eatableQuantity(Poison& poison) const
{
    return poison.eatenBy(*this);
}

double TwitchingBacterium::getScoreCoefficient(const NutrimentA& nutriment) const
{
    return nutriment.getScoreCoefficient(*this);
}

double TwitchingBacterium::getScoreCoefficient(const NutrimentB& nutriment) const
{
    return nutriment.getScoreCoefficient(*this);
}

double TwitchingBacterium::getScoreCoefficient(const Poison& poison) const
{
    return poison.getScoreCoefficient(*this);
}

unsigned int TwitchingBacterium::getTwitchCounter()
{
    return twitchCounter;
}

TwitchingBacterium::~TwitchingBacterium()
{
    -- twitchCounter;
}
