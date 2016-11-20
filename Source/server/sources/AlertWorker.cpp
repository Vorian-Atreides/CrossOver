/*
** Created by Gaston Siffert
*/

#include <stdlib.h>
#include <curl/curl.h>

#include <fstream>
#include <sstream>
#include <vector>
#include <rapidxml/rapidxml.hpp>

#include "AlertWorker.h"


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

AlertWorker::AlertWorker() :
    AlertWorker(zmqpp::context())
{
}

AlertWorker::AlertWorker(zmqpp::context const &context) :
    AWorker(context, "4002")
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
    curl_easy_setopt(curl, CURLOPT_USERNAME, "support@cross.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "12345");
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://mail:25");
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "support@cross.com");
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
}

bool AlertWorker::shoudlRaiseAnAlert(MetricUpdate const &message,
                            std::shared_ptr<Client> const &client) const
{
    if (message.has_cpu())
    {
        std::shared_ptr<Alert> const &alert = findAlertByKey(client->getAlerts(), "cpu");
        if (message.cpu() > alert->getLimit())
            return true;
    }
    if (message.has_memory())
    {
        std::shared_ptr<Alert> const &alert = findAlertByKey(client->getAlerts(), "memory");
        if (message.memory() > alert->getLimit())
            return true;
    }
    if (message.has_processes())
    {
        std::shared_ptr<Alert> const &alert = findAlertByKey(client->getAlerts(), "processes");
        if (message.processes() > alert->getLimit())
            return true;
    }
    return false;
}

std::shared_ptr<Alert> const &AlertWorker::findAlertByKey(
                            std::list<std::shared_ptr<Alert>> const &items,
                            std::string const &key) const
{
    for (std::shared_ptr<Alert> const &alert: items)
    {
        if (alert->getType() == key)
            return alert;
    }
}

void AlertWorker::parseClientsFile(std::list<std::shared_ptr<Client>> &clients) const
{
    rapidxml::xml_document<> document;
    rapidxml::xml_node<> *root;

    // Read the file
    std::ifstream file("../resources/clients.xml");
    if (!file.is_open())
    {
       //TODO add log
        return;
    }
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
    // Initialize the parser
    document.parse<0>(&buffer[0]);
    root = document.first_node("clients");
    // Start the parsing and mapping
    clients.clear();
    for (rapidxml::xml_node<> *client = root->first_node("client"); client;
        client = client->next_sibling())
    {
        Client *tmp = new Client();
        tmp->fromXml(client);
        clients.push_back(std::shared_ptr<Client>(tmp));
    }
    file.close();
}