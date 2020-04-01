#pragma once
#include "Bacterium.hpp"
#include "../Utility/DiffEqSolver.hpp"

class SimpleBacterium : public Bacterium
{
public:
    SimpleBacterium(const Vec2d& position);

    SimpleBacterium(Quantity energie, Vec2d position, Vec2d direction,
                    double radius, const MutableColor& couleur,
                    std::map<std::string, MutableNumber> param_mutables,
                    bool abstinence, MRU equation);

    //SimpleBacterium(const SimpleBacterium& autre);

    j::Value const& getConfig() const;

    void move(sf::Time dt);

    Vec2d getSpeedVector() const;

    SimpleBacterium* clone() const;

    SimpleBacterium* copie() const;





private :
    MRU equation;
    double t;
    double proba_basculement;


    void graphisme_particulier(sf::RenderTarget& target) const;

    void tentative_basculement();
    void basculement();

    void strategie1();
    void strategie2();
};
