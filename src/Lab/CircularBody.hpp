#pragma once

#include"../Utility/Vec2d.hpp"
#include <iostream>


class CircularBody
{
public :

    /**
     * @brief getPosition Accesseur de position
     * @return Position actuelle de l'instance courante
     */
    const Vec2d& getPosition() const;

    /**
     * @brief getRadius Accesseur de rayon
     * @return Rayon actuel de l'instance courante
     */
    double getRadius() const;

    /**
     * @brief move Ajoute à la position de l'instance courante un vecteur de déplacement (permet de faire bouger le CircularBody)
     * @param vector Coordonnées du vecteur de déplacement
     */
    void move(const Vec2d& vector);

    /**
     * @brief shift Donne position d'un objet qui doit se touver à côté de l'instance courante
     * @param vector Vecteur de décalage
     * @return Les coordonnées décalées par rapport à la position de l'instance courante
     */
    Vec2d shift(const Vec2d& vector) const;

    /**
     * @brief contains Vérifie les inclusions
     * @param other CircularBody pour lequel on vérifie s'il est contenu dans l'instance courante
     * @return vrai si other est contenu dans l'instance courante
     */
    bool contains(const CircularBody& other) const;

    /**
     * @brief contains Vérifie l'inclusion d'un point
     * @param point Coordonnées du point pour lequel on vérifie l'inclusion
     * @return vrai s'il est contenu
     */
    bool contains(const Vec2d& point) const;

    /**
     * @brief operator= Copie les valeurs des attributs de other dans l'instance courante
     * @param other CircularBody à copier
     * @return L'instance courante après sa copie
     */
    const CircularBody& operator=(CircularBody const& other);

    /**
     * @brief display Affiche la position et le rayon du CircularBody
     * @param out Flux de sortie
     * @return le flux passé en paramètre
     */
    std::ostream& display(std::ostream& out) const;

    /**
     * @brief isColliding Vérifie les collisions
     * @param other CircularBody pour lequel on vérifie s'il entre en collision avec l'instance courante
     * @return vrai s'ils sont en collision
     */
    bool isColliding(const CircularBody& other) const;

protected :
    /**
     * @brief CircularBody Constructeur
     * @param position Coordonnées de la position du CircularBody
     * @param radius Rayon du CircularBody
     */
    CircularBody(Vec2d const& position, double radius);
    /**
     * @brief CircularBody Constructeur de copie
     * @param other CircularBody à copier
     */
    CircularBody(const CircularBody& other);

    /**
     * @brief setPosition Manipulateur de position
     * @param pos Coordonnées de la nouvelle position à assigner à l'instance courante
     */
    void setPosition (const Vec2d& pos);

    /**
     * @brief setRadius Manipulateur de rayon
     * @param rayon Valeur du nouveau rayon à assigner à l'instance courante
     */
    void setRadius (double rayon);

private :
    Vec2d position;
    double radius;

    /**
     * @brief copie Effectue la copie des attributs d'un autre corps dans l'instance courante
     * @param body Instance à copier
     */
    void copy(const CircularBody& body);
};

/**
 * @brief operator << Affiche la position et le rayon du CircularBody
 * @param out Flux de sortie
 * @param body CircularBody dont on affiche les attributs
 * @return Le flux de sortie
 */
std::ostream& operator<<(std::ostream& out, CircularBody const& body);

/**
 * @brief operator> Vérifie les inclusions
 * @param body1 CircularBody dont on verifie s'il contient body2
 * @param body2 CircularBody dont on verifie s'il est contenu dans body1
 * @return vrai si body2 est contenu dans body1
 */
bool operator>(CircularBody const& body1, CircularBody const& body2);

/**
 * @brief operator& Vérifie les collisions
 * @param body1 et body2 CircularBody dont on verifie s'ils sont en collision l'un avec l'autre
 * @return vrai s'ils sont en collision
 */
bool operator&(CircularBody const& body1, CircularBody const& body2);

/**
 * @brief operator> Vérifie l'inclusion d'un point
 * @param body CircularBody dont on verifie s'il contient le point
 * @param point Coordonnées du point dont on vérifie s'il est contenu dans body
 * @return vrai si le point est contenu dans body
 */
bool operator>(CircularBody const& body, Vec2d const& point);







