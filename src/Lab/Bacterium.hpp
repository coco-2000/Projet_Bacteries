#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Utility/MutableColor.hpp"
#include <SFML/Graphics.hpp>
#include "Utility/Types.hpp"
#include <string>

class Bacterium : public CircularBody ,public Drawable, public Updatable
{
public :
    Bacterium(Quantity energie, Vec2d position, Vec2d direction,
              double radius, const MutableColor& couleur, bool abstinence = 0,
              std::map<std::string, MutableNumber>param_mutables = {});

    bool en_vie(); //peut etre le remplacer par morte et inverser le bool

    //methode mutate

    virtual j::Value const& getConfig() const = 0;

    Quantity getEnergy() const;
    sf::Time getDelay() const;
    Quantity getEnergyReleased() const;

    void drawOn(sf::RenderTarget& target) const override;

    void update(sf::Time dt) override;

    void consumeEnergy(Quantity qt);

protected :
    MutableColor couleur;
    Vec2d direction;
    Quantity energie;
    bool abstinence;
    std::map<std::string, MutableNumber> param_mutables;
    sf::Time compteur;

    void DisplayEnergy(sf::RenderTarget& target) const;
    void collisionPetri();
    void consumeNutriment(sf::Time dt);

    virtual void move(sf::Time dt) = 0;
    virtual Bacterium* clone() const; // ecrire final ?

};
