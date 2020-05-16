#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Utility/MutableColor.hpp"
#include <SFML/Graphics.hpp>
#include "Utility/Types.hpp"
#include <string>

class Nutriment;
class NutrimentA;
class NutrimentB;

class Bacterium : public CircularBody, public Drawable, public Updatable
{
public :
    /**
     * @brief Bacterium Constructeur
     * @param energie niveau d'énergie intiale de la bacterie
     * @param position Coordonnées de la position intiale de la bacterie
     * @param direction Direction du déplacement initiale de la bacterie
     * @param radius Rayon initiale de la bactérie
     * @param couleur Couleur initiale de la bacterie
     * @param param_mutables ensemble de paramètres numériques mutables
     * @param abstinence si la bacterie consomme des nutriments ou non
     */
    Bacterium(Quantity energy, const Vec2d& position, const Vec2d& direction,
              double radius, const MutableColor& color,
              const std::map<std::string, MutableNumber>& paramMutables = {},
              bool abstinence = 0);

    /**
     * @brief operator = empecher l'usage de l'opérateur d'affectation car il n'est pas utilisé
     * et afin d'éviter d'avoir à le redéfinir dans les sous classes de bactérium lorsque le
     * constructeur de copie est redéfini pour incrémenter les compteurs par exemple
     */
    Bacterium& operator=(Bacterium const&) = delete;

    /**
     * @brief alive savoir si la bacterie a suffisamment d'energie pour etre en vie
     * @return vrai si l'energie est suffisante
     */
    bool alive() const;

    /**
     * @brief drawOn dessiner la bacterie
     * @param target la fenetre dans laquelle on affiche la bacterie
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief update gère le déplacement des bacteries,
     * les collisions avec le bord de l'assiette de petri
     * la consommation des nutriments par les bacteries
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief setScore Manipulateur du score
     * @param score Score à assigner à l'attribut ancien_score
     *              (score avant mise à jour) de l'instance courante
     */
    void setScore(double score);

    /**
     * @brief getParam_mutables
     * @return l'ensemble des paramètres mutables de la bactérie
     */
    std::map<std::string, MutableNumber> getParam_mutables() const;

    /**
     * @brief getMaxEatableQuantity
     * @return la quantité maximale pouvant être prélevé par la bactérie sur le source de nutriment
     */
    Quantity getMaxEatableQuantity() const;

    /**
     * Méthode virtuelle pure
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie dont le type
     * correspond à celui de l'instance courante de bactérie)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    virtual Quantity eatableQuantity(NutrimentA& nutriment) = 0;

    /**
     * Méthode virtuelle pure
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie dont le type
     * correspond à celui de l'instance courante de bactérie)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    virtual Quantity eatableQuantity(NutrimentB& nutriment) = 0;

protected :
    /**
     * @brief getAngle
     * @return l'angle de direction de la bactérie
     */
    double getAngle() const;

    /**
     * @brief getColor
     * @return la couleur de la bactérie
     */
    sf::Color getColor() const;

    /**
     * @brief getDirection
     * @return la direction de la bactérie
     */
    Vec2d getDirection() const;

    /**
     * @brief getOldScore
     * @return le score de la bactérie lors du pas de simulation
     * précédent
     */
    double getOldScore() const;

    /**
     * @brief setDirection modifie la direction de la bactérie
     * @param new_dir nouvelle direction que la bactérie doit prendre
     */
    void setDirection(const Vec2d& new_dir);

    /**
     * @brief move Méthode virtuelle pure de déplacement des bactéries
     * (à redéfinir dans les sous-classes)
     * @param dt Pas de temps depuis le dernier déplacement de
     * l'instance courante
     */
    virtual void move(sf::Time dt) = 0;

    /**
     * @brief mutate Méthode de mutation d'une bactérie
     */
    virtual void mutate();

    /**
     * @brief getStepEnergy
     * @return l'énergie dépensée à chaque pas de déplacement
     */
    virtual Quantity getStepEnergy() const;

    /**
     * @brief consumeEnergy décrémenter le niveau d'énergie
     * @param qt la quantité pour laquelle l'énergie est décrémentée
     */
    void consumeEnergy(Quantity qt);

    /**
     * @brief shift_clone décale la bactérie clonée pour la différencier de la bactérie d'origine
     * @param v vecteur avec lequel la bactérie est décalée
     */
    virtual void shiftClone(const Vec2d& v);

    /**
     * @brief addProperty Ajoute à l'ensemble des paramètres mutables numériques de la bactérie une valeur numérique mutable donnée
     * @param key Clé (=nom) du paramètre mutable à ajouter
     * @param valeur Valeur associée à la clé, sous forme de MutableNumber
     */
    void addProperty(const std::string& key, const MutableNumber& valeur);

    /**
     * @brief getProperty Accesseur d'un paramètre mutable
     * @param key Clé (=nom) du paramètre mutable à renvoyer
     * @return La valeur, sous forme de MutableNumber, du paramètre associé à la clé
     */
    MutableNumber getProperty(const std::string& key) const;

    /**
     * @brief helperPositionScore Calcul score de la position de l'instance + un vecteur
     * @param offset Vecteur a ajouter à la position
     * @return Score associé à la nouvelle position
     */
    double helperPositionScore(const Vec2d& offset) const;

private :
    MutableColor color;
    double angle;
    Vec2d direction;
    Quantity energy;
    std::map<std::string, MutableNumber> paramMutables;
    bool abstinence;
    sf::Time counter;
    double oldScore;

    /**
     * @brief DisplayEnergy Affiche la quantité d'énergie de la bacterie (si mode debugging activé)
     * @param target Cible pour l'affichage
     */
    void displayEnergy(sf::RenderTarget& target) const;

    /**
     * @brief collisionPetri gère les collisions des bacteries
     * avec l'assiette de petri
     */
    void collisionPetri();

    /**
     * @brief divide Méthode de division commune à toutes les bactéries
     * Si les conditions de division sont remplies, créé une nouvelle bactérie clonée,
     * divise par 2 l'énergie de la bactérie d'origine et de celle clonée,
     * inverse la direction de déplacement de la bactérie d'origine et effectue des mutations
     * sur la bacterie clonée
     */
    void divide();

    /**
     * @brief clone réalise une copie polymorphique de la bacterie. Méthode virtuelle pure
     * @return Un pointeur sur la nouvelle bactérie issue de l'instance courante
     */
    virtual Bacterium* clone() const = 0;

    /**
     * @brief getEnergy
     * @return l'énergie minimale nécessaire à la division
     */
    Quantity getEnergy() const;

    /**
     * @brief getDelay
     * @return le temps d'attente entre deux consommations de nutriments pour la bactérie
     */
    sf::Time getDelay() const;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries
     * Il s'agit d'une méthode virtuelle pure
     * @return la valeur associée à getAppConfig()["bacterium"] du fichier json
     */
    virtual j::Value const& getConfig() const = 0;

    /**
     * @brief consumeNutriment gère la consommation des bacteries
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void consumeNutriment(sf::Time dt);

    /**
     * @brief rotationAngle mise à jour de l'angle de rotation
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void rotationAngle(sf::Time dt);

    /**
     * @brief eat Gère la consommation de nutriment par la bactérie (en fonction de du type de nutriment et de bactérie) :
     *            calcul quantité consommée par bactérie et la retire de la source de nutriment
     * @param nutriment qui est consommé par l'instance
     */
    void eat(Nutriment& nutriment);

};


