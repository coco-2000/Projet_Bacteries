#pragma once

#include"../Utility/Vec2d.hpp"
#include <iostream>


class CircularBody
{
public :

    CircularBody(Vec2d position, double radius);
    CircularBody(const CircularBody& other);

    const Vec2d& getPosition()  const;
    double getRadius()          const;

    void setPosition    (const Vec2d& pos);
    void setRadius      (double rayon);
    void move           (const Vec2d& vector);

    bool contains       (const CircularBody& other) const;
    bool isColliding    (const CircularBody& other) const;
    bool contains       (const Vec2d& point)         const;

    CircularBody& operator=(CircularBody const& other);

    bool operator>      (CircularBody const& other) const;
    bool operator&      (CircularBody const& other) const;
    bool operator>      (Vec2d const& point)        const;

   std::ostream& affiche(std::ostream& out)        const;


private :

    Vec2d position;
    double radius;

    void copie           (const CircularBody& body);
};

std::ostream& operator<<(std::ostream& out, CircularBody const& body);
