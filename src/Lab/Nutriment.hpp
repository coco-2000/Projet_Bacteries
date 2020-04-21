#pragma once
#include "CircularBody.hpp"
#include "Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"

class Nutriment : public CircularBody, public Drawable, public Updatable
{
public :
    /**
     * @brief Nutriment::Nutriment Constructeur
     * @param quantity Quantité intiale de l'instance courante
     * @param position Coordonnées de la position intiale de l'instance courante
     */
    Nutriment(Quantity quantity, const Vec2d& position);

    /**
     * @brief Nutriment::setQuantity Manipulateur de quantité, actualise égalment le rayon du nutriment
     * @param quantity Nouvelle quantité à assigner à quantité (+ rayon)
     */
    void setQuantity(Quantity quantity);

    /**
     * @brief drawOn Dessine un nutriment
     * @param target
     */
    void drawOn(sf::RenderTarget& target) const override;

   /**
    * @brief update Effectue la croissance d'un nutriment en mettant à jour sa quantité et son rayon
    * @param dt Pas de temps après lequel lequel le nutriment est mise à jour
    */
    void update(sf::Time dt) override;

   /**
    * @brief getTemperature Accesseur de température
    * @return la température courante de l'assiette de Petri
    */
    double getTemperature() const;

    /**
     * @brief ConditionTemperature Vérifie les conditions portant sur la température pour la croissance des nutriments
     * @param temperature Température courante
     * @return true si les conditions sont respectées false sinon
     */
    bool ConditionTemperature(double temperature) const;

    /**
     * @brief isEmpty permet de savoir s'il n'y a plus de nutriment dans la souche
     * @return vrai s'il n'y a plus de nutriment
     */
    bool isEmpty() const;

    /**
     * @brief Nutriment::takeQuantity Prélève une quantité donnée de nutriments de l'instance courante
     * @param prelevement Quantité de nutriments à prélever
     * @return Quantité de nutriments qui a pu être prélevée
     */
    Quantity takeQuantity(Quantity prelevement);

protected :
    const double dist;
    Quantity quantity_;

    /**
     * @brief DisplayQuantity Affiche de la quantité du nutriment (si mode debugging activé)
     * @param target Cible pour l'affichage
     */
    void DisplayQuantity(sf::RenderTarget& target) const;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux nutriments
     * Il s'agit d'une méthode virtuelle pure
     */
     virtual j::Value const& getConfig() const = 0;

    /**
     * @brief Nutriment::TestPrelevement Ajuste la quantité prélever en fonction de celle disponible
     * @param prelevement Quantité voulant être prélever
     */
    void TestPrelevement(Quantity& prelevement) const;
};
