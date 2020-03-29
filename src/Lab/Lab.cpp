#include "Lab.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"

Lab::Lab()
    : petri(getApp().getCentre(), ratio_rayon*getApp().getLabSize().x )
{}

bool Lab::contains(const CircularBody& corps) const
{
    return (petri > corps);
}

bool Lab::doesCollideWithDish(CircularBody const& body) const
{
    return (body & petri);
}

Nutriment* Lab::getNutrimentColliding(CircularBody const& body) const
{
    return petri.getNutrimentColliding(body);
}

void Lab::update(sf::Time dt)
{
    petri.update(dt);
    generateur_nutriment.update(dt);
}

void Lab::drawOn(sf::RenderTarget& targetWindow) const
{
    petri.drawOn(targetWindow);
}

void Lab::reset()
{
    petri.reset();
    generateur_nutriment.reset();
}

void Lab::addNutriment(Nutriment* nutriment)
{
    petri.addNutriment(nutriment);
}

void Lab::addBacterium(Bacterium* bacterie)
{
    petri.addBacterium(bacterie);
}

void Lab::increaseTemperature()
{
    petri.increaseTemperature();
}

void Lab::decreaseTemperature()
{
    petri.decreaseTemperature();
}

double Lab::getTemperature() const
{
    return petri.getTemperature();
}

void Lab::init_temperature()
{
    petri.init_temperature();
}

Lab::~Lab()
{
    reset();
}



