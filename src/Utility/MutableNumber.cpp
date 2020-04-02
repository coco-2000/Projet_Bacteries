#include "MutableNumber.hpp"

MutableNumber::MutableNumber(double value,
              double mutate_proba,
              double ecart_type,
              bool hasMin,
              bool hasMax,
              double Min,
              double Max)
    : mutation_proba(mutate_proba),
      EcartType(ecart_type),
      hasMin_(hasMin),
      Min_(Min),
      hasMax_(hasMax),
      Max_(Max)
{
    set(value);
}

MutableNumber::MutableNumber(j::Value const& config)
    : MutableNumber(config["initial"].toDouble(),
      config["rate"].toDouble(),
      config["sigma"].toDouble(),
      config["clamp min"].toBool(),
      config["clamp max"].toBool(),
      config["min"].toDouble(),
      config["max"].toDouble())
{}

double MutableNumber::get() const
{
    return valeur;
}

void MutableNumber::set(double value)
{
    if((!hasMin_ or value > Min_) and (!hasMax_ or value < Max_))
    {
        valeur = value;
    }
    else if(hasMin_)
    {
        valeur = Min_;
    }
    else {valeur = Max_;}
}

void MutableNumber::mutate()
{
    if(bernoulli(mutation_proba))
    {
        set(valeur + normal(0, EcartType*EcartType));
    }
}

MutableNumber MutableNumber::probability(double initialValue,
                          double mutationProbability,
                          double sigma)
{
    return MutableNumber (initialValue,
                          mutationProbability,
                          sigma,
                          true, 0,
                          true, 1);
}

MutableNumber MutableNumber::probability(j::Value const& config)
{
    return probability(config["initial"].toDouble(),
                       config["rate"].toDouble(),
                       config["sigma"].toDouble());
}
MutableNumber MutableNumber::positive(double initialValue,
                       double mutationProbability,
                       double sigma,
                       bool hasMax,
                       double max)
{
    return MutableNumber(initialValue,
                         mutationProbability,
                         sigma,
                         true, 0,
                         hasMax, max);
}

MutableNumber MutableNumber::positive(j::Value const& config,
                                      bool hasMax, double max)
{
    return positive(config["initial"].toDouble(),
                    config["rate"].toDouble(),
                    config["sigma"].toDouble(),
                    hasMax, max);
}
