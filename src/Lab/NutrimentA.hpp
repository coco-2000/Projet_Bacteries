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

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie
     * (appelle la méthode eatableQuantity de la sous classe à laquelle appartient la bactérie = polymorphisme)
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(Bacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie simple
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(SimpleBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à comportement de groupe
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(SwarmBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à tentacule
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(TwitchingBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à poison
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(PoisonBacterium& bacterie) override;

    double getPositionScore(const Bacterium& bacterie) const override;

    double getPositionScore(const SimpleBacterium& bacterie) const override;

    double getPositionScore(const SwarmBacterium& bacterie) const override;

    double getPositionScore(const TwitchingBacterium& bacterie) const override;

    double getPositionScore(const PoisonBacterium& bacterie) const override;

    private :
    /**
     * @brief getConfig redéfinition de la méthode virtuelle héritée de Nutriment
     * Raccourci pour accéder aux paramètres relatifs aux nutriments A
     * @return la valeur de getAppConfig()["nutriments"]["A"]
     */
    j::Value const& getConfig() const override;
};
