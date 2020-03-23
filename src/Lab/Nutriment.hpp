#pragma once
#include "CircularBody.hpp"
#include "Utility/Types.hpp"
#include <SFML/Graphics.hpp>

constexpr unsigned int TAILLE_OBJ_GRAPHIQUE(6);
constexpr unsigned int TAILLE_FONTE(15);

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
     * @brief Nutriment::TestPrelevement Ajuste la quantité prélever en fonction de celle disponible
     * @param prelevement Quantité voulant être prélever
     */
    void TestPrelevement(Quantity& prelevement);

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
    * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux nutriments
    * @return la valeur de getAppConfig()["nutriments"]
    */
   j::Value const& getConfig() const;

   /**
    * @brief update Effectue la croissance d'un nutriment en mettant à jour sa quantité et son rayon
    * @param dt Pas de temps après lequel lequel le nutriment est mise à jour
    */
   void update(sf::Time dt);

   /**
    * @brief getTemperature Accesseur de température
    * @return la température courante de l'assiette de Petri
    */
   double getTemperature() const;

private :
    const double dist;
    Quantity quantity_;
    void DisplayQuantity(sf::RenderTarget& target) const;
};
