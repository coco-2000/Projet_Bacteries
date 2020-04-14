#pragma once

#include "Bacterium.hpp"
#include "Grip.hpp"
#include "Nutriment.hpp"

enum Etat {IDLE, WAIT_TO_DEPLOY, DEPLOY, ATTRACT, RETRACT, EAT};

class TwitchingBacterium : public Bacterium
{
public :
    TwitchingBacterium(const Vec2d& position);
    void drawOn(sf::RenderTarget& target) const override;
    void moveGrip(const Vec2d& position);

protected :
    Grip grapin;
    Etat etat;

    j::Value const& getConfig() const override;
    void move(sf::Time dt) override;
    Bacterium* clone() const override;
    Quantity getStepEnergy() const override;
    Quantity getTentacleEnergy() const;
    void tentacleInit();
    void preparation_deploiement();
    Nutriment* tentacule_deploiement(sf::Time dt);
    void deplacement(sf::Time dt, Nutriment* nutriment_ptr);

};
