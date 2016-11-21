/*
** Created by Gaston Siffert
*/

#ifndef ALERT_WORKER_H
#define ALERT_WORKER_H

#include <memory>

#include <gtest/gtest_prod.h>

#include "models/Client.h"
#include "AWorker.h"

/*
** AlertWorker is a worker in charge of
** analyzing the message and the registered limits
** in the clients config file.
** It must send an email if a data outside
** one of the limits.
*/
class AlertWorker: public AWorker
{
private:
    FRIEND_TEST(AlertWorkerTest, ShouldRaiseAnAlert);
    FRIEND_TEST(AlertWorkerTest, ShouldNotRaiseAnAlert);
    FRIEND_TEST(AlertWorkerTest, FindAlertByKey);
    FRIEND_TEST(AlertWorkerTest, FindNotAlertByKey);
    FRIEND_TEST(AlertWorkerTest, ParseValidClients);
    FRIEND_TEST(AlertWorkerTest, ParseInvalidClients);

private:
    static std::string PUSHER_PORT;
    static std::string CLIENT_FILE;
    static std::string CLIENTS;
    static std::string CLIENT;
    static std::string SMTP_USER;
    static std::string SMTP_PASSWORD;
    static std::string SMTP_CONN;
    static std::string SMTP_FROM;

public:
    /*
    ** Provide a shared context in the application,
    ** the context is thread safe and multiplex the
    ** socket
    */
    AlertWorker(zmqpp::context const &context, std::string const &serverHost);
    ~AlertWorker() = default;

protected:
    void task(MetricUpdate const &message);

private:
    // Send an email to the client outsiding one of the limits
    void sendEmail(MetricUpdate const &message,
                   std::shared_ptr<Client> const &client) const;
    // Check if one of the limit is depassed.
    bool shoudlRaiseAnAlert(MetricUpdate const &message,
                            std::shared_ptr<Client> const &client) const;
    // Search the alert for a specific key: "memory", "cpu", ...
    std::list<std::shared_ptr<Alert>>::const_iterator findAlertByKey(
                            std::list<std::shared_ptr<Alert>> const &items,
                            std::string const &key) const;
    // Parse the config file with the list of clients
    void parseClientsFile(std::list<std::shared_ptr<Client>> &clients) const;
    void parseClients(std::list<std::shared_ptr<Client>> &clients,
                      std::string const &xml) const;
};

#endif //ALERT_WORKER_H
