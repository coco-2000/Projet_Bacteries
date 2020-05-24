#pragma once
#include "Graph.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

typedef std::pair<std::unique_ptr<Graph>,std::string> Graph_labelled;

class Stats : public Drawable, public Updatable
{
public :
    /**
     * @brief Stats constructeur met compteur et graphe actif à 0
     */
    Stats();

    /**
     * @brief getCurrentTitle permet d'obtenir le titre du graphe courant
     * @return le titre du graphe courant
     */
    const std::string& getCurrentTitle() const;

    /**
     * @brief next incrémente l'identifiant actif
     */
    void next();

    /**
     * @brief previous décrémente l'identifiant actif
     */
    void previous();

    /**
     * @brief drawOn permet d'afficher chacun des graphes de l'instance courante
     * @param target la fenetre dans laquelle on affiche les graphes
     */
    void drawOn(sf::RenderTarget& target) const override;

    /**
     * @brief update met à jour les graphes de l'instance courante en insérant les
     * nouvelles données calculées dans chacune des séries de chaque graphe
     * @param dt Pas de temps après lequel lequel la simulation est mise à jour
     */
    void update(sf::Time dt) override;

    /**
     * @brief reset purge l'ensemble des graphes de leurs séries de points et recommence
     * l'affichage depuis l'origine
     */
    void reset();

    /**
     * @brief addGraph ajoute un graphe à l'instance courante
     * @param id l'identifiant du graphe
     * @param title le titre du graphe
     * @param titles ensemble des titre de courbes du graphe
     * @param min valeur minimale pour laquelle s'affiche les points de courbes
     * @param max valeur maximale pour laquelle s'affiche les points de courbes
     * @param size dimension de la fenêtre graphique dans laquelle se font les affichages
     */
    void addGraph(int id, const std::string& title, std::vector<std::string> const& titles,
                  double min, double max, Vec2d const& size);

    /**
     * @brief setActive permet de d'affecter une nouvelle valeur à l'identifiant actif
     * @param id la nouvelle valeur affectée
     */
    void setActive(int id);

private:
    int currentId;
    std::map<int, Graph_labelled> graphSet;
    sf::Time counter;

    /**
     * @brief initCounter permet d'initialiser le compteur au temps 0
     */
    void initCounter();
};
