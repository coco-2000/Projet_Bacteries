#include "CircularBody.hpp"
#include"../Utility/Vec2d.hpp"
#include <iostream>
#include "Utility/Vec2d.hpp"


CircularBody::CircularBody(Vec2d position, double radius)
    : position(position), radius(radius) {}

CircularBody::CircularBody(const CircularBody& other)
{
    copie(other);
}

const Vec2d& CircularBody::getPosition() const
{
    return position;
}

double CircularBody::getRadius() const
{
    return radius;
}

void CircularBody::setPosition(const Vec2d& pos)
{
    position = pos;
}

void CircularBody::setRadius(double rayon)
{
    radius = rayon;
}

CircularBody& CircularBody::operator=(CircularBody const& other)
{
    copie(other);
    return (*this);
}

void CircularBody::move(const Vec2d& vector)
{
    position += vector;
}

bool CircularBody::contains(const CircularBody& other) const
{
    return ((radius >= other.radius) and (distance(position, other.position) <= radius - other.radius));
}

bool CircularBody::isColliding(const CircularBody& other) const
{
    return (distance(position, other.position) <= radius + other.radius);
}

bool CircularBody::contains(const Vec2d& point) const
{
    return (distance(position, point) <= radius);
}

bool CircularBody::operator>(CircularBody const& other) const
{
    return contains(other);
}

bool CircularBody::operator&(CircularBody const& other) const
{
    return isColliding(other);
}

bool CircularBody::operator>(Vec2d const& point) const
{
    return contains(point);
}

void CircularBody::copie(const CircularBody& body)
{
    position = body.position;
    radius = body.radius;
}


std::ostream& CircularBody::affiche(std::ostream& out) const
{
    out << "CircularBody: position = " << position
        << " ,radius = " << radius;

    return out;
}

std::ostream& operator<<(std::ostream& out, CircularBody const& body)
{
    return body.affiche(out);
}

Vec2d CircularBody::decalage(const Vec2d& vector) const
{
    return vector + position;
}

