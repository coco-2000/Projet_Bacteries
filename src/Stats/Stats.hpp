#pragma once
#include "Graph.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

class Stats : public Drawable, public Updatable
{
public :
    std::string getCurrentTitle();
    void next();
private:
    int CurrentId;

};

