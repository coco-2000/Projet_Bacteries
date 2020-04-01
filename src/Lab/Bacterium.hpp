#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Utility/MutableColor.hpp"
#include <SFML/Graphics.hpp>
#include "Utility/Types.hpp"
#include <string>

class Bacterium : public CircularBody, public Drawable, public Updatable
{
public :

    /**
     * @brief Bacterium::Bacterium Constructeur
     * @param energie niveau d'énergie intiale de la bacterie
     * @param position Coordonnées de la position intiale de la bacterie
     * @param direction Direction du déplacement initiale de la bacterie
     * @param couleur couleur initiale de la bacterie
     * @param param_mutables ensemble de paramètres numériques mutables
     * @param abstinence si la bacterie consomme des nutriments ou non
     */
    Bacterium(Quantity energie, Vec2d position, Vec2d direction,
              double radius, const MutableColor& couleur,
              std::map<std::string, MutableNumber>param_mutables = {},
              bool abstinence = 0);

    /**
     * @brief en_vie savoir si la bacterie a suffisamment d'energie pour etre en vie
     * @return vrai si l'energie est suffisante
     */
    bool en_vie();

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries
     * Il s'agit d'une méthode virtuelle pure
     * @return
     */
    virtual j::Value const& getConfig() const = 0;

    /**
     * @brief getEnergy
     * @return l'énergie minimale nécessaire à la division
     */
    Quantity getEnergy() const;

    /**
     * @brief getDelay
     * @return le temps d'attente entre deux consommations de nutriments pour la bactérie
     */
    sf::Time getDelay() const;

    /**
     * @brief getEnergyReleased
     * @return l'énergie dépensée à chaque pas de déplacement
     */
    Quantity getEnergyReleased() const;

    /**
     * @brief drawOn dessiner la bacterie
     * @param target la fenetre dans laquelle on affiche la bacterie
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief update gère le déplacement des bacteries,
     * les collisions avec le bord de l'assiette de petri
     * la consommation des nutriments par les bacteries
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief consumeEnergy décrémenter le niveau d'énergie
     * @param qt la quantité pour laquelle l'énergie est décrémentée
     */
    void consumeEnergy(Quantity qt);

    void setDirection(Vec2d direction);

    void addProperty(const std::string&, MutableNumber);
    MutableNumber getProperty(const std::string&) const;

    void setScore(double score);


protected :
    MutableColor couleur;
    double angle;
    Vec2d direction;
    Quantity energie;
    std::map<std::string, MutableNumber> param_mutables;
    bool abstinence;

    sf::Time compteur;
    sf::Time tps_basculement;
    double ancien_score;


    /**
     * @brief DisplayEnergy Affiche la quantité d'énergie de la bacterie (si mode debugging activé)
     * @param target Cible pour l'affichage
     */
    void DisplayEnergy(sf::RenderTarget& target) const;

    /**
     * @brief collisionPetri gère les collisions des bacteries
     * avec l'assiette de petri
     */
    void collisionPetri(sf::Time dt);

    /**
     * @brief consumeNutriment gère la consommation des bacteries
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void consumeNutriment(sf::Time dt);

    virtual void move(sf::Time dt) = 0;
    virtual Bacterium* clone() const = 0;
    virtual void graphisme_particulier(sf::RenderTarget& target) const = 0;
    virtual void tentative_basculement();
    void mutate();
    virtual Bacterium* copie() const = 0;

};
