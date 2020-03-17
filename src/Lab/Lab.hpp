#pragma once
#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>

constexpr double ratio_rayon(0.95/2);

class Lab
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
      */
     void reset();
     bool contains(const CircularBody&) const;

private :

    PetriDish petri;

};
