#pragma once
#include "MutableNumber.hpp"
#include <array>
#include <SFML/Graphics.hpp>


class MutableColor
{
public:
    MutableColor(j::Value const& config);
    void mutate();
    sf::Color get();


private :
    std::array <MutableNumber, 4> RGBA;


};

