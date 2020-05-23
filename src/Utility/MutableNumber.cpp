#include "MutableNumber.hpp"

MutableNumber::MutableNumber(double value, double rate, double sigma,
                             bool hasMin, double min, bool hasMax, double max)
    : rate(rate), sigma(sigma), hasMin(hasMin), min(min), hasMax(hasMax), max(max)
{
    set(value);
}

MutableNumber::MutableNumber(j::Value const& config)
    : MutableNumber(config["initial"].toDouble(),
      config["rate"].toDouble(),
      config["sigma"].toDouble(),
      config["clamp min"].toBool(),
      config["min"].toDouble(),
      config["clamp max"].toBool(),
      config["max"].toDouble())
{}

double MutableNumber::get() const
{
    return value;
}

void MutableNumber::set(double val)
{
    if((!hasMin or val > min) and (!hasMax or val < max))
    {
        value = val;
    }
    else if(hasMin and val < min)
    {
        value = min;
    }
    else
    {
        value = max;
    }
}

void MutableNumber::mutate()
{
    if(bernoulli(rate))
    {
        set(value + normal(0, sigma*sigma));
    }
}

MutableNumber MutableNumber::probability(double initialValue, double mutationProbability, double sigma)
{
    return MutableNumber(initialValue, mutationProbability, sigma, true, 0, true, 1);
}

MutableNumber MutableNumber::probability(j::Value const& config)
{
    return probability(config["initial"].toDouble(),
                       config["rate"].toDouble(),
                       config["sigma"].toDouble());
}
MutableNumber MutableNumber::positive(double initialValue, double mutationProbability, double sigma,
                                      bool hasMax, double max)
{
    return MutableNumber(initialValue, mutationProbability, sigma, true, 0, hasMax, max);
}

MutableNumber MutableNumber::positive(j::Value const& config, bool hasMax, double max)
{
    return positive(config["initial"].toDouble(),
                    config["rate"].toDouble(),
                    config["sigma"].toDouble(),
                    hasMax, max);
}
