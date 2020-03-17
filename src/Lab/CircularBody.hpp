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
    const Vec2d& decalage(const Vec2d& vector) const;

    bool contains       (const CircularBody& other) const;
    bool isColliding    (const CircularBody& other) const;
    bool contains       (const Vec2d& point)         const;

    CircularBody& operator=(CircularBody const& other);

    std::ostream& affiche(std::ostream& out)        const;


protected :

    Vec2d position;
    double radius;

    void copie           (const CircularBody& body);
};

std::ostream& operator<<(std::ostream& out, CircularBody const& body);

/**
 * @brief operator > verifier les inclusions
 * @param body1 on verifie s'il contient body2
 * @param body2 on verifie s'il est contenu dans body1
 * @return vrai si body2 est contenu dans body1
 */
bool operator>(CircularBody const& body1, CircularBody const& body2);

/**
 * @brief operator & verifier les collisions
 * @param body1 on verifie s'il est en collision avec body2
 * @param body2
 * @return vrai s'ils sont en collision
 */
bool operator&(CircularBody const& body1, CircularBody const& body2);

/**
 * @brief operator > verifier l'inclusion d'un point
 * @param body on verifie s'il contient le point
 * @param point onverfifie s'il contient le body
 * @return vrai si le point est contenu dans le body
 */
bool operator>(CircularBody  const& body, Vec2d const& point);







