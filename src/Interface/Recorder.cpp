#include "Recorder.hpp"
#include "Application.hpp"
Recorder::Recorder()
{
    addtowatch(getProperty(), true);
}

void Recorder::addtowatch(const std::vector<Property>& s, const bool b)
{
    for(auto p : s) {
        switch (p.m) {
        case INC:
            b ? getAppEnv().mapSet(p.name, getAppEnv().mapGet(p.name)+p.value) : getAppEnv().mapSet(p.name, getAppEnv().mapGet(p.name)-p.value);
            break;
        case SET:
            b ? getAppEnv().mapSet(p.name, p.value) : getAppEnv().mapSet(p.name, 0);
            break;
        }
    }
}

Recorder::~Recorder()
{
    addtowatch(getProperty(), false);
}
