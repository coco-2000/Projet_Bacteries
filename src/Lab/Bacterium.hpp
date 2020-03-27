#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

class Bacterium : public CircularBody ,public Drawable, public Updatable
{

};
