/*
** Created by Gaston Siffert
*/

#include "models/Client.h"

std::string Client::KEY = "key";
std::string Client::MAIL = "mail";
std::string Client::ALERT = "alert";

Client::Client()
{
    _key = "";
    _mail = "";
    _alerts = std::list<std::shared_ptr<Alert>>();
}

/*
** Getters
*/

std::string const &Client::getKey() const
{
    return _key;
}

std::string const &Client::getMail() const
{
    return _mail;
}

std::list<std::shared_ptr<Alert>> const &Client::getAlerts() const
{
    return _alerts;
}

/*
** Setters
*/

void Client::setKey(std::string const &value)
{
    _key = value;
}

void Client::setMail(std::string const &value)
{
    _mail = value;
}

void Client::setAlerts(std::list<std::shared_ptr<Alert>> const &value)
{
    _alerts = value;
}

/*
** IXmlModel
*/

void Client::fromXml(rapidxml::xml_node<> *xml)
{
    if (xml->first_attribute(KEY.c_str()) == NULL ||
        xml->first_attribute(MAIL.c_str()) == NULL)
    {
        // TODO add log
        return;
    }

    _key = xml->first_attribute(KEY.c_str())->value();
    _mail = xml->first_attribute(MAIL.c_str())->value();
    _alerts = std::list<std::shared_ptr<Alert>>();
    for (rapidxml::xml_node<> *alert = xml->first_node(ALERT.c_str()); alert;
        alert = alert->next_sibling())
    {
        if (alert == NULL)
        {
            //TODO add log            
            continue;
        }
         Alert *tmp = new Alert();
         tmp->fromXml(alert);
        _alerts.push_back(std::shared_ptr<Alert>(tmp));    
    }
}