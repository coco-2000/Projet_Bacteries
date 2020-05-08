#pragma once
#include "Graph.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

typedef std::pair<std::unique_ptr<Graph>,std::string> Graph_labelled;

class Stats : public Drawable, public Updatable
{
public :
    Stats();
    std::string getCurrentTitle() const;
    void next();
    void previous();
    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;
    void reset();
    void addGraph(int id, const std::string& title, std::vector<std::string> const& titles,
                  double min, double max, Vec2d const& size);
    void setActive(int id);

private:
    void initCounter();
    int currentId;
    std::map<int, Graph_labelled> graphSet;
    sf::Time counter;
};
