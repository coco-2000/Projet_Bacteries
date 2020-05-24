#pragma once
#include "Bacterium.hpp"
#include "../Utility/DiffEqSolver.hpp"

class SimpleBacterium : public Bacterium, public DiffEqFunction
{
public:
    /**
     * @brief SimpleBacterium Constructeur
     * Incrémente le compteur d'instances
     * @param position Coordonnées de la position de l'instance à créer
     */
    SimpleBacterium(const Vec2d& position);

    SimpleBacterium(const Vec2d& position, const Vec2d& direction, double radius,
                    Quantity energie, const MutableColor& couleur,
                    const std::map<std::string, MutableNumber>& param_mutables = {},
                    bool abstinence = 0);

    /**
     * @brief SimpleBacterium constructeur de copie
     * Incrémente le compteur d'instances
     * @param other SimpleBacterium à copier
     */
    SimpleBacterium(const SimpleBacterium& other);

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie simple)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentA& nutriment) const override;

    /**
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie simple)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    Quantity eatableQuantity(NutrimentB& nutriment) const override;

    Quantity eatableQuantity(Poison& poison) const override;

    double getScoreCoefficient(const NutrimentA& nutriment) const override;

    double getScoreCoefficient(const NutrimentB& nutriment) const override;

    double getScoreCoefficient(const Poison& poison) const override;

    /**
     * @brief ~SimpleBacterium Destructeur
     * Décrémente le compteur d'instances
     */
    ~SimpleBacterium() override;

    /**
     * @brief getSimpleCounter compte le nombre total d'instances de SimpleBacterium présentes
     * dans l'assiette de Pétri
     * @return le nombre total d'instances
     */
    static unsigned int getSimpleCounter();

protected :

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief move Déplace une bactérie
     * @param dt Pas de temps depuis le dernier déplacement de l'instance courante
     */
    void move(sf::Time dt) override;

    void consumeNutriment(sf::Time dt) override;
    void manageLost(sf::Time dt) override;


private :
    double timeFlagellum;
    static unsigned int simpleCounter;

    /**
     * @brief drawOn Permet d'ajouter des détails graphiques spécifique
     * aux bactéries simples
     * @param target Cible pour l'affichage
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief tentative_basculement Décide si la bactérie doit basculer ou non
     * @param dt Pas de temps au bout duquel la simulation est mise à jour
     */
    void trySwitch(sf::Time dt);

    /**
     * @brief switchDirection effectue le basculement de l'instance courante
     */
    void switchDirection();

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries simples
     * @return La valeur associée à getAppConfig()["simple bacterium"]
     */
    j::Value const& getConfig() const override;

    /**
     * Redéfinition d'une méthode virtuelle pure
     * @brief clone Effectue la copie d'une instance avec tous ses attributs
     * @return Un pointeur sur la nouvelle bactérie copiée de l'instance courante
     */
    SimpleBacterium* clone() const override;

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
