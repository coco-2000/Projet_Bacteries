#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"


class Obstacle : public CircularBody, public Drawable
{
public :
    /**
     * @brief Obstacle constructeur
     * @param position coordonnées de la position du nouvel obstacle
     */
    Obstacle( Vec2d const& position);

    /**
     * @brief drawOn dessiner l'obstacle
     * @param target la fenetre dans laquelle on affiche l'obstacle
     */
    void drawOn(sf::RenderTarget& target) const override;
};

