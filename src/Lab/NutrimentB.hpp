#pragma once
#include "Nutriment.hpp"

class NutrimentB: public Nutriment
{
public :
    /**
     * @brief NutrimentB Constructeur
     * @param quantity Quantité intiale de l'instance courante
     * @param position Coordonnées de la position intiale de l'instance courante
     */
    NutrimentB(Quantity quantity, const Vec2d& position);

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie
     * (appelle la méthode eatableQuantity de la sous classe à laquelle appartient la bactérie = polymorphisme)
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de nutriment consommée
     */
    Quantity eatenBy(const Bacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie simple
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de nutriment consommée
     */
    Quantity eatenBy(const SimpleBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à comportement de groupe
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de nutriment consommée
     */
    Quantity eatenBy(const SwarmBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à tentacule
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de nutriment consommée
     */
    Quantity eatenBy(const TwitchingBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité cédée par la source de nutriments à la bactérie à poison
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de nutriment consommée
     */
    Quantity eatenBy(const PoisonBacterium& bacterie) override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment en fonction du type de la bactérie
     * (appelle la méthode getScoreCoefficient de la sous classe à laquelle appartient la bactérie = polymorphisme)
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const Bacterium& bacterie) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment pour une bactérie simple
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const SimpleBacterium& bacterie) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment pour une bactérie à comportement de groupe
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const SwarmBacterium& bacterie) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment pour une bactérie à tentacule
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const TwitchingBacterium& bacterie) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment pour une bactérie à poison
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const PoisonBacterium& bacterie) const override;

    /**
     * @brief getNutriBCounter
     * @return Le nombre d'instance de nutriment B présent dans la boîte de Petri
     */
    static unsigned int getNutriBCounter();

    /** Destructeur
      */
    ~NutrimentB() override;

private :
    static unsigned int nutriBCounter;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux nutriments B
     * @return La valeur de getAppConfig()["nutriments"]["B"]
     */
    j::Value const& getConfig() const override;
};
