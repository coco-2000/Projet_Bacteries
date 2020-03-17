# pragma once
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "CircularBody.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class PetriDish : public CircularBody
{
public:

    /**
     * @brief PetriDish::PetriDish constructeur de PetriDish appel le constructeur de CircularBody
     * @param position
     * @param radius
     */
    PetriDish(Vec2d position, double radius);

    /**
     * @brief PetriDish pour empecher la copie
     */
    PetriDish(PetriDish const&) = delete;

    /**
     * @brief operator = pour empecher l'usage de l'opérateur d'affectation
     */
    PetriDish& operator=(PetriDish const&) = delete;

    /**
     * @brief PetriDish::addBacterium peuple l'assiette
     * @param bacterie ajoutée à l'assiette
     * @return vrai si la bacterie a pu être placé dans l'assiette
     */
    bool addBacterium(Bacterium* bacterie);

    /**
     * @brief PetriDish::addNutriment place nutriments dans l'assiette
     * @param nutriment ajouté à l'assiette
     * @return vrai si le nutriment a pu être placé dans l'assiette
     */
    bool addNutriment(Nutriment* nutriment);

    //à commenter
    void update(sf::Time dt);

    /**
     * @brief drawOn dessiner l'assiette de petri
     * @param targetWindow la fenetre dans laquelle on affiche l'assiette de Petri
     */
    void drawOn(sf::RenderTarget& targetWindow) const;

    /**
     * @brief PetriDish::reset supprime toutes les bacteries et tous les
     * nutriments placés dans l'assiette
     */
    void reset();

    /**
     * @brief PetriDish::~PetriDish destructeur, detruit l'assiette de petri
     * avec les bactéries et les nutriments qu'elle contient
     */
    ~PetriDish();


private :
    std::vector<Bacterium*> lesBacteries;
    std::vector<Nutriment*> lesNutriments;
};


