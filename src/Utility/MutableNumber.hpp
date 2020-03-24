#pragma once
#include "Random/Random.hpp"

class MutableNumber
{
public:
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
