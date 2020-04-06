#pragma once
#include "Bacterium.hpp"
#include "../Utility/DiffEqSolver.hpp"

class SimpleBacterium : public Bacterium
{
public:
    /**
     * @brief SimpleBacterium Constructeur
     * @param position Coordonnées de la position de l'instance à créer
     */
    SimpleBacterium(const Vec2d& position);

    /**
     * @brief SimpleBacterium Constructeur
     * @param energie Niveau d'énergie intial de la bacterie
     * @param position Coordonnées de la position intiale de la bacterie
     * @param direction Direction du déplacement initiale de la bacterie
     * @param radius Rayon initial de la bactérie
     * @param couleur Couleur initiale de la bacterie
     * @param param_mutables Ensemble de paramètres numériques mutables
     * @param abstinence Si la bacterie consomme des nutriments ou non
     */
    SimpleBacterium(Quantity energie, Vec2d position, Vec2d direction,
                    double radius, const MutableColor& couleur,
                    std::map<std::string, MutableNumber> param_mutables,
                    bool abstinence);

    /**
     * @brief getSpeedVector Permet d'accéder au vecteur de vitesse qui détermine
     *                       le déplacement de la bactérie
     * @return Le vecteur vitesse calculé en fonction de la direction et des
     *         paramètres relatifs à la vitesse de la bactérie
     */
    Vec2d getSpeedVector() const;

    void drawOn(sf::RenderTarget& target) const override;

private :
    MRU equation;
    double t;
    sf::Time tps_basculement;

    /**
     * @brief graphisme_particulier Permet d'ajouter des détails graphiques spécifiques aux bactéries simples
     * @param target Cible pour l'affichage
     */
    void graphisme_particulier(sf::RenderTarget& target) const;

    /**
     * @brief tentative_basculement Décide si la bactérie doit basculer ou non
     */
    void tentative_basculement() override;

    /**
     * @brief basculement effectue le basculement de l'instance courante
     */
    void basculement();

    /**
     * @brief strategie1 Première façon d'effectuer le basculement : choisir au hasard une direction
     * associer à l'étiquette "single random vector" dans le fichier de configuration
     */
    void strategie1();

    /**
     * @brief strategie2 Deuxième façon d'effectuer le basculement :
     * Générer N direction et retenir celle qui a le meilleur score
     * associer à l'helperétiquette "best of N" dans le fichier de configuration
     */
    void strategie2();

    double helperPositionScore (const Vec2d& offset);

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries simples
     * @return La valeur associée à getAppConfig()["simple bacterium"]
     */
    j::Value const& getConfig() const override;

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief move Déplace une bactérie
     * @param dt Pas de temps depuis le dernier déplacement de l'instance courante
     */
    void move(sf::Time dt) override;

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief copie Effectue la copie d'une instance avec tous ses attributs
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */
    SimpleBacterium* clone() const override;

};
