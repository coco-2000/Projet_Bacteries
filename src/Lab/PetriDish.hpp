# pragma once
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "CircularBody.hpp"
#include "Obstacle.hpp"
#include <vector>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "Swarm.hpp"

typedef std::unordered_map<std::string, double> GraphData;

class PetriDish : public CircularBody, public Drawable, public Updatable
{
public:

    /**
     * @brief PetriDish Constructeur
     * @param position Coordonnées du centre de l'assiette de Petri
     * @param radius Rayon de l'assiette de Petri
     */
    PetriDish(const Vec2d& position, double radius);

    /**
     * @brief addBacterium Ajoute une bactérie à l'assiette de Petri
     * @param bacterie Instance à ajouter à l'assiette
     * @return true si la bacterie a pu être placé dans l'assiette false sinon
     */
   bool addBacterium(Bacterium* bacterie);

    /**
     * @brief addNutriment Ajoute un nutriment à l'assiette de Petri
     * @param nutriment Instance à ajouter à l'assiette
     * @return true si le nutriment a pu être placé dans l'assiette false sinon
     */
    bool addNutriment(Nutriment* nutriment);

    /**
     * @brief addObstacle Ajoute un obstacle à l'assiette de Petri
     * @param obstacle Instance à ajouter à l'assiette
     * @return true si l'obstacle a pu être placé dans l'assiette false sinon
     */
    bool addObstacle(Obstacle* obstacle);

    /**
     * @brief createWall Crée un mur d'obstacles dans l'assiette
     * @param position1 Coordonnées du 1er obstacle du mur
     * @param position2 Coordonnées du dernier obstacle du mur
     */
    void createWall(const Vec2d& position1, const Vec2d& position2);

    /**
     * @brief deleteObstacle Supprime un obstacle de l'assiette
     * @param position Coordonnées de l'obstacle à supprimer
     */
    void deleteObstacle(const Vec2d& position);

    /**
     * @brief minimumDistToObstacle Calcul la distance entre la position donnée et l'obstacle le plus proche
     * @param position Coordonnées de la position
     * @return La distance calculée
     */
    double minimumDistToObstacle(const Vec2d& position) const;

    /**
     * @brief doesCollideWithObstacle Vérifie si le corps entre en collision avec un obstacle
     * @param body Corps dont on vérifie la collision
     * @return true s'il est en collision false sinon
     */
    bool doesCollideWithObstacle(CircularBody const& body) const;

    /**
     * @brief getLastObstaclePos
     * @return La position du dernier obstacle créé et non supprimé
     */
    Vec2d getLastObstaclePos() const;

    /**
     * @brief addSwarm Ajoute un groupe Swarm à la boîte de Petri
     * @param swarm Groupe à ajouter
     */
    void addSwarm(Swarm* swarm);

    /**
     * @brief getSwarmWithId
     * @param id Identificateur du Swarm à retourner
     * @return Pointeur sur le swarm dont l'identifiacteur est id (nullptr si aucun ne correspond)
     */
    Swarm* getSwarmWithId(const std::string& id) const;

    /**
     * @brief update Effectue la croissance des nutriments de l'assiette de Petri en mettant à jour leur quantité et leur rayon
     * Supprime les nutriments et les bacteries si besoin
     * Met à jour le leader des swarms
     * @param dt Pas de temps après lequel la petri est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief drawOn Dessine l'assiette de petri
     * @param targetWindow Fenêtre dans laquelle on affiche l'assiette de Petri
     */
    void drawOn(sf::RenderTarget& targetWindow) const override;

    /**
     * @brief reset Supprime toutes les bacteries et tous les nutriments placés dans l'assiette
     *              et réinitialise la température
     */
    void reset();

    /**
     * @brief getTemperature
     * @return La temperature courante de l'assiette de Petri
     */
    double getTemperature() const;

    /**
     * @brief increaseTemperature Augmente la température de l'assiette de Petri d'un delta
     *        défini dans le fichier de configuration des paramètres
     */
    void increaseTemperature();

    /**
     * @brief decreaseTemperature Réduit la température de l'assiette de Petri d'un delta
     *        défini dans le fichier de configuration des paramètres
     */
    void decreaseTemperature();

    /**
     * @brief initTemperature Initialise la température de l'assiette de Petri à sa valeur par défaut
     */
    void initTemperature();

    /**
     * @brief getNutrimentColliding Vérifie si un corps circulaire est en contact avec un des
     *        nutriments de la boite de Petri et retourne le nutriment si c'est le cas
     * @param body Corps circulaire dont on vérifie la collision avec les nutriments
     * @return Le nutriment avec lequel le corps circulaire est en collision s'il existe (nullptr sinon)
     */
    Nutriment* getNutrimentColliding(CircularBody const& body) const;

    /**
     * @brief getPositionScore Calcule le score associé à une position donnée dans l'assiette de Petri
     * @param position Coordonnées de la position
     * @param bacterie Instance de bacterie dont on calcule le score associée à la position
     * @return Score associée à la position de la bactérie
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
     * @brief initGradient Initialise l'attribut puissance de l'assiette de
     *        Petri qui est associée au paramètre "Gradient exponent" en fonction du
     *        fichier de configuration
     */
    void initGradient();

    /**
     * @brief addAnnex Ajoute un pointeur sur une bactérie dans le vecteur annexe
     *                 de l'assiette de Petri
     * @param bacterie Pointeur sur la bactérie à ajouter (créée par clonage en l'occurence)
     */
    void addAnnex(Bacterium* bacterie);

    /**
     * @brief getPropertySimpleBacterium Calcule les nouvelles valeurs associées à chacune des séries du graphe SimpleBacteria
     * @return L'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertySimpleBacteria() const;

    /**
     * @brief getPropertyTwitchingBacteria Calcule les nouvelles valeurs associées à chacune des séries du graphe TwitchingBacteria
     * @return L'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyTwitchingBacteria() const;

    /**
     * @brief getPropertyBacteria Calcule les nouvelles valeurs associées à chacune des séries du graphe Bacteria
     * @return L'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyBacteria() const;

    /**
     * @brief getPropertyNutrimentQuantity Calcule les nouvelles valeurs associées à chacune des séries du graphe Nutriment Quantity
     * @return L'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyNutrimentQuantity() const;

    /**
     * @brief getPropertyGeneral Calcule les nouvelles valeurs associées à chacune des séries du graphe Général
     * @return L'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyGeneral() const;

    /**
     * @brief getPropertyNutriment Calcule les nouvelles valeurs associées à chacune des séries du graphe Nutriment
     * @return L'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyNutriment() const;

    /**
     * @brief getPropertyBacteriaDivision Calcule les nouvelles valeurs associées à chacune des séries du graphe Bacteria Division
     * @return L'ensemble des nouvelles valeurs calculées
     */
    GraphData getPropertyBacteriaDivision() const;

    /**
     * @brief ~PetriDish Destructeur : detruit l'assiette de petri avec les bactéries et les nutriments qu'elle contient
     */
    ~PetriDish() override;

private :
    std::vector<Bacterium*> bacteries;
    std::vector<Swarm*> swarms;
    std::vector<Nutriment*> nutriments;
    std::vector<Obstacle*> obstacles;
    double power;
    double temperature;
    std::vector<Bacterium*> annex;

    /**
     * @brief Suppression du Constructeur de copie pour empêcher la copie de l'assiette de Petri
     */
    PetriDish(PetriDish const&) = delete;

    /**
     * @brief Suppression de l'operator = pour empêcher l'usage de l'opérateur d'affectation
     */
    PetriDish& operator=(PetriDish const&) = delete;

    /**
     * @brief getMeanBacteria Calcule la moyenne des valeurs d'un paramètre mutable sur toutes les bactéries
     * possédant ce paramètre mutable
     * @param s Nom du paramètre mutable
     * @return La moyenne calculée
     */
    double getMeanMutableParam(const std::string& s) const;

    /**
     * @brief getTotalNutriment Calcule la somme de toutes les quantités de nutriments présents dans l'assiette de Petri
     * @return La somme totale
     */
    double getTotalNutriment() const;

    /**
     * @brief getMeanDivisionBacteria Calcule la proportion de bactérie issues d'une division parmi l'ensemble des bactéries
     * @return Le rapport calculé
     */
    double getMeanDivisionBacteria() const;

    /**
     * @brief updateBacteries Assure le déplacement, les collisions et la consommation des nutriments pour toutes les
     * bacteries de l'assiette de petri
     * @param dt Pas de temps après lequel la petri est mise à jour
     */
    void updateBacteries(sf::Time dt);

    /**
     * @brief updateNutriments Effectue la croissance de tous les nutriments de l'assiette de Petri en mettant à jour leur
     * quantité et leur rayon
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void updateNutriments (sf::Time dt);

    /**
     * @brief initAnnex Initialise le vecteur annexe de l'assiette de Petri à un vecteur vide
     */
    void initAnnex();

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres associée à l'assiette de Petri
     * @return la valeur de getAppConfig()["petri dish"]
     */
    j::Value const& getConfig() const;

    /**
     * @brief updateSwarms Mise à jour du vecteur de Swarm de l'assiette de Petri
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void updateSwarms(sf::Time dt);

    /**
     * @brief deleteUnderObstacle Supprime toutes les bacteries et tous les nutriments se trouvant en contact avec
     * l'obstacle passé en paramètre
     * @param obstacle
     */
    void deleteUnderObstacle(Obstacle* obstacle);
};


