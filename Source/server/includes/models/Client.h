/*
** Created by Gaston Siffert
*/

#ifndef CLIENT_H
#define CLIENT_H

#include <list>
#include <memory>

#include "Alert.h"
#include "IXmlModel.h"

/*
** Describe a client in the clients config file
*/
class Client: public IXmlModel
{
private:
    static std::string KEY;
    static std::string MAIL;
    static std::string ALERT;

private:
    std::string _key;
    std::string _mail;
    std::list<std::shared_ptr<Alert>> _alerts;

public:
    Client();
    ~Client() = default;

public:
    std::string const &getKey() const;
    std::string const &getMail() const;
    std::list<std::shared_ptr<Alert>> const &getAlerts() const;

public:
    void setKey(std::string const &value);
    void setMail(std::string const &value);
    void setAlerts(std::list<std::shared_ptr<Alert>> const &value);

public:
    void fromXml(rapidxml::xml_node<> *xml);
};

#endif //CLIENT_H