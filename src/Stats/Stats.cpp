#include <Stats/Stats.hpp>
#include "Application.hpp"

Stats::Stats()
    : currentId(0)
{
    initCounter();
}

std::string Stats::getCurrentTitle() const
{
    return labels_set.at(currentId);
}

void Stats::next()
{
    currentId = (1 + currentId)%labels_set.size();
}

void Stats::previous()
{
    currentId = (currentId-1)%labels_set.size();
}

void Stats::reset()
{
    for(auto& value : graph_labelled_set)
    {
        value.second.reset();
    }
    initCounter();
}

void Stats::addGraph(int id, const std::string& title, const std::vector<std::string> &titles, double min, double max, const Vec2d &size)
{
   if(!labels_set.count(id)) // dans le cas où l'id existerait déjà
   {
       graph_labelled_set[labels_set[id]].reset(new Graph(titles, size, min, max));
       labels_set[id] = title;
       currentId = id;
   }
   else
   {
       throw std::invalid_argument("id déjà existant");
   }
}

void Stats::drawOn(sf::RenderTarget &target) const
{
    graph_labelled_set.at(getCurrentTitle())->drawOn(target);
}

void Stats::initCounter()
{
    counter = sf::Time::Zero;
}

Graph Stats::getGraphwith(const std::string& title) const
{
    return *graph_labelled_set.at(title);
}

void Stats::setActive(int id)
{
    currentId = id;
}

void Stats::update(sf::Time dt)
{
    if(counter>= sf::seconds(getAppConfig()["stats"]["refresh rate"].toDouble()))
    {

    }
    else
    {
        initCounter();
    }
}
