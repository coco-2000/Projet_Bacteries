#include "TwitchingBacterium.hpp"
#include "Application.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.hpp"


TwitchingBacterium::TwitchingBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(), getConfig()["energy"]["max"].toDouble()),
                position,
                Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(), getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"],
                {{"tentacle speed", MutableNumber::positive(getConfig()["tentacle"]["speed"])},
                {"tentacle length", MutableNumber::positive(getConfig()["tentacle"]["length"])}}),
      grip(position, radius/4),
      state(IDLE)

{}

j::Value const& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

Bacterium* TwitchingBacterium::clone() const
{
    TwitchingBacterium* twitching = new TwitchingBacterium(*this);
    twitching->tentacle_init();

    return twitching;
}

void TwitchingBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);
    const auto line = buildLine(position, grip.getPosition(), couleur.get(), 1);
    target.draw(line);
    const auto circle = buildCircle(grip.getPosition(), grip.getRadius(), couleur.get());
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
        case WAIT_TO_DEPLOY : Wait_to_deploy_state(); break;
        case DEPLOY : deploy_state(dt, nutriment_ptr); break;
        case ATTRACT : attract_state(dt, nutriment_ptr); break;
        case RETRACT : retract_state (dt); break;
        case EAT : eat_state(nutriment_ptr); break;
    }

    nutriment_ptr = nullptr;
}

void TwitchingBacterium::Wait_to_deploy_state()
{
    constexpr int N(20); // nb de directions aléatoires à générer

    for(int i(0); i < N; ++i)
    {
        const Vec2d new_dir (Vec2d::fromRandomAngle());
        if(helperPositionScore (new_dir) > helperPositionScore(direction))
            direction = new_dir;
    }

    state = DEPLOY;
}

void TwitchingBacterium::deploy_state(sf::Time dt, const Nutriment* nutriment_ptr)
{
    gripToward(direction, dt);

    if(nutriment_ptr != nullptr)
        state = ATTRACT;
    else if ( (grip.getPosition() - position).length() >= getProperty("tentacle length").get() or getAppEnv().doesCollideWithDish(grip) )
        state = RETRACT;
}

void TwitchingBacterium::attract_state(sf::Time dt, const Nutriment *nutriment_ptr)
{

     const double dist_tentacule = getProperty("tentacle speed").get()*dt.asSeconds();
     const Vec2d deltaPos((grip.getPosition()-position)*dist_tentacule*getConfig()["speed factor"].toDouble());

     CircularBody::move(deltaPos);
     consumeEnergy(deltaPos.length() * getStepEnergy());

     if (nutriment_ptr == nullptr)
         state = RETRACT;

     else if (*nutriment_ptr & *this)
         state = EAT;
}

void TwitchingBacterium::tentacle_init()
{
    moveGrip(position - grip.getPosition());
    state = IDLE;
}

void TwitchingBacterium::retract_state(sf::Time dt)
{
    (*this > grip) ? tentacle_init() : gripToward((position-grip.getPosition()).normalised(), dt);
}

void TwitchingBacterium::gripToward (const Vec2d& dir, sf::Time dt)
{
    direction = dir;
    const double dist_tentacule = getProperty("tentacle speed").get()*dt.asSeconds();
    moveGrip(dir*dist_tentacule);
    consumeEnergy(getTentacleEnergy()*dist_tentacule);
}

void TwitchingBacterium::eat_state(const Nutriment *nutriment_ptr)
{
    if (nutriment_ptr == nullptr)
        state = IDLE;
    else if (!(*nutriment_ptr & *this))
        state = IDLE;
}

void TwitchingBacterium::shift_clone(const Vec2d& v)
{
    Bacterium::shift_clone(v);
    moveGrip(v);
}

double TwitchingBacterium::getTwitchCounter()
{
    return twitchBcounter;
}

