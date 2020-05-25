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
     * @param id
     * @param group
     */
    Swarm(const std::string& id, const std::vector<SwarmBacterium*>& group = {});

    /**
     * @brief getColor Cherche la couleur du Swarm dans le fichier de configuration
     * @return La couleur du swarm dont fait parti l'instance courante
     */
    MutableColor getColor() const;

    /**
     * @brief addBacterium Ajoute une bactérie au groupe et met à jour le leader du groupe s'il n'y en a pas
     * @param bacterie Instance de bactérie à ajouter au Swarm
     */
    void addBacterium(SwarmBacterium* bacterie);

    /**
     * @brief supprBacterium Supprime une bactérie du groupe et met à jour le leader du groupe
     * @param bacterie Instance de bactérie à supprimer du swarm
     */
    void supprBacterium(SwarmBacterium* bacterie);

    /**
     * @brief getId
     * @return l'identificateur du Swarm
     */
    const std::string& getId() const;

    /**
     * @brief update Met à jour le leader du groupe
     * @param dt Pas de temps après lequel la simulation est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief IsLeader Vérifie si une bactérie est leader du groupe
     * @param bacterie
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
     * @brief f Calcule le vecteur force déterminant le déplacement des bactéries du Swarm
     * Ici les bactéries du groupe ont un déplacement de groupe qui dépend de la position du leader
     * @param position Position de la bactérie sur laquelle s'applique la force calculée
     * @param speed Vitesse de la bactérie sur laquelle s'applique la force calculée //inutilisé
     * @return Le vecteur force appliqué sur la bactérie à comportement de groupe
     */
    Vec2d f(Vec2d position, Vec2d speed) const override;

    /**
     * @brief getConfig Raccourci pour accéder aux paramètres relatifs aux Swarms
     * @return La valeur associée à getAppConfig()["swarm"]
     */
    const j::Value& getConfig() const;

    /**
     * @brief getLeaderPosition
     * @return La position du leader
     */
    const Vec2d& getLeaderPosition() const;
};

