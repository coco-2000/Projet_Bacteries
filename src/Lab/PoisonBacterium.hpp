#pragma once

#include "SwimmingBacterium.hpp"
#include "Bacterium.hpp"

class PoisonBacterium : public SwimmingBacterium
{
public:
    /**
     * @brief PoisonBacterium Constructeur
     * Incrémente le compteur d'instances
     * @param position Coordonnées de la position de l'instance à créer
     */
    PoisonBacterium(const Vec2d& position);

    /**
     * @brief PoisonBacterium Constructeur de copie
     * Incrémente le compteur d'instances
     * @param other Instance de bactérie à copier
     */
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

    /**
     * @brief eatableQuantity Calcule l'énergie oté à la bactérie par le poison et consomme le poison
     * (appelle la méthode eatenBy de poison qui prend pour argument une bactérie à poison)
     *  @param poison qui est consommé par la bactérie
     * @return L'énergie otée à la bactérie
     */
    Quantity eatableQuantity(Poison& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment de type A pour une bactérie à poison
     * (appelle la méthode getScoreCoefficient du nutrimentA qui prend pour argument une bactérie à poison)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const NutrimentA& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment de type B pour une bactérie à poison
     * (appelle la méthode getScoreCoefficient du nutrimentB qui prend pour argument une bactérie à poison)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const NutrimentB& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du poison pour une bactérie à poison
     * @param poison qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const Poison& poison) const override;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries à poison
     * @return La valeur associée à getAppConfig()["poison bacterium"]
     */
    j::Value const& getConfig() const override;

    /**
     * @brief clone Effectue la copie d'une instance avec tous ses attributs
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */
    PoisonBacterium* clone() const override;

    /**
     * @brief getPoisonCounter compte le nombre total d'instances de PoisonBacterium présentes dans l'assiette de Pétri
     * @return le nombre total d'instances
     */
    static unsigned int getPoisonCounter();

    /**
     * @brief move Déplace la bactérie et dépose le poison
     * @param dt Pas de temps depuis le dernier déplacement de l'instance courante
     */
    void move(sf::Time dt) override;

    /**
     * @brief ~PoisonBacterium Destructeur
     * Décrémente le compteur d'instances
     */
    ~PoisonBacterium() override;

private :
    static unsigned int poisonCounter;
    sf::Time delayPoison;

    /**
     * @brief dropPoison Ajoute un poison à l'ensemble de nutriment de l'assiette de Petri
     */
    void dropPoison() const;
};
