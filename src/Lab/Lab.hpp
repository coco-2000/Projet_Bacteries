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
      * @brief Lab Constructeur qui permet de positionner l'assiette de Petri au centre de la fenêtre
      *            graphique associée au Lab et avec un diamètre occupant les 95% de la largeur de cette fenêtre.
      */
     Lab();

     /**
      * @brief update Fais évoluer le Lab qui gère la mise à jour de l'assiette de Petri et du générateur de nutriment
      * @param dt l'intervalle de temps écoulé depuis le dernier update
      */
     void update(sf::Time dt) override;

     /**
      * @brief drawOn Dessine un Lab qui gère le dessin de son assiette de Petri
      * @param targetWindow la fenêtre dans laquelle le Lab est affiché
      */
     void drawOn(sf::RenderTarget& targetWindow) const override;

     /**
      * @brief reset Vide l'assiette de Petri et réinitialise le générateur de nutriments
      * (est appelé pour faire fonctionner la touche 'R')
      */
     void reset();

     /**
      * @brief increaseTemperature Augmente la température de la boite de Petri du Lab
      */
     void increaseTemperature();

     /**
      * @brief decreaseTemperature Diminue la température de la boite de Petri du Lab
      */
     void decreaseTemperature();

     /**
      * @brief addNutriment Ajoute un nutriment à la boite de Petri du Lab
      * @param nutriment qui est ajouté à la boite de Petri du Lab
      * @return vrai si le nutriment a pu être ajouté
      */
     bool addNutriment(Nutriment* nutriment);

     /**
      * @brief addBacterium Ajouter une bacterie à la boite de Petri du Lab
      * @param bacterie qui est ajouté à la boite de Petri du Lab
      * @return vrai si la bactérie a pu être ajoutée
      */
     bool addBacterium(Bacterium* bacterie);

     /**
      * @brief addObstacle Ajoute un obstacle à la boite de Petri du Lab
      * @param obstacle qui est ajouté à la boite de Petri du Lab
      * @return vrai si l'obstacle a pu être ajouté
      */
     bool addObstacle(Obstacle* obstacle);

     /**
      * @brief createWall crée un mur d'obstacles dans la boite de Petri du Lab
      * @param position1 Coordonnées du 1er obstacle du mur
      * @param position2 Coordonnées du dernier obstacle du mur
      */
     void createWall(const Vec2d& position1, const Vec2d& position2);

     /**
      * @brief deleteObstacle Supprime un obstacle de la boite de Petri du Lab
      * @param position Coordonnées de l'obstacle à supprimer
      */
     void deleteObstacle(const Vec2d& position);

     /**
      * @brief minimumDistToObstacle Calcule la distance entre la position donnée et l'obstacle le plus proche
      * @param position
      * @return La distance calculée
      */
     double minimumDistToObstacle(const Vec2d& position) const;

     /**
      * @brief getLastObstaclePos
      * @return La position du dernier obstacle créé et non supprimé
      */
     Vec2d getLastObstaclePos() const;

     /**
      * @brief getTemperature
      * @return la température de l'assiette de petri du Lab
      */
     double getTemperature() const;

     /**
      * @brief doesCollideWithDish Vérifie si le body entre en collision avec l'assiette de petri du Lab
      * @param body Corps dont on vérifie la collision
      * @return true s'il est en collision, false sinon
      */
     bool doesCollideWithDish(CircularBody const& body) const;

     /**
      * @brief doesCollideWithDish Vérifie si le body entre en collision avec un obstacle de l'assiette de petri du Lab
      * @param body Corps dont on vérifie la collision
      * @return true s'il est en collision, false sinon
      */
     bool doesCollideWithObstacle(CircularBody const& body) const;

     /**
      * @brief getNutrimentColliding Permet d'obtenir le nutriment en collision avec un CircularBody
      * @param body Corps qui peut rentrer en collision avec le nutriment
      * @return Le nutriment qui est en collision avec le body
      */
     Nutriment* getNutrimentColliding(CircularBody const& body) const;

     /**
      * @brief getPositionScore Calcule le score associé à une position dans l'assiette de petri en fonction du type de la bactérie considérée
      * @param position Coordonnées de la position dont il faut calculer le score
      * @param bacterie dont laquelle on calcule le score
      * @return Le score associée à la position
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
      * @brief addSwarm Ajoute un groupe Swarm à la boîte de Petri du Lab
      * @param group Swarm à ajouter
      */
     void addSwarm(Swarm* group);

     /**
      * @brief getSwarmWithId
      * @param id Identificateur du Swarm à retourner
      * @return Swarm dont l'identifiacteur est id
      */
     Swarm* getSwarmWithId(const std::string& id) const;

     /**
      * @brief fetchData permet de calculer la nouvelle donnée à insérer dans chaque série d'un graph
      * @param titre : le titre du graphe pour lequel les calculs sont effectués
      * @return L'ensemble des nouvelles valeurs calculées correpondant à chacune des séries du graph
      */
     std::unordered_map<std::string, double> fetchData(const std::string & titre) const;

     /**
      * @brief resetControls Réinitialise les paramètres de la simulation en fonction des valeurs du fichier de configuration
      */
     void resetControls();

     /**
      * @brief getDistToPetri Calcule la distance entre la position donnée et le bord de l'assiete de Petri
      * @param position Coordonnées de la position dont on calcule la distance
      * @return la distance calculée
      */
     double getDistToPetri(const Vec2d& position) const;

     /**
      * @brief getMiddleDirectionVector
      * @param position Coordonnées de la position à partir de laquelle on cherche le vecteur directeur
      * @return Le vecteur directeur unitaire entre la position et le centre de l'assiette de petri du Lab
      */
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
     * @param body Corps pour lequel on vérifie s'il se trouve à l'interieur
     * @return true si le CircularBody est à l'interieur false sinon
     */
    bool contains(const CircularBody& body) const;

    /**
     * @brief initGradient Initialise l'attribut puissance de l'assiette de Petri qui est associée au
     * paramètre "Gradient exponent" en fonction du fichier de configuration
     */
    void initGradient();

    /**
     * @brief initTemp Réinitialise la température de la boite de Petri du Lab d'après la valeur du
     *                 fichier de configuration
     */
    void initTemp();
};
