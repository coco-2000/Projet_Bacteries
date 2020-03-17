#include "CircularBody.hpp"
#include"../Utility/Vec2d.hpp"
#include <iostream>
#include "Utility/Vec2d.hpp"

/**
 * @brief CircularBody::CircularBody Constructeur
 * @param position Coordonnées de la position du CircularBody
 * @param radius Rayon du CircularBody
 */
CircularBody::CircularBody(Vec2d position, double radius)
    : position(position), radius(radius) {}

/**
 * @brief CircularBody::CircularBody Constructeur de copie
 * @param other CircularBody à copier
 */
CircularBody::CircularBody(const CircularBody& other)
{
    copie(other);
}

/**
 * @brief CircularBody::getPosition Accesseur de position
 * @return Position actuelle de l'instance courante
 */
const Vec2d& CircularBody::getPosition() const
{
    return position;
}

/**
 * @brief CircularBody::getRadius Accesseur de rayon
 * @return Rayon actuel de l'instance courante
 */
double CircularBody::getRadius() const
{
    return radius;
}

/**
 * @brief CircularBody::setPosition Manipulateur de position
 * @param pos Coordonnées de la nouvelle position à assigner à l'instance courante
 */
void CircularBody::setPosition(const Vec2d& pos)
{
    position = pos;
}

/**
 * @brief CircularBody::setRadius Manipulateur de rayon
 * @param rayon Valeur du nouveau rayon à assigner à l'instance courante
 */
void CircularBody::setRadius(double rayon)
{
    radius = rayon;
}

/**
 * @brief CircularBody::operator = Copie les valeurs des attributs de other dans l'instance courante
 * @param other CircularBody à copier
 * @return L'instance courante après sa copie
 */
CircularBody& CircularBody::operator=(CircularBody const& other)
{
    copie(other);
    return (*this);
}

/**
 * @brief CircularBody::move Ajoute à la position de l'instance courante un vecteur de déplacement (permet de faire bouger le CircularBody)
 * @param vector Coordonnées du vecteur de déplacement
 */
void CircularBody::move(const Vec2d& vector)
{
    position += vector;
}

/**
 * @brief CircularBody::contains verifier les inclusions
 * @param other est celui pour lequel on verifie s'il est contenu dans l'instance courante
 * @return vrai s'il est contenu
 */

bool CircularBody::contains(const CircularBody& other) const
{
    return ((radius >= other.radius) and (distance(position, other.position) <= radius - other.radius));
}

/**
 * @brief CircularBody::isColliding vérifier les collisions
 * @param other est celui pour lequel on vérifie s'il entre en collision avec l'instance courante
 * @return vrai s'ils sont en collision
 */
bool CircularBody::isColliding(const CircularBody& other) const
{
    return (distance(position, other.position) <= radius + other.radius);
}

/**
 * @brief CircularBody::contains verifier l'inclusion d'un point
 * @param point : celui pour lequel on vérifie l'inclusion
 * @return vrai s'il est contenu
 */
bool CircularBody::contains(const Vec2d& point) const
{
    return (distance(position, point) <= radius);
}

/**
 * @brief CircularBody::operator > verifier les inclusions
 * @param other est celui pour lequel on verifie s'il est contenu dans l'instance courante
 * @return vrai s'il est contenu
 */
bool CircularBody::operator>(CircularBody const& other) const
{
    return contains(other);
}

/**
 * @brief CircularBody::operator & vérifier les collisions
 * @param other est celui pour lequel on vérifie s'il entre en collision avec l'instance courante
 * @return vrai s'ils sont en collision
 */
bool CircularBody::operator&(CircularBody const& other) const
{
    return isColliding(other);
}

/**
 * @brief CircularBody::operator > verifier l'inclusion d'un point
 * @param point : celui pour lequel on vérifie l'inclusion
 * @return vrai s'il est contenu
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
 * @brief CircularBody::affiche affiche la position et le rayon du CircularBody
 * @param out : flux de sortie
 * @return le flux passé en paramètre
 */
std::ostream& CircularBody::affiche(std::ostream& out) const
{
    out << "CircularBody: position = " << position
        << " ,radius = " << radius;

    return out;
}

/**
 * @brief operator << affiche la position et le rayon du CircularBody
 * @param out
 * @param body
 * @return
 */
std::ostream& operator<<(std::ostream& out, CircularBody const& body)
{
    return body.affiche(out);
}

const Vec2d& CircularBody::decalage(const Vec2d& vector) const
{
    return vector + position;
}

