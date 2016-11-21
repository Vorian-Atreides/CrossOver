/*
** Created by Gaston Siffert
*/

#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include <curl/curl.h>
#include <rapidxml/rapidxml.hpp>

#include "AlertWorker.h"

std::string AlertWorker::PUSHER_PORT    = "4002";
std::string AlertWorker::CLIENT_FILE    = "../resources/clients.xml";
std::string AlertWorker::CLIENTS        = "clients";
std::string AlertWorker::CLIENT         = "client";
std::string AlertWorker::SMTP_USER      = "support@cross.com";
std::string AlertWorker::SMTP_PASSWORD  = "12345";
std::string AlertWorker::SMTP_CONN      = "smtp://mail:25";
std::string AlertWorker::SMTP_FROM      = "support@cross.com";

/*
** LibCurl callback to build the email
** payload
*/
static size_t buildPayload(void *ptr, size_t size, size_t nmemb, void *data)
{
    MetricUpdate const *message = (MetricUpdate const *)(data);
    std::stringstream stream;

    stream << "to: gs060292@live.fr\r\n";
    stream << "from: support@cross.com\r\n";
    stream << "subject: SMTP TLS example message\r\n";
    stream << "\r\n";
    stream << "Hellor World !\r\n";
    stream << ".\r\n";

    std::string const &buffer = stream.str();
    memcpy(ptr, buffer.c_str(), buffer.length());
    return buffer.length();
}

AlertWorker::AlertWorker(zmqpp::context const &context,
                         std::string const &serverHost) :
    AWorker(context, serverHost, PUSHER_PORT)
{
}

/*
** AWorker
*/

void AlertWorker::task(MetricUpdate const &message)
{
    std::list<std::shared_ptr<Client>> clients;

    parseClientsFile(clients);
    for (auto client: clients)
        if (client->getKey() == message.key())
        {
            if (shoudlRaiseAnAlert(message, client))
                sendEmail(message, client);
            return;
        }
}

/*
** Private
*/

void AlertWorker::sendEmail(MetricUpdate const &message,
                            std::shared_ptr<Client> const &client) const
{
    CURL *curl;
    struct curl_slist *recipients = NULL;

    curl = curl_easy_init();
    if (!curl)
    {
        //TODO add log
        return;
    }
    curl_easy_setopt(curl, CURLOPT_USERNAME, SMTP_USER.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, SMTP_PASSWORD.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, SMTP_CONN.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, SMTP_FROM.c_str());
    recipients = curl_slist_append(recipients, client->getMail().c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, &buildPayload);
    curl_easy_setopt(curl, CURLOPT_READDATA, &message);
    if (curl_easy_perform(curl) != CURLE_OK)
    {
       //TODO add log
    }
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
    std::cout << "Alert" << std::endl;
}

bool AlertWorker::shoudlRaiseAnAlert(MetricUpdate const &message,
                            std::shared_ptr<Client> const &client) const
{
    std::list<std::shared_ptr<Alert>> const &alerts = client->getAlerts();
    if (message.has_cpu())
    {
        std::list<std::shared_ptr<Alert>>::const_iterator const &alert = findAlertByKey(alerts, "cpu");
        if (alert != alerts.cend() && message.cpu() > (*alert)->getLimit())
            return true;
    }
    if (message.has_memory())
    {
        std::list<std::shared_ptr<Alert>>::const_iterator const &alert = findAlertByKey(alerts, "memory");
        if (alert != alerts.cend() && message.memory() > (*alert)->getLimit())
            return true;
    }
    if (message.has_processes())
    {
        std::list<std::shared_ptr<Alert>>::const_iterator const &alert = findAlertByKey(alerts, "processes");        
        if (alert != alerts.cend() && message.processes() > (*alert)->getLimit())
            return true;
    }
    return false;
}

std::list<std::shared_ptr<Alert>>::const_iterator AlertWorker::findAlertByKey(
                            std::list<std::shared_ptr<Alert>> const &items,
                            std::string const &key) const
{
    for (std::list<std::shared_ptr<Alert>>::const_iterator it = items.cbegin();
        it != items.cend(); ++it)
    {
        if ((*it)->getType() == key)
            return it;
    }
    return items.cend();
}

void AlertWorker::parseClientsFile(std::list<std::shared_ptr<Client>> &clients) const
{
    // Read the file
    std::ifstream file(CLIENT_FILE);
    if (!file.is_open())
    {
       //TODO add log
        return;
    }
    std::string xml((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    parseClients(clients, xml);
}

void AlertWorker::parseClients(std::list<std::shared_ptr<Client>> &clients,
                                std::string const &xml) const
{
    rapidxml::xml_document<> document;
    rapidxml::xml_node<> *root;

    std::vector<char> buffer(xml.begin(), xml.end());
	buffer.push_back('\0');

    document.parse<0>(&buffer[0]);
    root = document.first_node(CLIENTS.c_str());
    if (root == NULL)
    {
        //TODO add log
        return;
    }
    // Start the parsing and mapping
    clients.clear();
    for (rapidxml::xml_node<> *client = root->first_node(CLIENT.c_str()); client;
        client = client->next_sibling())
    {
        if (client == NULL)
        {
            //TODO add log            
            continue;
        }
        Client *tmp = new Client();
        tmp->fromXml(client);
        clients.push_back(std::shared_ptr<Client>(tmp));
    }
}