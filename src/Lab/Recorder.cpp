#include "Recorder.hpp"
#include "Application.hpp"


/**Recorder::Recorder()
{
    commitProperty(getRecordProperty(), true);
}**/


void Recorder::commitProperty(const std::vector<Property>& properties, const bool b)
{
    for(auto p : properties) {
        switch (p.m) {
        case INC:
            b ? getAppEnv().mapSet(p.name, getAppEnv().mapGet(p.name).first + p.value, p.associateClass) : getAppEnv().mapSet(p.name, getAppEnv().mapGet(p.name).first -p.value);
            break;
        case SET:
            b ? getAppEnv().mapSet(p.name, p.value) : getAppEnv().mapSet(p.name, 0);
            break;
        }
    }
}

/**Recorder::~Recorder()
{
    commitProperty(getRecordProperty(), false);
}**/
