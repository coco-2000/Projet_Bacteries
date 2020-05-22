#include "Obstacle.hpp"
#include "../Utility/Utility.hpp"
#include "Application.hpp"

Obstacle::Obstacle(const Vec2d &position)
    : CircularBody (position, getAppConfig()["obstacle"]["radius"].toDouble())
{}

void Obstacle::drawOn(sf::RenderTarget &target) const
{
    constexpr unsigned int TAILLE_OBJ_GRAPHIQUE(6); //taille de l'objet graphique

    const auto texture = getAppConfig()["obstacle"]["texture"].toString();
    auto nutrimentSprite = buildSprite(getPosition(), TAILLE_OBJ_GRAPHIQUE, getAppTexture(texture));
    // adapte la taille du Sprite au rayon du nutriment:
    nutrimentSprite.setScale(2 * getRadius() / getAppTexture(texture).getSize().x,
                             2 * getRadius() / getAppTexture(texture).getSize().y);
    target.draw(nutrimentSprite);
}
