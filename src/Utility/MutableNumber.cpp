#include "MutableNumber.hpp"

MutableNumber::MutableNumber(double value,
              double mutate_proba,
              double ecart_type,
              bool a_borne_inf = false,
              bool a_borne_sup = false,
              double borne_inf = 0,
              double borne_sup = 0)
    : mutation_proba(mutate_proba),
      EcartType(ecart_type),
      aBorneInf(a_borne_inf),
      aBorneSup(a_borne_sup),
      BorneInf(borne_inf),
      BorneSup(borne_sup),
      set(value)
{}

MutableNumber::MutableNumber(j::Value const& config)
    : MutableNumber(config["initial"].toDouble(),
      config["rate"].toDouble(),
      config["sigma"].toDouble(),
      config["clamp min"].toBool(),
      config["clamp max"].toBool(),
      config["min"].toDouble(),
      config["max"].toDouble(),)
{}

double MutableNumber::get() const
{
    return valeur;
}
void MutableNumber::set(double value)
{
    if((!aBorneInf or value > BorneInf) and (!aBorneSup or value < BorneSup))
    {
        valeur = value;
    }
    else if(aBorneInf)
    {
        valeur = BorneInf;
    }
    else {valeur = BorneSup;}
}

void MutableNumber::mutate()
