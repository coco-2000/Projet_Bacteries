#pragma once
#include <vector>
#include "../Utility/MutableColor.hpp"
#include <string>
#include "../Interface/Updatable.hpp"
#include "SwarmBacterium.hpp"

class Swarm : public Updatable, public DiffEqFunction
{
public:
    /**
     * @brief Swarm Constructeur
     * @param identificateur
     * @param groupe
     */
    Swarm(std::string identificateur, const std::vector <SwarmBacterium*>& groupe = {});

    /**
     * @brief getColor Cherche la couleur du Swarm dans le fichier de configuration
     * @return La couleur de associée à l'instance courante
     */
    MutableColor getColor() const;

    /**
     * @brief addBacterium Ajoute une bactérie au groupe et met à jour le leader du groupe
     * @param bacterie Bactérie swarm à ajouter
     */
    void addBacterium(SwarmBacterium* bacterie);

    /**
     * @brief supprBacterium Supprime une bactérie au groupe et met à jour le leader du groupe
     * @param bacterie Bactérie swarm à supprimer
     */
    void supprBacterium(SwarmBacterium* bacterie);

    /**
     * @brief getLeaderPosition Calcul la position du leader
     * @return la position du leader
     */
    Vec2d getLeaderPosition() const;

    /**
     * @brief getId Accesseur pour l'identificateur du Swarm
     * @return l'identificateur du Swarm
     */
    std::string getId() const;

    /**
     * @brief update Met à jour le leader du groupe
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void update(sf::Time dt);

    /**
     * @brief updateLeaderDirection Met à jour la direction du leader
     */
    void updateLeaderDirection();

    bool SuisJeLeader(const SwarmBacterium* bacterie);

    /**
     * @brief Destucteur de Swarm
     * Détruit les pointeurs vers les bactéries sans détruire les bactéries en elles-mêmes
     */
    ~Swarm();
private:
    std::string identificateur;
    std::vector <SwarmBacterium*> groupe;
    SwarmBacterium* leader;
    MutableColor couleur;

    /**
     * @brief setLeader Met à jour le leader du groupe
     */
    void setLeader();

    /**
     * @brief f Calcul le vecteur force déterminant le déplacement des bactéries du Swarm
     * Ici les bactéries du groupe ont un déplacement de groupe qui dépend de la position du leader
     * @param position Position de la bactérie sur laquelle s'applique la force calculée
     * @param speed Vitesse de la bactérie sur laquelle s'applique la force calculée /inutilisé
     * @return Le vecteur force appliqué sur la bactérie swarm
     */
    Vec2d f(Vec2d position, Vec2d speed) const;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux Swarms
     * @return La valeur associée à getAppConfig()["swarm"]
     */
    j::Value getConfig() const;
};

