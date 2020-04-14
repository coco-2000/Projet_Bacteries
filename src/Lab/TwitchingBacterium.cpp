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
    Nutriment* nutriment_ptr = nullptr;

    switch(etat)
    {
        case IDLE : etat = WAIT_TO_DEPLOY; break;
        case WAIT_TO_DEPLOY : preparation_deploiement(); break;
        case DEPLOY : nutriment_ptr = tentacule_deploiement(dt); break;
        case ATTRACT : deplacement(dt, nutriment_ptr); break;
        case RETRACT : break;
        case EAT : break;
    }
}

void TwitchingBacterium::preparation_deploiement()
{
    constexpr int N(20); // nb de directions aléatoires à générer

    for(int i(0); i < N; ++i)
    {
        const Vec2d new_dir (Vec2d::fromRandomAngle());

        if(helperPositionScore (new_dir) > helperPositionScore(direction))
        {
            setDirection(new_dir);
        }
    }

    etat = DEPLOY;
}

Nutriment* TwitchingBacterium::tentacule_deploiement(sf::Time dt)
{
    const double dist_tentacule = getConfig()["tentacle speed"].toDouble()*dt.asSeconds();
    Nutriment* nutriment_ptr(getAppEnv().getNutrimentColliding(grapin));

    moveGrip(direction*dist_tentacule);
    consumeEnergy(getTentacleEnergy()*dist_tentacule);

    if (nutriment_ptr != nullptr)
    {
        etat = ATTRACT;
        return nutriment_ptr;
    }
    else
    {
        etat = RETRACT;
        return nullptr;
    }
}

void TwitchingBacterium::deplacement(sf::Time dt, Nutriment* nutriment_ptr)
{
    if (*nutriment_ptr & *this)
        etat = EAT;
    else
    {
        const double dist_tentacule = getConfig()["tentacle speed"].toDouble()*dt.asSeconds();
        const Vec2d deltaPos((grapin.getPosition()-position)*dist_tentacule*getConfig()["speed factor"].toDouble());

        CircularBody::move(deltaPos);
        consumeEnergy(deltaPos.length() * getStepEnergy());

        if (nutriment_ptr->isEmpty())
        {
            etat = RETRACT;
        }
    }
}

void TwitchingBacterium::tentacleInit()
{
    moveGrip(position - grapin.getPosition());
}








