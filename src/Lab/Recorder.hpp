# pragma once
#include<string>
#include<vector>


class Recorder
{
public:
    enum mode {INC, SET};
    struct Property{
        std::string name;
        /**
         * @brief value
         * si le mode est INC, value correspond à la valeur à incrémenter
         * si le mode est SET, value correpond à la valeur à mettre
         */
        double value;
        mode m;
        std::string associateClass;
    };



protected:
    std::string className;
    //Recorder();
    void commitProperty(const std::vector<Property>& properties, bool incOrdec);
    virtual std::vector<Property>getRecordProperty() const = 0;
    virtual ~Recorder() = default;
};
