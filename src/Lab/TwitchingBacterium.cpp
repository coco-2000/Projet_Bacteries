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
      grapin(position, radius/4),
      etat(IDLE)

{}

j::Value const& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

Bacterium* TwitchingBacterium::clone() const
{
    TwitchingBacterium* twitching = new TwitchingBacterium(*this);

    //pour que l'on puisse tout de suite voir s'il y a eu division
    twitching->CircularBody::move({10,-10});

    //Pour avoir le grapin à nouveau à la même position que la bacterie
    twitching->moveGrip(twitching->getPosition()-twitching->grapin.getPosition());

    return twitching;
}

void TwitchingBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);
    const auto line = buildLine(position, grapin.getPosition(), couleur.get(), 1);
    target.draw(line);
    const auto circle = buildCircle(grapin.getPosition(), grapin.getRadius(), couleur.get());
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
    grapin.move(delta);
}

void TwitchingBacterium::move(sf::Time dt)
{
    Nutriment* nutriment_ptr = getAppEnv().getNutrimentColliding(grapin);

    switch(etat)
    {
        case IDLE : etat = WAIT_TO_DEPLOY; break;
        case WAIT_TO_DEPLOY : Wait_to_deploy_state(); break;
        case DEPLOY : deploy_state(dt, nutriment_ptr); break;
        case ATTRACT : attract_state(dt, nutriment_ptr); break;
        case RETRACT : retract_state (dt); break;
        case EAT : eat_state(nutriment_ptr); break;
    }
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

    etat = DEPLOY;
}

void TwitchingBacterium::deploy_state(sf::Time dt, Nutriment* nutriment_ptr)
{
    grapinToward(direction, dt);

    if(nutriment_ptr != nullptr)
        etat = ATTRACT;
    else if ( (grapin.getPosition()-position).length() >= getProperty("tentacle length").get() or getAppEnv().doesCollideWithDish(grapin) )
        etat = RETRACT;
}

void TwitchingBacterium::attract_state(sf::Time dt, Nutriment* nutriment_ptr)
{

     const double dist_tentacule = getProperty("tentacle speed").get()*dt.asSeconds();
     const Vec2d deltaPos((grapin.getPosition()-position)*dist_tentacule*getConfig()["speed factor"].toDouble());

     CircularBody::move(deltaPos);
     consumeEnergy(deltaPos.length() * getStepEnergy());

     if (nutriment_ptr == nullptr)
         etat = RETRACT;

     else if (*nutriment_ptr & *this)
         etat = EAT;
}

void TwitchingBacterium::tentacle_init()
{
    moveGrip(position - grapin.getPosition());
    etat = IDLE;
}

void TwitchingBacterium::retract_state(sf::Time dt)
{
    (*this > grapin) ? tentacle_init() : grapinToward((position-grapin.getPosition()).normalised(), dt);
}

void TwitchingBacterium::grapinToward (Vec2d dir, sf::Time dt)
{
    direction = dir;
    const double dist_tentacule = getProperty("tentacle speed").get()*dt.asSeconds();
    moveGrip(dir*dist_tentacule);
    consumeEnergy(getTentacleEnergy()*dist_tentacule);
}

void TwitchingBacterium::eat_state(Nutriment *nutriment_ptr)
{
    if (nutriment_ptr == nullptr)
        etat = IDLE;
    else if (!(*nutriment_ptr & *this))
        etat = IDLE;
}





