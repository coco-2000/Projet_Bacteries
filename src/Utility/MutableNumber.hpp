#pragma once
#include "Random/Random.hpp"

class MutableNumber
{
public:
    /**
     * @brief MutableNumber Constructeur
     * @param value valeur du MutableNumber (qui est un nombre)
     * @param rate Probabilité de mutation
     * @param sigma Ecart type permettant la modification aléatoire de la valeur du nombre
     * @param hasMin Indique si le nombre a une borne inférieure
     * @param min Borne inférieure
     * @param hasMax Indique si le nombre a une borne superieure
     * @param max Borne supérieure
     */
    MutableNumber(double value,
                  double rate,
                  double sigma,
                  bool hasMin = false,
                  double min = 0,
                  bool hasMax = false,
                  double max = 0);

    /**
     * @brief MutableNumber Constructeur
     * @param config Entrée du fichier de configuration depuis laquelle on prend les paramètres
     */
    MutableNumber(j::Value const& config);

    /**
     * @brief get Accesseur du nombre
     * @return La valeur du MutableNumber (qui est un nombre)
     */
    double get() const;

    /**
     * @brief set Manipulateur de la valeur
     * (vérifie le plafonnage de la valeur entre la borne inférieure et la borne supérieure si elles existent)
     * @param value Valeur à attribuer au nombre
     */
    void set(double value);

    /**
     * @brief mutate Modifie la valeur du nombre de façon aléatoire
     */
    void mutate();

    /**
     * @brief probability Génère un MutableNumber de type probabilité (valeurs plafonnées entre 0 et 1)
     * @param initialValue Valeur du MutableNumber (qui est un nombre)
     * @param rate Probabilité de mutation
     * @param sigma Ecart type permettant la modification aléatoire de la valeur du nombre
     * @return Le MutableNumber généré à partir des paramètres passés en argument
     */
    static MutableNumber probability(double initialValue, double rate, double sigma);

    /**
     * @brief probability Génère un MutableNumber de type probabilité (valeurs plafonnées entre 0 et 1)
     * @param config Entrée du fichier de configuration depuis laquelle on prend les paramètres
     * @return Le MutableNumber généré à partir des paramètres du fichier de configuration
     */
    static MutableNumber probability(j::Value const& config);

    /**
     * @brief positive Génère un MutableNumber de type positif (valeurs minimale plafonnée à zéro)
     * @param initialValue Valeur du MutableNumber (qui est un nombre)
     * @param rate Probabilité de mutation
     * @param sigma Ecart type permettant la modification aléatoire de la valeur du nombre
     * @param hasMax Indique si le nombre a une borne superieure
     * @param max Borne supérieure
     * @return Le MutableNumber généré à partir des paramètres passés en argument
     */
    static MutableNumber positive(double initialValue,
                                  double rate,
                                  double sigma,
                                  bool hasMax = false,
                                  double max = 0);

    /**
     * @brief positive Génère un MutableNumber de type positif (valeurs minimale plafonnée à zéro)
     * @param config Entrée du fichier de configuration depuis laquelle on prend les paramètres
     * @param hasMax Indique si le nombre a une borne superieure
     * @param max Borne supérieure
     * @return Le MutableNumber généré à partir des paramètres du fichier de configuration et de la borne passée en argument
     */
    static MutableNumber positive(j::Value const& config,
                                  bool hasMax = false,
                                  double max = 0);

private :
    double value;
    double rate;
    double sigma;
    bool hasMin;
    double min;
    bool hasMax;
    double max;
};


