#include "PetriDish.hpp"
#include "../Utility/Utility.hpp"
#include "../Config.hpp"
#include "CircularBody.hpp"

/**
 * @brief PetriDish::PetriDish constructeur de PetriDish appel le constructeur de CircularBody
 * @param position
 * @param radius
 */
PetriDish::PetriDish(Vec2d position, double radius)
    : CircularBody (position, radius)
{}

/**
 * @brief PetriDish::addBacterium peuple l'assiette
 * @param bacterie ajoutée à l'assiette
 * @return vrai si la bacterie a pu être placé dans l'assiette
 */
bool PetriDish::addBacterium(Bacterium* bacterie)
{
    bool conditions = true;

    if (conditions)
        lesBacteries.push_back(bacterie);

    return conditions;
}

/**
 * @brief PetriDish::addNutriment place nutriments dans l'assiette
 * @param nutriment ajouté à l'assiette
 * @return vrai si le nutriment a pu être placé dans l'assiette
 */
bool PetriDish::addNutriment(Nutriment* nutriment)
{

    bool conditions = true;

    if (conditions)
        lesNutriments.push_back(nutriment);

    return conditions;
}

/**
 * @brief PetriDish::reset supprime toutes les bacteries et tous les
 * nutriments placés dans l'assiette
 */
void PetriDish::reset()
{
    for (auto& bacterie : lesBacteries)
    {
        delete bacterie;
        bacterie = nullptr;
    }

    for (auto& nutriment : lesNutriments)
    {
        delete nutriment;
        nutriment = nullptr;
    }
}

/**
 * @brief PetriDish::~PetriDish destructeur, detruit l'assiette de petri
 * avec les bactéries et les nutriments qu'elle contient
 */
PetriDish::~PetriDish()
{
    reset();
}

/**
 * @brief PetriDish::update
 * @param dt
 */
void PetriDish::update(sf::Time dt)
{
    //faire evoluer les bacteries
}

/**
 * @brief PetriDish::drawOn
 * @param targetWindow
 */
void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    auto border = buildAnnulus(position, radius, sf::Color::Black, epaisseur_anneau);
    targetWindow.draw(border);
}

