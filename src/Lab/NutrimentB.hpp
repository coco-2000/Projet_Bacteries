#pragma once
#include "Nutriment.hpp"

class NutrimentB: public Nutriment
{
public :

    /**
     * @brief NutrimentB constructeur, le construit comme un Nutriment
     * @param quantity Quantité intiale de l'instance courante
     * @param position Coordonnées de la position intiale de l'instance courante
     */
    NutrimentB(Quantity quantity, const Vec2d& position);

protected:

    /**
     * @brief getConfig redéfinition de la méthode virtuelle héritée de Nutriment
     * Raccourci pour accéder aux paramètres relatifs aux nutriments B
     * @return la valeur de getAppConfig()["nutriments"]["B"]
     */
    j::Value const& getConfig() const override;
};
