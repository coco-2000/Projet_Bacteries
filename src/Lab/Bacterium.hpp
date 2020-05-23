#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Utility/MutableColor.hpp"
#include <SFML/Graphics.hpp>
#include "Utility/Types.hpp"
#include <string>
#include <functional>

class Nutriment;
class NutrimentA;
class NutrimentB;
class Poison;

class Bacterium : public CircularBody, public Drawable, public Updatable
{
public :
    /**
     * @brief Bacterium Constructeur
     * @param position Coordonnées de la position intiale de la bacterie
     * @param direction Direction du déplacement initiale de la bacterie
     * @param radius Rayon initiale de la bactérie
     * @param energy niveau d'énergie intiale de la bacterie
     * @param color Couleur initiale de la bacterie
     * @param paramMutables ensemble de paramètres numériques mutables
     * @param abstinence si la bacterie consomme des nutriments ou non
     */
    Bacterium(const Vec2d& position, const Vec2d& direction, double radius, Quantity energy,
              const MutableColor& color, const std::map<std::string, MutableNumber>& paramMutables = {},
              bool abstinence = 0);

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
     * @brief getParamMutables
     * @return l'ensemble des paramètres mutables de la bactérie
     */
    std::map<std::string, MutableNumber> getparamMutables() const;

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
    virtual Quantity eatableQuantity(NutrimentA& nutriment) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie dont le type
     * correspond à celui de l'instance courante de bactérie)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommé
     */
    virtual Quantity eatableQuantity(NutrimentB& nutriment) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du poison qui prend pour argument une bactérie dont le type
     * correspond à celui de l'instance courante de bactérie)
     * @param nutriment de type poison qui est consommé par la bactérie
     * @return La quantité de poison consommé
     */
    virtual Quantity eatableQuantity(Poison& poison) const = 0;

    bool isLost() const;

   /* virtual double getMaxpHviable() const = 0;
    virtual double getMinpHviable() const = 0;
    virtual double getMaxTemperatureViable() const =0;
    virtual double getMinTemperatureViable() const =0;
    virtual double getHeatResistanceEnergy() const = 0;
    virtual double getpHResistanceEnergy() const = 0;
    bool TemperatureViable() const;
    bool pHviable() const; */

    /**
     * Méthode virtuelle pure
     * @brief getPositionScore Calcul le coefficient associé à un nutriment (ici de type A) pour le calcul du
     * score de la position en fonction du type de la bactérie
     * @return le coefficient par lequel est multiplié le score par rapport à une source de nutriments
     */
    virtual double getScoreCoefficient(const NutrimentA& nutriment) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief getPositionScore Calcul le coefficient associé à un nutriment (ici de type B) pour le calcul du
     * score de la position en fonction du type de la bactérie
     * @return le coefficient par lequel est multiplié le score par rapport à une source de nutriments
     */
    virtual double getScoreCoefficient(const NutrimentB& nutriment) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief getPositionScore Calcul le coefficient associé à un nutriment (ici de type poison) pour le calcul du
     * score de la position en fonction du type de la bactérie
     * @return le coefficient par lequel est multiplié le score par rapport à une source de nutriments
     */
    virtual double getScoreCoefficient(const Poison& poison) const = 0;

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
     * @param newDir nouvelle direction que la bactérie doit prendre
     */
    void setDirection(const Vec2d& newDir);

    /**
     * @brief move Méthode virtuelle pure de déplacement des bactéries
     * (à redéfinir dans les sous-classes)
     * @param dt Pas de temps depuis le dernier déplacement de
     * l'instance courante
     */
    virtual void move(sf::Time dt) = 0;

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
     * @brief getProperty Accesseur d'un paramètre mutable
     * @param key Clé (=nom) du paramètre mutable à renvoyer
     * @return La valeur, sous forme de MutableNumber, du paramètre associé à la clé
     */
    MutableNumber getProperty(const std::string& key) const;

    /**
     * @brief strategy1 Première façon d'effectuer le basculement : choisir au hasard une direction
     * associer à l'étiquette "single random vector" dans le fichier de configuration
     */
    void strategy1();

    /**
     * @brief strategy2 Deuxième façon d'effectuer le basculement :
     * Générer N direction et retenir celle qui a le meilleur score
     * associer à l'helperétiquette "best of N" dans le fichier de configuration
     */
    void strategy2();

    /**
     * @brief consumeNutriment gère la consommation des bacteries
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    virtual void consumeNutriment(sf::Time dt);

    double getLostEnergyFactor() const;

    double getLostLambdaSwitch() const;

    sf::Time getMaxTimeLost() const;

    sf::Time getTimeSwitch() const;

    void setTimeSwitch(sf::Time newTime);

    virtual void manageLost(sf::Time dt);

    void setLost(bool islost);

    void lostTrySwitch(sf::Time dt);



private :
    MutableColor color;
    double angle;
    Vec2d direction;
    Quantity energy;
    std::map<std::string, MutableNumber> paramMutables;
    bool abstinence;
    sf::Time consumeCounter;
    double oldScore;
    bool lost;
    sf::Time timeLost;
    sf::Time timeSwitch;

    /**
     * @brief displayEnergy Affiche la quantité d'énergie de la bacterie (si mode debugging activé)
     * @param target Cible pour l'affichage
     */
    void displayEnergy(sf::RenderTarget& target) const;

    /**
     * @brief collision gère les collisions des bacteries
     * avec l'assiette de petri
     */
    void collision();

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
     * @brief rotationAngle mise à jour de l'angle de rotation
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void rotationAngle(sf::Time dt);

    /**
     * @brief eat Gère la consommation de nutriment par la bactérie (en fonction du type du nutriment et de la bactérie) :
     *            -> calcul la quantité consommée par bactérie et la retire de la source de nutriment
     * @param nutriment qui est consommé par l'instance
     */
    void eat(Nutriment& nutriment);

    /**
     * @brief mutate Méthode de mutation d'une bactérie
     */
    virtual void mutate();

    /**
     * @brief addProperty Ajoute à l'ensemble des paramètres mutables numériques de la bactérie une valeur numérique mutable donnée
     * @param key Clé (=nom) du paramètre mutable à ajouter
     * @param value Valeur associée à la clé, sous forme de MutableNumber
     */
    void addProperty(const std::string& key, const MutableNumber& value);

    /**
     * @brief helperPositionScore Calcul le score de la position de l'instance + un vecteur
     * @param offset Vecteur a ajouter à la position
     * @param bacterie Instance courante dont on calcule le score
     * @return Score associé à la nouvelle position
     */
    double helperPositionScore(const Vec2d& offset, const Bacterium& bacterie) const;

    /**
     * @brief operator = empecher l'usage de l'opérateur d'affectation car il n'est pas utilisé
     * et afin d'éviter d'avoir à le redéfinir dans les sous classes de bactérium lorsque le
     * constructeur de copie est redéfini pour incrémenter les compteurs par exemple
     */
    Bacterium& operator=(Bacterium const&) = delete;
};


