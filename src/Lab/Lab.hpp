#pragma once

#include <SFML/Graphics.hpp>
#include "PetriDish.hpp"
#include "Swarm.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "NutrimentGenerator.hpp"

typedef std::function<std::unordered_map<std::string, double>()> Result;

class Lab : public Drawable, public Updatable
{
public:
    /**
      * @brief Lab constructeur permet de positionner l'assiette de Petri au centre
      * de la fenêtre graphique associée au Lab et avec un diamètre occupant les 95%
      * de la largeur de cette fenêtre.
      */
     Lab();

     /**
      * @brief update faire évoluer un Lab
      * pour le moment fait seulement évoluer l'assiette de Petri
      * @param dt l'intervalle de temps écoulé depuis le dernier update
      */
     void update(sf::Time dt) override;

     /**
      * @brief drawOn dessiner un lab
      * pour le moment dessine seulement une assiette de Petri
      * @param targetWindow la fenetre dans laquelle le Lab est affiché
      */
     void drawOn(sf::RenderTarget& targetWindow) const override;

     /**
      * @brief reset vide l'assiette de Petri
      * sera appelé pour faire fonctionner la touche 'R'
      * réinitialise le générateur de nutriments
      */
     void reset();

     /**
      * @brief increaseTemperature Augmenter la température de la boite de Petri du Lab
      */
     void increaseTemperature();

     /**
      * @brief decreaseTemperature Diminue la température de la boite de Petri du Lab
      */
     void decreaseTemperature();

     /**
      * @brief addNutriment Ajoute un nutriment à la boite de Petri du Lab
      * @param Nutriment qui est ajouté à la boite de Petri du Lab
      * @return vrai si le nutriment a pu être ajouté
      */
     bool addNutriment(Nutriment* nutriment);

     /**
      * @brief addBacterium permet d'ajouter des bacteries au lab
      * @param bacterie : celle qui est ajoutée au lab
      * @return vrai si la bactérie a pu être ajoutée
      */
     bool addBacterium(Bacterium* bacterie);

     /**
      * @brief addObstacle ajoute obstacle au lab
      * @param obstacle ajouté au lab
      * @return vrai si l'obstacle a pu être ajouté
      */
     bool addObstacle(Obstacle* obstacle);

     /**
      * @brief createWall crée un mur d'obstacles dans le lab
      * @param position1 position du 1er obstacle du mur
      * @param position2 position du dernier obstacle du mur
      */
     void createWall(const Vec2d& position1, const Vec2d &position2);

     /**
      * @brief deleteObstacle supprime obstacle de l'assiette
      * @param position coordonnées de l'obstacle à supprimer
      */
     void deleteObstacle(const Vec2d& position);

     /**
      * @brief minimumDistToObstacle
      * @param position
      * @return la distance entre la position donnée et l'obstacle le plus proche
      */
     double minimumDistToObstacle(const Vec2d& position) const;

     /**
      * @brief getLastObstaclePos
      * @return la position du dernier obstacle créé et non supprimé
      */
     Vec2d getLastObstaclePos() const;

     /**
      * @brief getTemperature obtenir la temperature de l'assiette de petri du lab
      * @return la température de l'assiette de petri
      */
     double getTemperature() const;

     /**
      * @brief doesCollideWithDish regarde si le body rentre en collision avec l'assiette de petri
      * @param body le corps qui peut rentrer en collision
      * @return vrai s'il est en collision
      */
     bool doesCollideWithDish(CircularBody const& body) const;

     /**
      * @brief doesCollideWithDish regarde si le body rentre en collision avec un obstacle de la petri
      * @param body le corps qui peut rentrer en collision
      * @return vrai s'il est en collision
      */
     bool doesCollideWithObstacle(CircularBody const& body) const;

     /**
      * @brief getNutrimentColliding obtenir le nutriment en collision avec le body
      * @param body le corps qui peut rentrer en collision avec le nutriment
      * @return le nutriment qui est en collision avec le body
      */
     Nutriment* getNutrimentColliding(CircularBody const& body) const;

     /**
      * @brief getPositionScore Calcule le score associée à une position donnée dans
      *                         l'assiette de Petri
      * @param position Coordonnées de la position dont il faut calculer le score
      * @return Score associée à la position
      */
     double getPositionScore(const Vec2d& position, const Bacterium& bacterie) const;

     /**
      * @brief increaseGradientExponent Augmente l'attribut puissance de l'assiette de
      *        Petri qui est associée au paramètre "Gradient exponent"
      */
     void increaseGradientExponent();

     /**
      * @brief decreaseGradientExponent Diminue l'attribut puissance de l'assiette de
      *        Petri qui est associée au paramètre "Gradient exponent"
      */
     void decreaseGradientExponent();

     /**
      * @brief getGradientExponent Accesseur de l'attribut puissance de l'assiette de
      *        Petri qui est associée au paramètre "Gradient exponent"
      * @return la valeur du paramètre "Gradient exponent"
      */
     double getGradientExponent() const;

     /**
      * @brief addAnnex Ajoute un pointeur sur une bactérie le vecteur annexe de l'assiette de Petri
      * @param clone Pointeur sur la bactérie à ajouter (créée par clonage en l'occurence)
      */
     void addAnnex(Bacterium* clone);

     /**
      * @brief addSwarm Ajoute un groupe Swarm à la boîte de Petri
      * @param groupe Swarm à ajouter
      */
     void addSwarm(Swarm* groupe);

     /**
      * @brief getSwarmWithId Accesseur pour le Swarm associé à un identificateur donné
      * @param id Identificateur du Swarm à retourner
      * @return Swarm dont l'identifiacteur est id
      */
     Swarm* getSwarmWithId(const std::string& id) const;

     /**
      * @brief fetchData permet de calculer la nouvelle donnée à insérer dans chaque série d'un graphe
      * @param titre : le titre du graphe pour lequel les calculs sont effectués
      * @return l'ensemble des nouvelles valeurs calculées correpondant à chacune des séries du graphe
      */
     std::unordered_map<std::string, double> fetchData(const std::string & titre) const;

     /**
      * @brief resetControls reinitialise les paramètres de la simulation en fonction des valeurs du fichier de configuration
      */
     void resetControls();

     double getDistToPetri(const Vec2d& position) const;

     Vec2d getMiddleDirectionVector(const Vec2d& position) const;

     /** @brief Destructeur
       */
     ~Lab() override;

private :

    PetriDish petri;
    NutrimentGenerator nutrimentGenerator;
    std::unordered_map<std::string, Result> namesGraph;

    /**
     * @brief contains Vérifie si un CircularBody est à l'intérieur de son assiette de Petri
     * @return true si le CircularBody est à l'interieur false sinon
     */
    bool contains(const CircularBody& corps) const;

    /**
     * @brief initGradient Initialise l'attribut puissance de l'assiette de
     *        Petri qui est associée au paramètre "Gradient exponent" en fonction du
     *        fichier de configuration
     */
    void initGradient();

    /**
     * @brief initTemp Réinitialise la température de la boite de Petri du Lab d'après
     *                 la valeur du fichier de configuration
     */
    void initTemp();
};
