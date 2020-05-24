#pragma once
#include "Bacterium.hpp"
#include "../Utility/DiffEqSolver.hpp"

class SwimmingBacterium : public Bacterium, public DiffEqFunction
{
public:
    /**
     * @brief SwimmingBacterium Constructeur
     * @param position Coordonnées de la position intiale de la bacterie
     * @param direction Direction du déplacement initiale de la bacterie
     * @param radius Rayon initiale de la bactérie
     * @param energy Niveau d'énergie intiale de la bacterie
     * @param color Couleur initiale de la bacterie
     * @param paramMutables Ensemble de paramètres numériques mutables
     * @param abstinence Indique si la bacterie consomme des nutriments ou non
     */
    SwimmingBacterium(const Vec2d& position, const Vec2d& direction, double radius,
                       Quantity energy, const MutableColor& color,
                       const std::map<std::string, MutableNumber>& paramMutables = {},
                       bool abstinence = 0);

    /**
     * @brief SwimmingBacterium Constructeur de copie
     * Incrémente le compteur d'instances
     * @param other SwimmingBacterium à copier
     */
    SwimmingBacterium(const SwimmingBacterium& other);

protected :
    /**
     * @brief move Déplace la bactérie
     * @param dt Pas de temps depuis le dernier déplacement de l'instance courante
     */
    void move(sf::Time dt) override;

    /**
     * @brief consumeNutriment gère la consommation des bacteries
     * @param dt Pas de temps après lequel la bactérie est mise à jour
     */
    //void consumeNutriment(sf::Time dt) override;

    /**
     * @brief manageLost Vérifie si le délai pour être perdue est dépassé, met l'attribut lost à false
     * (la bactérie n'est plus perdue) et met à jour timeLost
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    //void manageLost(sf::Time dt) override;

private :
    double timeFlagellum;

    /**
     * @brief drawOn Dessine la bactérie et ajoute une flagelle à l'arrière de celle-ci
     * @param target Cible pour l'affichage
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief trySwitch Décide si la bactérie doit basculer ou non et le fait da
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void trySwitch(sf::Time dt);

    /**
     * @brief switchDirection Effectue le basculement de l'instance courante
     */
    void switchDirection();

    /**
     * @brief f Calcul le vecteur force déterminant le déplacement de la bactérie
     * Ici la force est nulle ce qui assure un mouvement rectiligne uniforme
     * @param position Position de l'instance courante /inutilisé
     * @param speed Vitesse de l'instance coiurante /inutilisé
     * @return Le vecteur force appliqué à la bactérie simple, le vecteur nul
     */
    Vec2d f(Vec2d position, Vec2d speed) const override;

    /**
     * @brief getSpeedVector Permet d'accéder au vecteur de vitesse qui détermine
     *                       le déplacement de la bactérie
     * @return Le vecteur vitesse calculé en fonction de la direction et des
     *         paramètres relatifs à la vitesse de la bactérie
     */
    Vec2d getSpeedVector() const;

};
