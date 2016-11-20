/*
** Created by Gaston Siffert
*/

#include "models/Alert.h"

std::string Alert::TYPE = "type";
std::string Alert::LIMIT = "limit";

Alert::Alert()
{
    _type = "";
    _limit = 0;
}

/*
** Getters
*/

std::string const &Alert::getType() const
{
    return _type;
}

int Alert::getLimit() const
{
    return _limit;
}

/*
** Setters
*/

void Alert::setType(std::string const &value)
{
    _type = value;
}

void Alert::setLimit(int value)
{
    _limit = value;
}

/*
** IXmlModel
*/

void Alert::fromXml(rapidxml::xml_node<> *xml)
{
    _type = xml->first_attribute(TYPE.c_str())->value();
    /*
    ** We assume the limit as the same unit
    ** than the received data from the client notification.
    */
    _limit = atoi(xml->first_attribute(LIMIT.c_str())->value());
}