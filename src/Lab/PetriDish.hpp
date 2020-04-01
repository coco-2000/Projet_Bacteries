# pragma once
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "CircularBody.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"


class PetriDish : public CircularBody, public Drawable, public Updatable
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
     * Suprime les nutriments et les bacteries si besoin
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres associée à l'assiette de Petri
     * @return la valeur de getAppConfig()["petri dish"]
     */
    j::Value const& getConfig() const;

    /**
     * @brief drawOn dessiner l'assiette de petri
     * @param targetWindow la fenetre dans laquelle on affiche l'assiette de Petri
     */
    void drawOn(sf::RenderTarget& targetWindow) const override;

    /**
     * @brief PetriDish::reset supprime toutes les bacteries et tous les
     * nutriments placés dans l'assiette
     * réinitialise la température
     */
    void reset();

    /**
     * @brief getTemperature Accesseur de temperature
     * @return La temperature courante de l'assiette de Petri
     */
    double getTemperature() const;

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

    Nutriment* getNutrimentColliding(CircularBody const& body) const;

    /**
     * @brief PetriDish::~PetriDish destructeur, detruit l'assiette de petri
     * avec les bactéries et les nutriments qu'elle contient
     */
    ~PetriDish() override;

    /**
     * @brief getPositionScore Calcule le score associée à une position donnée dans
     *                         l'assiette de Petri
     * @param position Coordonnées de la position dont il faut calculer le score
     * @return Score associée à la position
     */
    double getPositionScore(const Vec2d& position) const;

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
     * @brief init_puissance Initialise l'attribut puissance de l'assiette de
     *        Petri qui est associée au paramètre "Gradient exponent" en fonction du
     *        fichier de configuration
     */
    void init_puissance();

    /**
     * @brief ajout_annexe Ajoute un pointeur sur une bactérie le vecteur annexe
     *                     de l'assiette de Petri
     * @param clone Pointeur sur la bactérie à ajouter (créée par clonage en l'occurence)
     */
    void ajout_annexe(Bacterium*);

private :
    std::vector<Bacterium*> lesBacteries;
    std::vector<Nutriment*> lesNutriments;
    double puissance;
    double temperature;
    std::vector<Bacterium*> annexe;

    /**
     * @brief update_bacteries assure le déplacement, les collisions et la consommation
     * des nutriments pour toutes les bacteries de l'assiette de petri
     * @param dt
     */
    void update_bacteries (sf::Time dt);

    /**
     * @brief update_nutriments Effectue la croissance de tous les nutriments de l'assiette de Petri
     * en mettant à jour leur quantité et leur rayon
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void update_nutriments (sf::Time dt);

    /**
     * @brief init_annexe Initialise le vecteur annexe de l'assiette de Petri
     *                    à un vecteur vide
     */
    void init_annexe();
};


