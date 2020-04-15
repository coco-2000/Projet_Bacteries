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
    void tentacle_init();
    void Wait_to_deploy_state();
    void deploy_state(sf::Time dt, Nutriment* nutriment_ptr);
    void attract_state(sf::Time dt, Nutriment* nutriment_ptr);
    void retract_state(sf::Time dt);
    void eat_state(Nutriment* nutriment_ptr);
    void grapinToward (Vec2d dir, sf::Time dt);

};
