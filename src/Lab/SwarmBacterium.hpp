#pragma once

#include "Bacterium.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/DiffEqSolver.hpp"


class Swarm;

class SwarmBacterium : public Bacterium, public DiffEqFunction
{
public:

    /**
     * @brief SwarmBacterium Constructeur
     * Incrémente le compteur d'instances
     * @param position Coordonnées de la position l'instance à créer
     * @param group Swarm auquel la nouvelle instance appartient
     */
    SwarmBacterium(const Vec2d& position, Swarm* group);

    /**
     * @brief SwarmBacterium Constructeur de copie
     * Incrémente le compteur d'instances
     * @param other Instance de bactérie à copier
     */
    SwarmBacterium(SwarmBacterium const& other);

    /**
     * @brief drawOn Dessine une SwarmBacterium et l'anneau si l'instance courante est leader du groupe
     * @param target Fenêtre dans laquelle le dessin se fait
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommée par la bactérie et retire cette
     *                        quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie à comportement de groupe)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentA& nutriment) const override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie à comportement de groupe)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentB& nutriment) const override;

    /**
     * @brief eatableQuantity Calcule l'énergie oté à la bactérie par le poison et consomme le poison
     * (appelle la méthode eatenBy de poison qui prend pour argument une bactérie à comportement de groupe)
     *  @param poison qui est consommé par la bactérie
     * @return L'énergie otée à la bactérie
     */
    Quantity eatableQuantity(Poison& poison) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment de type A pour une bactérie
     *                            à comportement de groupe
     * (appelle la méthode getScoreCoefficient du nutrimentA qui prend pour argument une bactérie à comportement de groupe)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const NutrimentA& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment de type B pour une bactérie
     *                            à comportement de groupe
     * (appelle la méthode getScoreCoefficient du nutrimentB qui prend pour argument une bactérie à comportement de groupe)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const NutrimentB& nutriment) const override;

    /**
     * @brief getScoreCoefficient Calcule le coefficient associée au score du poison pour une bactérie à comportement
     *                            de groupe
     * @param poison qui est consommé par la bactérie
     * @return Le coefficient calculé
     */
    double getScoreCoefficient(const Poison& poison) const override;

    /**
    * @brief Destructeur
    * Détruit le pointeur vers le groupe auquel la bactérie appartient (sans détruire le Swarm lui-même)
    * Décrémente le compteur d'instances
    */
    ~SwarmBacterium() override;

    /**
     * @brief getSwarmCounter
     * @return Le nombre d'instance de SwarmBacterium présente dans l'assiette de Pétri
     */
    static unsigned int getSwarmCounter();

private:
    Swarm* group;
    static unsigned int swarmCounter;
    double speed;

    /**
     * @brief move Déplace une bactérie
     * @param dt Pas de temps depuis le dernier déplacement de l'instance courante
     */
    void move(sf::Time dt) override;

    /**
     * @brief clone Effectue la copie d'une instance avec tous ses attributs
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */
    SwarmBacterium* clone() const override;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries swarms
     * @return La valeur associée à getAppConfig()["swarm bacterium"]
     */
    j::Value const& getConfig() const override;

    /**
     * @brief getSpeedVector Calcule le vecteur de vitesse de l'instance courante
     * @return La vitesse courante de l'instance
     */
    Vec2d getSpeedVector() const;

    /**
     * @brief f Calcule le vecteur force déterminant le déplacement des SwarmBacterium lorsqu'elles sont perdues
     * Ici les bactéries ont un déplacement rectiligne uniforme
     * @param position Position de la bactérie sur laquelle s'applique la force calculée //inutilisé
     * @param speed Vitesse de la bactérie sur laquelle s'applique la force calculée //inutilisé
     * @return Le vecteur force appliqué sur la bactérie (ici un vecteur nul)
     */
    Vec2d f(Vec2d position, Vec2d speed) const override;
};
