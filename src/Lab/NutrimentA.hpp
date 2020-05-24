#pragma once
#include "Nutriment.hpp"

class NutrimentA: public Nutriment
{
public :

    /**
     * @brief NutrimentA Constructeur
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
    Quantity eatenBy(const Bacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie simple
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(const SimpleBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à comportement de groupe
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(const SwarmBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à tentacule
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(const TwitchingBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à poison
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return la quantité de nutriment consommée
     */
    Quantity eatenBy(const PoisonBacterium& bacterie) override;

    double getScoreCoefficient(const Bacterium& bacterie) const override;

    double getScoreCoefficient(const SimpleBacterium& bacterie) const override;

    double getScoreCoefficient(const SwarmBacterium& bacterie) const override;

    double getScoreCoefficient(const TwitchingBacterium& bacterie) const override;

    double getScoreCoefficient(const PoisonBacterium& bacterie) const override;

    static unsigned int getnutACounter();

    ~NutrimentA() override;

private :

    static unsigned int nutACounter;

    /**
     * @brief getConfig redéfinition de la méthode virtuelle héritée de Nutriment
     * Raccourci pour accéder aux paramètres relatifs aux nutriments A
     * @return la valeur de getAppConfig()["nutriments"]["A"]
     */
    j::Value const& getConfig() const override;
};
