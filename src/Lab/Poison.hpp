#pragma once
#include "Nutriment.hpp"
#include "../Interface/Drawable.hpp"

class Poison : public Nutriment
{
public:
    /**
     * @brief Poison Constructeur
     * @param quantity Quantité intiale de l'instance courante
     * @param position Coordonnées de la position intiale de l'instance courante
     */
    Poison(Vec2d const& position);

    /**
     * @brief getNutriBCounter
     * @return le nombre d'instance de poison présent dans la boîte de Petri
     */
    static unsigned int getPoisonCounter();

    /**
     * @brief eatenBy Calcule la quantité d'énergie ôtée par le poison à la bactérie
     * (appelle la méthode eatableQuantity de la sous classe à laquelle appartient la bactérie = polymorphisme)
     * @param bacterie dont on calcule la quantité d'énergie qu'elle perd
     * @return La quantité de poison "consommée" (autrement dit -énergie perdue par la bactérie)
     */
    Quantity eatenBy(const Bacterium& bacterie) override;

    /**
     * @brief eatenBy Calcule la quantité d'énergie ôtée par le poison à la bactérie simple
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de poison "consommée" (autrement dit -énergie perdue par la bactérie)
     */
    Quantity eatenBy(const SwarmBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcule la quantité d'énergie ôtée par le poison à la bactérie à comportement de groupe
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de poison "consommée" (autrement dit -énergie perdue par la bactérie)
     */
    Quantity eatenBy(const SimpleBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcul la quantité d'énergie ôtée par le poison à la bactérie à tentacule
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de poison "consommée" (autrement dit -énergie perdue par la bactérie)
     */
    Quantity eatenBy(const TwitchingBacterium& bacterie) override;

    /**
     * @brief eatenBy Calcule la quantité d'énergie ôtée par le poison à la bactérie à poison
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de poison "consommée" (autrement dit -énergie perdue par la bactérie)
     */
    Quantity eatenBy(const PoisonBacterium& bacterie) override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associé au score du poison en fonction du type de la bactérie
     * (appelle la méthode getScoreCoefficient de la sous classe à laquelle appartient la bactérie = polymorphisme)
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const Bacterium& bacterie) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du poison pour une bactérie simple
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const SimpleBacterium& bacterie) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du poison pour une bactérie à comportement de groupe
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const SwarmBacterium& bacterie) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du poison pour une bactérie à tentacule
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const TwitchingBacterium& bacterie) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du poison pour une bactérie à poison
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return Le coefficient calculée
     */
    double getScoreCoefficient(const PoisonBacterium& bacterie) const override;

    /** Destructeur
      */
    ~Poison();

private :
    static unsigned int poisonCounter;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux poisons
     * @return la valeur de getAppConfig()["nutriments"]["poison"]
     */
    j::Value const& getConfig() const override;
};
