#include "NutrimentGenerator.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include <cmath>

void NutrimentGenerator::update(sf::Time dt)
{
    sf::Time delta = sf::seconds(getAppConfig()["generator"]["nutriment"]["delay"].toDouble()) ;
    if(compteur >= delta )
    {
        reset();

        Vec2d position(normal(getApp().getLabSize().x/2, pow(getApp().getLabSize().x/4,2)),
                       normal(getApp().getLabSize().y/2, pow(getApp().getLabSize().y/4,2)));

        if (bernoulli(getAppConfig()["generator"]["nutriment"]["prob"].toDouble()))
        {
            getAppEnv().addNutriment(new NutrimentA(uniform(getShortConfig().nutrimentA_min_qty, getShortConfig().nutrimentA_max_qty),
                                     position));
        }
        else
        {
            getAppEnv().addNutriment(new NutrimentB(uniform(getShortConfig().nutrimentB_min_qty, getShortConfig().nutrimentB_max_qty),
                                     position));
        }
    }
    else
    {
         compteur + dt;
    }
}

void NutrimentGenerator::reset()
{
    compteur = sf::Time::Zero;
}
