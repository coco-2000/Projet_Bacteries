#pragma once
#include "Nutriment.hpp"

class NutrimentA: public Nutriment
{
public :

    /**
     * @brief NutrimentA constructeur, le construit comme un Nutriment
     * @param quantity Quantité intiale de l'instance courante
     * @param position Coordonnées de la position intiale de l'instance courante
     */
    NutrimentA(Quantity quantity, const Vec2d& position);

    Quantity eatenBy(Bacterium& bacterie) override;
    Quantity eatenBy(SimpleBacterium& bacterie) override;
    Quantity eatenBy(SwarmBacterium& bacterie) override;
    Quantity eatenBy(TwitchingBacterium& bacterie) override;

protected:
    /**
     * @brief getConfig redéfinition de la méthode virtuelle héritée de Nutriment
     * Raccourci pour accéder aux paramètres relatifs aux nutriments A
     * @return la valeur de getAppConfig()["nutriments"]["A"]
     */
    j::Value const& getConfig() const override;
};
