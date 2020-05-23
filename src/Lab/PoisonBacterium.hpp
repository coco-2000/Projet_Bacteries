#pragma once

#include "SimpleBacterium.hpp"
#include "Bacterium.hpp"

class PoisonBacterium : public SimpleBacterium
{
public:
    /**
     * @brief PoisonBacterium Constructeur
     * @param position Coordonnées de la position de l'instance à créer
     */
    PoisonBacterium(const Vec2d& position);

    PoisonBacterium(const PoisonBacterium& other);

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie à poison)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentA& nutriment) const override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie à poison)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentB& nutriment) const override;

    Quantity eatableQuantity(Poison& nutriment) const override;

    double getScoreCoefficient(const NutrimentA& nutriment) const override;

    double getScoreCoefficient(const NutrimentB& nutriment) const override;

    double getScoreCoefficient(const Poison& poison) const override;

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries à poison
     * @return La valeur associée à getAppConfig()["poison bacterium"]
     */
    j::Value const& getConfig() const override;

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief clone Effectue la copie d'une instance avec tous ses attributs
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */
    PoisonBacterium* clone() const override;

    static double getPoisonCounter();

    void move(sf::Time dt) override;

    ~PoisonBacterium() override;

private :
    static double poisonCounter;
    sf::Time delayPoison;

    void dropPoison() const;

    void resetDelay();
};
