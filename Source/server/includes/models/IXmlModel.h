/*
** Created by Gaston Siffert
*/

#ifndef IXML_MODEL_H
#define IXML_MODEL_H

#include "rapidxml/rapidxml.hpp"

/*
** Interface used to describe the
** populated class by an xml document
*/
class IXmlModel
{
public:
    virtual void fromXml(rapidxml::xml_node<> *xml) = 0;
};

#endif //IXML_MODEL_H
