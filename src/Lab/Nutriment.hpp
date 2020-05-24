#pragma once
#include "CircularBody.hpp"
#include "Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"

class Bacterium;
class SimpleBacterium;
class SwarmBacterium;
class TwitchingBacterium;
class PoisonBacterium;

class Nutriment : public CircularBody, public Drawable, public Updatable
{

public :
    /**
     * @brief Nutriment Constructeur
     * @param quantity Quantité intiale de l'instance courante
     * @param position Coordonnées de la position intiale de l'instance courante
     */
    Nutriment(Quantity quantity, const Vec2d& position);

    /**
     * @brief drawOn Dessine un nutriment
     * @param target Fenêtre dans laquelle le nutriment est dessiné
     */
    void drawOn(sf::RenderTarget& target) const override;

   /**
    * @brief update Effectue la croissance d'un nutriment en mettant à jour sa quantité et son rayon
    * @param dt Pas de temps après lequel lequel le nutriment est mise à jour
    */
    void update(sf::Time dt) override;

    /**
     * @brief temperatureCondition Vérifie les conditions portant sur la température pour la croissance des nutriments
     * @param temperature Température courante
     * @return true si les conditions sont respectées false sinon
     */
    bool temperatureCondition(double temperature) const;

    /**
     * @brief isEmpty Permet de savoir si la source de nutriment est vide (quantity = 0)
     * @return vrai s'il n'y a plus de nutriment false sinon
     */
    bool isEmpty() const;

    /**
     * @brief takeQuantity Prélève une quantité donnée de nutriments de l'instance courante
     * @param taking Quantité de nutriments à prélever
     * @return Quantité de nutriments qui a pu être prélevée
     */
    Quantity takeQuantity(Quantity taking);

    /**
     * @brief getQuantity
     * @return La quantité de nutriment contenue dans la source de nutriment
     */
    Quantity getQuantity() const;

    /**
     * Methode virtuelle pure
     * @brief eatenBy Calcule la quantité cédée par la source de nutriment à la bactérie
     * (appelle la méthode eatableQuantity de la sous classe à laquelle appartient la bactérie = polymorphisme)
     * @param bacterie dont on calcule la quantité de nutriment qu'elle consomme
     * @return La quantité de nutriment consommée
     */
    virtual Quantity eatenBy(const Bacterium& bacterie) = 0;

    /**
     * Methode virtuelle pure
     * @brief eatenBy Calcule la quantité cédée par la source de nutriments à la bactérie simple
     * @return La quantité de nutriment consommée
     */
    virtual Quantity eatenBy(const SimpleBacterium& bacterie) = 0;

    /**
     * Methode virtuelle pure
     * @brief eatenBy Calcule la quantité cédée par la source de nutriments à la bactérie à comportement de groupe
     * @return La quantité de nutriment consommée
     */
    virtual Quantity eatenBy(const SwarmBacterium& bacterie) = 0;

    /**
     * Methode virtuelle pure
     * @brief eatenBy Calcule la quantité cédée par la source de nutriments à la bactérie à tentacule
     * @return La quantité de nutriment consommée
     */
    virtual Quantity eatenBy(const TwitchingBacterium& bacterie) = 0;

    /**
     * Methode virtuelle pure
     * @brief eatenBy Calcule la quantité cédée par la source de nutriments à la bactérie à poison
     * @return La quantité de nutriment consommée
     */
    virtual Quantity eatenBy(const PoisonBacterium& bacterie) = 0;

    /**
     * Méthode virtuelle pure
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment en fonction du type de la bactérie
     * (appelle la méthode getScoreCoefficient de la sous classe à laquelle appartient la bactérie = polymorphisme)
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return le coefficient calculée
     */
    virtual double getScoreCoefficient(const Bacterium& bacterie) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment pour une bactérie simple
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return le coefficient calculée
     */
    virtual double getScoreCoefficient(const SimpleBacterium& bacterie) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment pour une bactérie à comportement de groupe
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return le coefficient calculée
     */
    virtual double getScoreCoefficient(const SwarmBacterium& bacterie) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment pour une bactérie à tentacule
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return le coefficient calculée
     */
    virtual double getScoreCoefficient(const TwitchingBacterium& bacterie) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief getScoreCoefficient Calcule le coefficient associée au score du nutriment pour une bactérie à poison
     * @param bacterie Instance de bactérie pour laquelle on calcule le score associée à la position
     * @return le coefficient calculée
     */
    virtual double getScoreCoefficient(const PoisonBacterium& bacterie) const = 0;

protected :

    /**
     * @brief setQuantity Manipulateur de quantité, actualise égalment le rayon du nutriment
     * @param quantity à assigner à l'attribut quantité (+ rayon) du nutriment
     */
    void setQuantity(Quantity quantity);

private :

    Quantity quantity;

    /**
     * @brief displayQuantity Affiche la quantité du nutriment (si mode debugging activé)
     * @param target Cible pour l'affichage
     */
    void displayQuantity(sf::RenderTarget& target) const;

    /**
     * méthode virtuelle pure
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux nutriments
     */
     virtual j::Value const& getConfig() const = 0;

    /**
     * @brief Suppression du constructeur de copie pour empêcher son utilisation car il n'est
     * pas utilisé et afin d'éviter d'avoir à le redéfinir dans les sous classes de nutriment
     */
    Nutriment(const Nutriment& other) = delete;

    /**
     * @brief Suppression de l'operator= pour empecher l'usage de l'opérateur d'affectation car
     * il n'est pas utilisé et afin d'éviter d'avoir à le redéfinir dans les sous classes de nutriment
     * lorsque le constructeur de copie est redéfini pour incrémenter les compteurs par exemple
     */
    Nutriment& operator=(Nutriment const&) = delete;

    /**
     * @brief getGrowthSpeed Raccourci pour le paramètre de vitesse de croissance du fichier de configuration
     * en fonction du type de nutriment
     * @return la valeur associée à growth speed du fichier de configuration
     */
    double getGrowthSpeed() const;

    /**
     * @brief getMaxQuantity Raccourci pour le paramètre quantité maximale du fichier de configuration en
     * fonction du type de nutriment
     * @return la valeur associée à quantity max du fichier de configuration
     */
    double getMaxQuantity() const;
};
