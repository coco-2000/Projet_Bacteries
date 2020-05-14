# pragma once
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "CircularBody.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "Swarm.hpp"

typedef std::unordered_map<std::string, double> GraphData;

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
     * @brief PetriDish Empêche la copie
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

    /**
     * @brief getNutrimentColliding Vérifie si un corps circulaire est en contact avec un des
     *        nutriments de la boite de Petri et retourne le nutriment si c'est le cas
     * @param body Corps circulaire dont on vérifie la collision avec les nutriments
     * @return Le nutriment avec lequel le corps circulaire est en collision s'il existe (nullptr sinon)
     */
    Nutriment* getNutrimentColliding(CircularBody const& body) const;

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
     * @brief initGradient Initialise l'attribut puissance de l'assiette de
     *        Petri qui est associée au paramètre "Gradient exponent" en fonction du
     *        fichier de configuration
     */
    void initGradient();

    /**
     * @brief addAnnex Ajoute un pointeur sur une bactérie le vecteur annexe
     *                     de l'assiette de Petri
     * @param clone Pointeur sur la bactérie à ajouter (créée par clonage en l'occurence)
     */
    void addAnnex(Bacterium*);

    /**
     * @brief addSwarm Ajoute un groupe Swarm à la boîte de Petri
     * @param groupe Swarm à ajouter
     */
    void addSwarm(Swarm *groupe);

    /**
     * @brief getSwarmWithId Accesseur pour le Swarm de la boite de Petri associé à un identificateur donné
     * @param id Identificateur du Swarm à retourner
     * @return Swarm dont l'identifiacteur est id
     */
    Swarm* getSwarmWithId(std::string id) const;

    /**
     * @brief PetriDish::~PetriDish destructeur, detruit l'assiette de petri
     * avec les bactéries et les nutriments qu'elle contient
     */
    ~PetriDish() override;

    /**
     * @brief getPropertySimpleBacterium calcule les nouvelles valeurs associées
     * à chacune des series du graphe SimpleBacteria
     * @return l'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertySimpleBacteria() const;

    /**
     * @brief getPropertyTwitchingBacteria calcule les nouvelles valeurs associées
     * à chacune des series du graphe TwitchingBacteria
     * @return l'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyTwitchingBacteria() const;

    /**
     * @brief getPropertyBacteria calcule les nouvelles valeurs associées
     * à chacune des series du graphe Bacteria
     * @return l'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyBacteria() const;

    /**
     * @brief getPropertyNutrimentQuantity calcule les nouvelles valeurs
     * associées à chacune des series du graphe NutrimentQuantity
     * @return l'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyNutrimentQuantity() const;

    /**
     * @brief getPropertyGeneral calcule les nouvelles valeurs
     * associées à chacune des series du graphe Général
     * @return l'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyGeneral() const;

private :
    std::vector<Bacterium*> lesBacteries;
    std::vector<Swarm*> lesSwarms;
    std::vector<Nutriment*> lesNutriments;
    double puissance;
    double temperature;
    std::vector<Bacterium*> annexe;

    /**
     * @brief getMeanBacteria calcule la moyenne des valeurs d'un paramètre mutable
     * sur toutes les bactéries possédant ce paramètre mutable
     * @param s le nom du paramètre mutable
     * @return la moyenne
     */
    double getMeanBacteria(const std::string& s) const;

    /**
     * @brief getTotalNutriment calcule la somme de toutes les quantités de nutriments
     * présents dans l'assiette de Petri
     * @return la somme totale
     */
    double getTotalNutriment() const;

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
     * @brief initAnnex Initialise le vecteur annexe de l'assiette de Petri
     *                    à un vecteur vide
     */
    void initAnnex();

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres associée à l'assiette de Petri
     * @return la valeur de getAppConfig()["petri dish"]
     */
    j::Value const& getConfig() const;

    /**
     * @brief update_swarms Mise à jour de vecteur de Swarm de l'assiette de Petri
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void update_swarms(sf::Time dt);

};


