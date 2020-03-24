#pragma once
#include "MutableNumber.hpp"
#include <array>
#include <SFML/Graphics.hpp>


class MutableColor
{
public:
    /**
     * @brief MutableColor Constructeur
     * @param config Entrée du fichier de configuration depuis laquelle on prend les paramètres
     */
    MutableColor(j::Value const& config);

    /**
     * @brief mutate Fais muter chacun des composants de la couleur
     */
    void mutate();

    /**
     * @brief get Accesseur de la couleur
     * @return La couleur sous une forme reconnue par SFML
     */
    sf::Color get();


private :
    std::array <MutableNumber, 4> RGBA;


};

