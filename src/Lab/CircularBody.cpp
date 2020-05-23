#include "CircularBody.hpp"
#include"../Utility/Vec2d.hpp"
#include <iostream>
#include "Utility/Vec2d.hpp"


CircularBody::CircularBody( Vec2d const& position, double radius)
    : position(position), radius(radius)
{

}

CircularBody::CircularBody(const CircularBody& other)
{
    copy(other);
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

void CircularBody::setRadius(double rad)
{
    radius = rad;
}

CircularBody& CircularBody::operator=(CircularBody const& other)
{
    copy(other);
    return (*this);
}

void CircularBody::move(const Vec2d& vector)
{
    position += vector;
}

bool CircularBody::contains(const CircularBody& other) const
{
    return ((radius >= other.radius)
            and (distance(position, other.position)
                 <= radius - other.radius));
}

bool CircularBody::isColliding(const CircularBody& other) const
{
    return (distance(position, other.position) <= radius + other.radius);
}

bool CircularBody::contains(const Vec2d& point) const
{
    return (distance(position, point) <= radius);
}

void CircularBody::copy(const CircularBody& body)
{
    position = body.position;
    radius = body.radius;
}


std::ostream& CircularBody::display(std::ostream& out) const
{
    out << "CircularBody: position = " << position
        << " ,radius = " << radius;

    return out;
}

std::ostream& operator<<(std::ostream& out, CircularBody const& body)
{
    return body.display(out);
}

Vec2d CircularBody::shift(const Vec2d& vector) const
{
    return vector + position;
}

bool operator>(CircularBody const& body1, CircularBody const& body2)
{
    return body1.contains(body2);
}

bool operator&(CircularBody const& body1, CircularBody const& body2)
{
    return body1.isColliding(body2);
}

bool operator>(CircularBody  const& body, Vec2d const& point)
{
    return body.contains(point);
}
