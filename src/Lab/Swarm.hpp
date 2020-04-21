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
    Swarm(std::string id, const std::vector <SwarmBacterium*>& group = {});

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
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief updateLeaderDirection Met à jour la direction du leader
     */
    void updateLeaderDirection();

    /**
     * @brief IsLeader Vérifie si une bactérie est leader du groupe
     * @param bacterie Instance dont on vérifie la condition
     * @return true si la bactérie est leader, false sinon
     */
    bool IsLeader(const SwarmBacterium* bacterie) const;

    /**
     * @brief Destucteur de Swarm
     * Détruit les pointeurs vers les bactéries sans détruire les bactéries en elles-mêmes
     */
    ~Swarm() override;

private:
    std::string id;
    std::vector <SwarmBacterium*> group;
    SwarmBacterium* leader;
    MutableColor color;

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

