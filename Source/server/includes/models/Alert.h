/*
** Created by Gaston Siffert
*/

#ifndef ALERT_H
#define ALERT_H

#include <string>

#include "IXmlModel.h"

/*
** Describe an alert in the clients config file
*/
class Alert : public IXmlModel
{
private:
    static std::string TYPE;
    static std::string LIMIT;

private:
    std::string _type;
    int _limit;

public:
    Alert();
    ~Alert() = default;

public:
    std::string const &getType() const;
    int getLimit() const;

public:
    void setType(std::string const &value);
    void setLimit(int value);

public:
    void fromXml(rapidxml::xml_node<> *xml);
};

#endif //ALERT_H