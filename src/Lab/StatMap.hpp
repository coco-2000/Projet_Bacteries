#pragma once

#include "Recorder.hpp"
#include <unordered_map>
#include<string>

class StatMap
{
public:

    StatMap();

    const void operator+(const std::string&);
    const void mapSet(const Recorder::Property&);
    const void mapGet(const std::string&);
    const void registerNewClass(const std::string&);
    const void registerNewProperty(const std::string&, const std::string& classsName);
    const void incrementProperty(const Recorder::Property&, const std::string& classsName);



private :

    std::unordered_map<std::string, double> data;


};


