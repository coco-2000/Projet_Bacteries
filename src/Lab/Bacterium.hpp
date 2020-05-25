#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Utility/MutableColor.hpp"
#include "Utility/Types.hpp"

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
     * @param energy Niveau d'énergie intiale de la bacterie
     * @param color Couleur initiale de la bacterie
     * @param paramMutables Ensemble de paramètres numériques mutables
     * @param abstinence Indique si la bacterie consomme des nutriments ou non
     */
    Bacterium(const Vec2d& position, const Vec2d& direction, double radius, Quantity energy,
              const MutableColor& color, const std::map<std::string, MutableNumber>& paramMutables = {},
              bool abstinence = 0);

    /**
     * @brief alive Permet de savoir si la bacterie a suffisamment d'energie pour être en vie
     * @return vrai si l'énergie est strictement supérieur à 0
     */
    bool alive() const;

    /**
     * @brief drawOn Dessine la bacterie
     * @param target Fenêtre dans laquelle la bacterie est affichée
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief update gère le déplacement des bacteries,
     * les collisions avec le bord de l'assiette de petri
     * la consommation des nutriments par les bacteries
     * la division des bactéries
     * met à jour l'angle de rotation des bactéries
     * gère le mode perdu des bactéries
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief setScore Manipulateur du score
     * @param  Score à assigner à l'attribut oldScore
     *         (score avant mise à jour) de l'instance courante
     */
    void setScore(double score);

    /**
     * @brief getParamMutables
     * @return l'ensemble des paramètres mutables de la bactérie
     */
    std::map<std::string, MutableNumber> getparamMutables() const;

    /**
     * @brief getMaxEatableQuantity
     * @return la quantité maximale pouvant être prélevé par la bactérie sur la source de nutriment
     */
    Quantity getMaxEatableQuantity() const;

    /**
     * Méthode virtuelle pure
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentA qui prend pour argument une bactérie dont le type
     * correspond à celui de l'instance courante de bactérie)
     * @param nutriment de type A qui est consommé par la bactérie
     * @return La quantité de nutriment consommée
     */
    virtual Quantity eatableQuantity(NutrimentA& nutriment) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du nutrimentB qui prend pour argument une bactérie dont le type
     * correspond à celui de l'instance courante de bactérie)
     * @param nutriment de type B qui est consommé par la bactérie
     * @return La quantité de nutriment consommée
     */
    virtual Quantity eatableQuantity(NutrimentB& nutriment) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief eatableQuantity Calcul la quantité de nutriment consommé par la bactérie et
     *                        retire cette quantité au nutriment
     * (appelle la méthode eatenBy du poison qui prend pour argument une bactérie dont le type
     * correspond à celui de l'instance courante de bactérie)
     * @param nutriment de type poison qui est consommé par la bactérie
     * @return La quantité de poison consommée
     */
    virtual Quantity eatableQuantity(Poison& poison) const = 0;

    /**
     * @brief isLost
     * @return vrai si la bactérie et perdue, c'est-à-dire qu'elle a percuté un obstacle ou
     * le bord il a peu de temps et est ainsi étourdie par le choc
     */
    bool isLost() const;

    /**
     * @brief getDivideEnergy
     * @return l'énergie minimale nécessaire à la division
     */
    Quantity getDivideEnergy() const;

    /**
     * @brief getEnergy
     * @return L'énergie de l'instance courante de bactérie
     */
    Quantity getEnergy() const;

    /**
     * Méthode virtuelle pure
     * @brief getScoreCoefficient Calcul le coefficient associé à un nutriment (ici de type A) pour le calcul du
     * score de la position en fonction du type de la bactérie
     * @return le coefficient par lequel est multiplié le score par rapport à une source de nutriments
     */
    virtual double getScoreCoefficient(const NutrimentA& nutriment) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief getScoreCoefficient Calcul le coefficient associé à un nutriment (ici de type B) pour le calcul du
     * score de la position en fonction du type de la bactérie
     * @return le coefficient par lequel est multiplié le score par rapport à une source de nutriments
     */
    virtual double getScoreCoefficient(const NutrimentB& nutriment) const = 0;

    /**
     * Méthode virtuelle pure
     * @brief getScoreCoefficient Calcul le coefficient associé à un nutriment (ici de type poison) pour le calcul du
     * score de la position en fonction du type de la bactérie
     * @return le coefficient par lequel est multiplié le score par rapport à une source de nutriments
     */
    virtual double getScoreCoefficient(const Poison& poison) const = 0;

    /**
     * @brief getDivideCounter
     * @return le nombre de divisions effectuées par la bactérie
     */
    unsigned int getDivideCounter() const;

protected :
    /**
     * @brief getAngle
     * @return L'angle de direction de la bactérie
     */
    double getAngle() const;

    /**
     * @brief getColor
     * @return La couleur de la bactérie
     */
    sf::Color getColor() const;

    /**
     * @brief getDirection
     * @return Le vecteur de direction de la bactérie
     */
    Vec2d getDirection() const;

    /**
     * @brief getOldScore
     * @return le score que la bactérie avait lors du pas de simulation précédent
     */
    double getOldScore() const;

    /**
     * @brief setDirection modifie le vecteur de direction de la bactérie
     * @param newDir nouvelle direction que la bactérie doit prendre
     */
    void setDirection(const Vec2d& newDir);

    /**
     * @brief move Méthode virtuelle pure de déplacement des bactéries
     * (à redéfinir dans les sous-classes)
     * @param dt Pas de temps depuis le dernier déplacement de l'instance courante
     */
    virtual void move(sf::Time dt) = 0;

    /**
     * @brief getStepEnergy
     * @return L'énergie dépensée à chaque pas de déplacement
     */
    virtual Quantity getStepEnergy() const;

    /**
     * @brief consumeEnergy Décremente le niveau d'énergie
     * @param qt Quantité d'énergie retirée à la bactérie
     */
    void consumeEnergy(Quantity qt);

    /**
     * @brief shiftClone Décale la bactérie clonée pour la différencier de la bactérie d'origine
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
     * (associé à l'étiquette "single random vector" dans le fichier de configuration)
     */
    void strategy1();

    /**
     * @brief strategy2 Deuxième façon d'effectuer le basculement : Générer N direction et retenir celle qui a le meilleur score
     * (associé à l'étiquette "best of N" dans le fichier de configuration)
     */
    void strategy2();

    /**
     * @brief consumeNutriment gère la consommation des bacteries
     * @param dt Pas de temps après lequel la bactérie est mise à jour
     */
    virtual void consumeNutriment(sf::Time dt);

    /**
     * @brief getTimeSwitch
     * @return Le temps depuis lequel la bactérie n'a pas basculé
     */
    sf::Time getTimeSwitch() const;

    /**
     * @brief setTimeSwitch
     * @param newTime Temps a assigner à l'attribut timeSwitch
     */
    void setTimeSwitch(sf::Time newTime);

    /**
     * @brief getLostEnergyFactor
     * @return L'énergie dépensée à chaque pas de déplacement lorsque la bactérie est
     * lost (perdue), c'est-à-dire qu'elle a percuté un obstacle ou le bord il y a peu de temps
     * et est ainsi étourdie par le choc
     */
    double getLostEnergyFactor() const;

    /**
     * @brief setLost Modifie l'attribut lost
     * @param islost la nouvelle valeur de lost et initialise timeLost à 0
     */
    void setLost(bool islost);

    /**
     * @brief lostTrySwitch Calcul la probabilité pour l'instance courante de bactérie de basculer
     * si elle est perdue et effectue le basculement
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void lostTrySwitch(sf::Time dt);

    /**
     * @brief manageLost Vérifie si le délai pour être perdue est dépassé, met l'attribut lost à false
     * (la bactérie n'est plus perdue) et met à jour timeLost
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    virtual void manageLost(sf::Time dt);

private :

    MutableColor color;
    double angle;
    Vec2d direction;
    Quantity energy;
    std::map<std::string, MutableNumber> paramMutables;
    bool abstinence;
    double oldScore;
    bool lost;
    unsigned int divideCounter;
    sf::Time consumeCounter;
    sf::Time timeLost;
    sf::Time timeSwitch;

    /**
     * (Méthode virtuelle pure)
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux bacteries
     * @return L'ensemble des paramètres du fichier app.json associé au type de l'instance courante
     */
    virtual j::Value const& getConfig() const = 0;

    /**
     * @brief getMaxTimeLost
     * @return Le temps maximal pendant lequel une bactérie est perdue,
     * c'est-à-dire qu'elle a percuté un obstacle ou le bord il a peu de temps
     * et est ainsi étourdie par le choc
     */
    sf::Time getMaxTimeLost() const;

    /**
     * @brief displayEnergy Affiche la quantité d'énergie de la bacterie (si mode debugging activé)
     * @param target Cible pour l'affichage
     */
    void displayEnergy(sf::RenderTarget& target) const;

    /**
     * @brief collision Gère les collisions des bacteries avec le bord de l'assiette et les obstacles
     */
    void collision();

    /**
     * @brief divide Méthode de division commune à toutes les bactéries
     * Si les conditions de division sont remplies, créé une nouvelle bactérie clonée,
     * divise par 2 l'énergie de la bactérie d'origine et de celle clonée,
     * modifie la direction de déplacement de la bactérie d'origine
     * et effectue des mutations sur la bacterie clonée
     */
    void divide();

    /**
     * (Méthode virtuelle pure)
     *  @brief clone Réalise une copie polymorphique de la bacterie.
     * @return Un pointeur sur la nouvelle bactérie issue de l'instance courante
     */
    virtual Bacterium* clone() const = 0;

    /**
     * @brief getDelay
     * @return Le temps d'attente entre deux consommations de nutriments pour la bactérie
     */
    sf::Time getDelay() const;

    /**
     * @brief rotationAngle Mise à jour de l'angle de rotation
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

    /**
     * @brief getLostLambdaSwitch
     * @return Le facteur lambda du fichier de configuration qui paramètrise la probabilité
     *         pour la bactérie de basculer quand elle est perdue
     */
    double getLostLambdaSwitch() const;

    /**
     * @brief manageGap Gère les cas où la bactérie qui percute le bord de l'assiette va un peu
     * trop loin et chavauche le bord
     */
    void manageGap();
};


