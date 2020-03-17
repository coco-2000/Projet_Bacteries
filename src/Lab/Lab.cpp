#include "Lab.hpp"


bool Lab::contains(const CircularBody& corps) const
{
    return (*Petri > corps);
}

Lab(const PetriDish& Petri, const Application& application){}
