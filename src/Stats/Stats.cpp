#include <Stats/Stats.hpp>
#include "Application.hpp"

Stats::Stats()
    : currentId(0)
{
    initCounter();
}

const std::string& Stats::getCurrentTitle() const
{
    return graphSet.at(currentId).second;
}

void Stats::next()
{
    setActive(graphSet.size() == 0 ? currentId : ((currentId+1)%graphSet.size()));
}

void Stats::previous()
{
    setActive(graphSet.size() == 0 ? currentId : ((currentId-1)%graphSet.size()));
}

void Stats::reset()
{
    for(auto& value : graphSet) {
        value.second.first->reset();
    }
    initCounter();
}

void Stats::addGraph(int id, const std::string& title, const std::vector<std::string>& titles, double min, double max, const Vec2d& size)
{
    if(graphSet.find(id) == graphSet.end()) { // dans le cas où l'id existerait déjà
        graphSet[id].first.reset(new Graph(titles, size, min, max));
        graphSet[id].second = title;
        setActive(id);
    } else {
        throw std::invalid_argument("id de graphe déjà existant");
    }
}

void Stats::drawOn(sf::RenderTarget& target) const
{
    graphSet.at(currentId).first->drawOn(target);
}

void Stats::initCounter()
{
    counter = sf::Time::Zero;
}


void Stats::setActive(int id)
{
    currentId = id;
}

void Stats::update(sf::Time dt)
{
    if(counter>= sf::seconds(getShortConfig().stats_refresh_rate)) {
        for(auto& graph : graphSet) {
            graph.second.first->updateData(counter, getAppEnv().fetchData(graph.second.second));
        }
        initCounter();
    } else {
        counter += dt;
    }
}

