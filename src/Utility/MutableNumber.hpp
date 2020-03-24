#pragma once
#include "Random/Random.hpp"

class MutableNumber
{
public:
    /**
     * @brief MutableNumber Constructeur de Classe
     * @param value valeur du MutableNumber (qui est un nombre)
     * @param mutate_proba Probabilité de mutation
     * @param ecart_type Ecart type permettant la modification aléatoire de la valeur du nombre
     * @param hasMin Indique si le nombre a une borne inférieure
     * @param Min Borne inférieure
     * @param hasMax Indique si le nombre a une borne inférieure
     * @param Max Borne supérieure
     */
    MutableNumber(double value,
                  double mutate_proba,
                  double ecart_type,
                  bool hasMin,
                  double Min,
                  bool hasMax,
                  double Max);


    MutableNumber(j::Value const& config);
    double get() const;
    void set(double value);
    void mutate();

private :
    double valeur;
    double mutation_proba;
    double EcartType;
    bool hasMin_;
    double Min_;
    bool hasMax_;
    double Max_;
};

MutableNumber probability(double initialValue, double mutationProbability, double sigma);
MutableNumber probability(j::Value const& config);
MutableNumber positive(double initialValue, double mutationProbability, double sigma, bool hasMax, double max);
MutableNumber positive(j::Value const& config, bool hasMax, double max);
