#pragma once
#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "NutrimentGenerator.hpp"

constexpr double ratio_rayon(0.95/2);

class Lab : public Drawable, public Updatable
{
public:
    /**
      * @brief Lab constructeur permet de positionner l'assiette de Petri au centre
      * de la fenêtre graphique associée au Lab et avec un diamètre occupant les 45%
      * de la largeur de cette fenêtre.
      */
     Lab();

     /**
      * @brief update faire évoluer un Lab
      * pour le moment fait seulement évoluer l'assiette de Petri
      * @param dt l'intervalle de temps écoulé depuis le dernier update
      */
     void update(sf::Time dt);

     /**
      * @brief drawOn dessiner un lab
      * pour le moment dessine seulement une assiette de Petri
      * @param targetWindow la fenetre dans laquelle le Lab est affiché
      */
     void drawOn(sf::RenderTarget& targetWindow) const;

     /**
      * @brief reset vide l'assiette de Petri
      * sera appelé pour faire fonctionner la touche 'R'
      * réinitialise le générateur de nutriments
      */
     void reset();

     /**
      * @brief contains Verifie si un CIrcularBody est à l'interueur de son assiette de Petri
      * @return true si le CircularBody est à l'interieur false sinon
      */
     bool contains(const CircularBody&) const;

     /**
      * @brief increaseTemperature permet d'augmenter la température
      * des éléments du lab
      */
     void increaseTemperature();

     /**
      * @brief decreaseTemperature permet de diminuer la température
      * des éléments du lab
      */
     void decreaseTemperature();

     /**
      * @brief init_temperature permet de réinitialiser la température
      * des éléments du lab à la valeur du fichier de configuration
      */
     void init_temperature();

     /**
      * @brief addNutriment permet de ajouter un nutriment au lab
      * @param nutriment : celui qui est ajouté au lab
      */
     void addNutriment(Nutriment* nutriment);

     /**
      * @brief getTemperature obtenir la temperature de l'assiette de petri
      * du lab
      * @return la température de l'assiette de petri
      */
     double getTemperature() const;

     ~Lab();

private :

    PetriDish petri;
    NutrimentGenerator generateur_nutriment;

};
