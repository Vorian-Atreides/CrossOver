/*
** Created by Gaston Siffert
*/

#ifndef ALERT_WORKER_H
#define ALERT_WORKER_H

#include <memory>

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
public:
    /*
    ** Provide a shared context in the application,
    ** the context is thread safe and multiplex the
    ** socket
    */
    AlertWorker(zmqpp::context const &context);
    /*
    ** Create an process independant context
    */
    AlertWorker();
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
    std::shared_ptr<Alert> const &findAlertByKey(
                            std::list<std::shared_ptr<Alert>> const &items,
                            std::string const &key) const;
    // Parse the config file with the list of clients
    void parseClientsFile(std::list<std::shared_ptr<Client>> &clients) const;
};

#endif //ALERT_WORKER_H
