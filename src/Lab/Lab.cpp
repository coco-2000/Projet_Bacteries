#include "Lab.hpp"
#include "CircularBody.hpp"
#include "Application.hpp"


bool Lab::contains(const CircularBody& corps) const
{
    return (petri > corps);
}

Lab::Lab()
    : petri(getApp().getCentre(), ratio_rayon*getApp().getLabSize().x )
{}

void Lab::update(sf::Time dt)
{
    petri.update(dt);
}

void Lab::drawOn(sf::RenderTarget& targetWindow) const
{
    petri.drawOn(targetWindow);
}

void Lab::reset()
{
    petri.reset();
}

void Lab::addNutriment(Nutriment* nutriment)
{
    petri.addNutriment(nutriment);
}
