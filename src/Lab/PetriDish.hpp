# pragma once
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "CircularBody.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

constexpr int epaisseur_anneau(5);

typedef double Temperature;

class PetriDish : public CircularBody
{
public:

    /**
     * @brief PetriDish::PetriDish constructeur de PetriDish appel le constructeur
     * de CircularBody et initialise sa température à la valeur du fichier
     * de configuration
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

    /**
     * @brief update Effectue la croissance des nutriments de l'assiette de Petri en mettant à jour leur quantité et leur rayon
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
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
    /**
     * @brief getTemperature Accesseur de temperature
     * @return La temperature courante de l'assiette de Petri
     */
    Temperature getTemperature() const;

    /**
     * @brief increaseTemperature Augmente la température de l'assiette de Petri
     * Augmente d'un delta défini dans le fichier de configuration des paramètres
     */
    void increaseTemperature();

    /**
     * @brief decreaseTemperature Réduit la température de l'assiette de Petri
     * Augmente d'un delta défini dans le fichier de configuration des paramètres
     */
    void decreaseTemperature();

    /**
     * @brief init_temperature Initialise la température de l'assiette de Petri à sa valeur par défaut
     */
    void init_temperature();

private :
    std::vector<Bacterium*> lesBacteries;
    std::vector<Nutriment*> lesNutriments;

    Temperature temperature;
};


