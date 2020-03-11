#include "CircularBody.hpp"
#include"../Utility/Vec2d.hpp"
#include <iostream>

/**
 * @brief CircularBody::CircularBody
 * @param position
 * @param radius
 */
CircularBody::CircularBody(Vec2d position, double radius)
    : position(position), radius(radius) {}
/**
 * @brief CircularBody::CircularBody
 * @param other
 */
CircularBody::CircularBody(const CircularBody& other)
{
    copie(other);
}
/**
 * @brief CircularBody::getPosition
 * @return position actuelle du corps
 */
const Vec2d& CircularBody::getPosition() const
{
    return position;
}
/**
 * @brief CircularBody::getRadius
 * @return
 */
double CircularBody::getRadius() const
{
    return radius;
}
/**
 * @brief CircularBody::setPosition
 * @param pos
 */
void CircularBody::setPosition(const Vec2d& pos)
{
    position = pos;
}
/**
 * @brief CircularBody::setRadius
 * @param rayon
 */
void CircularBody::setRadius(double rayon)
{
    radius = rayon;
}
/**
 * @brief CircularBody::operator =
 * @param other
 * @return
 */
CircularBody& CircularBody::operator=(CircularBody const& other)
{
    copie(other);
    return (*this);
}
/**
 * @brief CircularBody::move
 * @param vector
 */
void CircularBody::move(const Vec2d& vector)
{
    position += vector;
}
/**
 * @brief CircularBody::contains
 * @param other
 * @return
 */
bool CircularBody::contains(const CircularBody& other) const
{
    return ((radius >= other.radius) and (distance(position, other.position) <= radius - other.radius));
}

/**
 * @brief CircularBody::isColliding
 * @param other
 * @return
 */
bool CircularBody::isColliding(const CircularBody& other) const
{
    return (distance(position, other.position) <= radius + other.radius);
}

/**
 * @brief CircularBody::contains
 * @param point
 * @return
 */
bool CircularBody::contains(const Vec2d point) const
{
    return (distance(position, point) <= radius);
}

/**
 * @brief CircularBody::operator >
 * @param other
 * @return
 */
bool CircularBody::operator>(CircularBody const& other) const
{
    return contains(other);
}

/**
 * @brief CircularBody::operator &
 * @param other
 * @return
 */
bool CircularBody::operator&(CircularBody const& other) const
{
    return isColliding(other);
}

/**
 * @brief CircularBody::operator >
 * @param point
 * @return
 */
bool CircularBody::operator>(Vec2d const& point) const
{
    return contains(point);
}

/**
 * @brief CircularBody::copie
 * @param body
 */
void CircularBody::copie(const CircularBody& body)
{
    position = body.position;
    radius = body.radius;
}

/**
 * @brief CircularBody::affiche
 * @param out
 * @return
 */
std::ostream& CircularBody::affiche(std::ostream& out) const
{
    out << "CircularBody: position = " << position
        << " ,radius = " << radius;

    return out;
}

/**
 * @brief operator <<
 * @param out
 * @param body
 * @return
 */
std::ostream& operator<<(std::ostream& out, CircularBody const& body)
{
    return body.affiche(out);
}
