#include "TwitchingBacterium.hpp"

#include "Application.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"

unsigned int TwitchingBacterium::twitchCounter(0);

TwitchingBacterium::TwitchingBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(), getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(), getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"],
                {{"tentacle speed", MutableNumber::positive(getConfig()["tentacle"]["speed"])},
                {"tentacle length", MutableNumber::positive(getConfig()["tentacle"]["length"])}}),
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
    return getConfig()["energy"]["consumption factor"]["move"].toDouble();
}

Quantity TwitchingBacterium::getTentacleEnergy() const
{
    return getConfig()["energy"]["consumption factor"]["tentacle"].toDouble();
}

void TwitchingBacterium::moveGrip(const Vec2d& delta)
{
    grip.move(delta);
}

void TwitchingBacterium::move(sf::Time dt)
{
    const Nutriment* nutriment_ptr = getAppEnv().getNutrimentColliding(grip);

    switch(state)
    {
        case IDLE : state = WAIT_TO_DEPLOY; break;
        case WAIT_TO_DEPLOY : waitToDeployState(); break;
        case DEPLOY : deployState(dt, nutriment_ptr); break;
        case ATTRACT : attractState(dt, nutriment_ptr); break;
        case RETRACT : retractState (dt); break;
        case EAT : eatState(nutriment_ptr); break;
    }

    nutriment_ptr = nullptr;
}

void TwitchingBacterium::waitToDeployState()
{
    constexpr int N(20); // nb de directions aléatoires à générer

    for(int i(0); i < N; ++i)
    {
        const Vec2d new_dir (Vec2d::fromRandomAngle());
        if(helperPositionScore (new_dir) > helperPositionScore(getDirection()))
            setDirection(new_dir);
    }

    state = DEPLOY;
}

void TwitchingBacterium::deployState(sf::Time dt, const Nutriment* nutriment_ptr)
{
    gripToward(getDirection(), dt);

    if(nutriment_ptr != nullptr)
        state = ATTRACT;
    else if ( (grip.getPosition() - getPosition()).length() >= getProperty("tentacle length").get()
              or getAppEnv().doesCollide(grip))
        state = RETRACT;
}

void TwitchingBacterium::attractState(sf::Time dt, const Nutriment *nutriment_ptr)
{

     const double dist_tentacule = getProperty("tentacle speed").get()*dt.asSeconds();
     const Vec2d deltaPos((grip.getPosition()-getPosition())*dist_tentacule*getConfig()["speed factor"].toDouble());

     CircularBody::move(deltaPos);
     consumeEnergy(deltaPos.length() * getStepEnergy());

     if (nutriment_ptr == nullptr)
         state = RETRACT;

     else if (*nutriment_ptr & *this)
         state = EAT;
}

void TwitchingBacterium::tentacleInit()
{
    moveGrip(getPosition() - grip.getPosition());
    state = IDLE;
}

void TwitchingBacterium::retractState(sf::Time dt)
{
    (*this > grip) ? tentacleInit() : gripToward((getPosition()-grip.getPosition()).normalised(), dt);
}

void TwitchingBacterium::gripToward (const Vec2d& dir, sf::Time dt)
{
    setDirection(dir);
    const double dist_tentacule = getProperty("tentacle speed").get()*dt.asSeconds();
    moveGrip(dir*dist_tentacule);
    consumeEnergy(getTentacleEnergy()*dist_tentacule);
}

void TwitchingBacterium::eatState(const Nutriment *nutriment_ptr)
{
    if ((nutriment_ptr == nullptr) or (!(*nutriment_ptr & *this)))
        state = IDLE;
}

void TwitchingBacterium::shiftClone(const Vec2d& v)
{
    Bacterium::shiftClone(v);
    moveGrip(v);
}

unsigned int TwitchingBacterium::getTwitchCounter()
{
    return twitchCounter;
}

Quantity TwitchingBacterium::eatableQuantity(NutrimentA& nutriment)
{
    return nutriment.eatenBy(*this);
}

Quantity TwitchingBacterium::eatableQuantity(NutrimentB& nutriment)
{
    return nutriment.eatenBy(*this);
}

TwitchingBacterium::~TwitchingBacterium()
{
    -- twitchCounter;
}
