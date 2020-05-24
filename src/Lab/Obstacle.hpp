#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"


class Obstacle : public CircularBody, public Drawable
{
public :
    /**
     * @brief Obstacle Constructeur
     * @param position Coordonnées de la position de l'obstacle à créer
     */
    Obstacle( Vec2d const& position);

    /**
     * @brief drawOn Dessine l'obstacle
     * @param target Fenetre dans laquelle on affiche l'obstacle
     */
    void drawOn(sf::RenderTarget& target) const override;
};

