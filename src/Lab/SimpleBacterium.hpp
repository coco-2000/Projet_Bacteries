#pragma once
#include "SwimmingBacterium.hpp"

class SimpleBacterium : public SwimmingBacterium
{
public:
    /**
     * @brief SimpleBacterium Constructeur
     * Incrémente le compteur d'instances
     * @param position Coordonnées de la position de l'instance à créer
     */
    SimpleBacterium(const Vec2d& position);

    /**
     * @brief SimpleBacterium Constructeur de copie
     * Incrémente le compteur d'instances
     * @param other Instance de bactérie à copier
     */
    SimpleBacterium(const SimpleBacterium& other);

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie simple)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentA& nutriment) const override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie simple)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentB& nutriment) const override;

    /**
     * @brief eatableQuantity Calcule l'énergie oté à la bactérie par le poison et consomme le poison
     * (appelle la méthode eatenBy de poison qui prend pour argument une bactérie simple)
     *  @param poison qui est consommé par la bactérie
     * @return L'énergie otée à la bactérie
     */
    Quantity eatableQuantity(Poison& poison) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment de type A pour une bactérie simple
     * (appelle la méthode getScoreCoefficient du nutrimentA qui prend pour argument une bactérie simple)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const NutrimentA& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment de type B pour une bactérie simple
     * (appelle la méthode getScoreCoefficient du nutrimentB qui prend pour argument une bactérie simple)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const NutrimentB& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du poison pour une bactérie simple
     * @param poison qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const Poison& poison) const override;

    /**
     * @brief clone Effectue la copie d'une instance avec tous ses attributs
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */
    SimpleBacterium* clone() const override;

    /**
     * @brief ~SimpleBacterium Destructeur
     * Décrémente le compteur d'instances
     */
    ~SimpleBacterium() override;

    /**
     * @brief getSimpleCounter
     * @return Le nombre d'instance de SimpleBacterium présente dans l'assiette de Pétri
     */
    static unsigned int getSimpleCounter();

private :
    static unsigned int simpleCounter;

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries simples
     * @return La valeur associée à getAppConfig()["simple bacterium"]
     */
    j::Value const& getConfig() const override;
};
