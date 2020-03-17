#pragma once
#include "CircularBody.hpp"
#include "Utility/Types.hpp"
#include <SFML/Graphics.hpp>


class Nutriment : public CircularBody
{
public :
    /**
     * @brief Nutriment::Nutriment Constructeur
     * @param quantity Quantité intiale de l'instance courante
     * @param position Coordonnées de la position intiale de l'instance courante
     */
    Nutriment(Quantity quantity, const Vec2d& position);

    /**
     * @brief Nutriment::takeQuantity Prélève une quantité donnée de nutriments de l'instance courante
     * @param prelevement Quantité de nutriments à prélever
     * @return Quantité de nutriments qui a pu être prélevée
     */
    Quantity takeQuantity(Quantity prelevement);

    /**
     * @brief Nutriment::setQuantity Manipulateur de quantité, actualise égalment le rayon du nutriment
     * @param quantity Nouvelle quantité à assigner à quantité (+ rayon)
     */
    void setQuantity(Quantity quantity);

    /**
     * @brief drawOn Dessine un nutriment
     * @param target
     */
    void drawOn(sf::RenderTarget& target) const;

    /**
     * @brief getConfig Simplfifie l'accès aux paramètres
     * @return Paramètre de simulation souhaité
     */
    j::Value const& getConfig() const;


private :
    Quantity quantity_;

    void DisplayQuantity(sf::RenderTarget& target) const;
};
