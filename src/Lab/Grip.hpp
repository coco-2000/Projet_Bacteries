#pragma once
#include "CircularBody.hpp"

class Grip : public CircularBody {
public:
    /**
     * @brief Grip Constructeur
     * @param position Coordonnées de la position du CircularBody
     * @param radius Rayon du CircularBody
     */
    Grip(const Vec2d& position, double radius);
};

