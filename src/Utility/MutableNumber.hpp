#pragma once
#include "Random/Random.hpp"

class MutableNumber
{
public:
    MutableNumber(double, double, double, bool, bool, double, double);
    MutableNumber(j::Value const& config);
    double get() const;
    void set(double value);
    void mutate();

private :
    double valeur;
    double mutation_proba;
    double EcartType;
    bool aBorneInf;
    bool aBorneSup;
    double BorneInf;
    double BorneSup;
};
