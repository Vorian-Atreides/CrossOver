#include <gtest/gtest.h>

#include "AlertWorker.h"

#define LOCALHOST "localhost"

static std::shared_ptr<Client> initClient(std::string const &alertType, int alertLimit)
{
    std::shared_ptr<Client> client = std::shared_ptr<Client>(new Client());
    std::shared_ptr<Alert> alert = std::shared_ptr<Alert>(new Alert());
    alert->setType(alertType);
    alert->setLimit(alertLimit);
    std::list<std::shared_ptr<Alert>> alerts = std::list<std::shared_ptr<Alert>>();
    alerts.push_back(alert);
    client->setAlerts(alerts);

    return client;
}

TEST(AlertWorkerTest, ShouldRaiseAnAlert)
{
    zmqpp::context context;
    AlertWorker worker(context, LOCALHOST);

    // Check the memory alert    
    MetricUpdate message = MetricUpdate();
    message.set_key("user1");
    message.set_memory(60.0);
    std::shared_ptr<Client> client = initClient("memory", 50);
    ASSERT_TRUE(worker.shoudlRaiseAnAlert(message, client));

    // Check the processes alert
    message = MetricUpdate();
    message.set_key("user1");
    message.set_processes(200);
    client = initClient("processes", 100);
    ASSERT_TRUE(worker.shoudlRaiseAnAlert(message, client));

    // Check the cpu alert
    message = MetricUpdate();
    message.set_key("user1");
    message.set_cpu(40);
    client = initClient("cpu", 30);
    ASSERT_TRUE(worker.shoudlRaiseAnAlert(message, client));
}

TEST(AlertWorkerTest, ShouldNotRaiseAnAlert)
{
    zmqpp::context context;
    AlertWorker worker(context, LOCALHOST);

    // Check the memory alert    
    MetricUpdate message = MetricUpdate();
    message.set_key("user1");
    message.set_memory(40.0);
    std::shared_ptr<Client> client = initClient("memory", 50);
    ASSERT_FALSE(worker.shoudlRaiseAnAlert(message, client));

    // Check the processes alert
    message = MetricUpdate();
    message.set_key("user1");
    message.set_processes(80);
    client = initClient("processes", 100);
    ASSERT_FALSE(worker.shoudlRaiseAnAlert(message, client));

    // Check the cpu alert
    message = MetricUpdate();
    message.set_key("user1");
    message.set_cpu(25);
    client = initClient("cpu", 30);
    ASSERT_FALSE(worker.shoudlRaiseAnAlert(message, client));
}

static std::list<std::shared_ptr<Alert>> initAlerts(std::string const &alertType)
{
    std::shared_ptr<Alert> alert = std::shared_ptr<Alert>(new Alert());
    alert->setType(alertType);
    std::list<std::shared_ptr<Alert>> alerts = std::list<std::shared_ptr<Alert>>();
    alerts.push_back(alert);
    return alerts;
}

TEST(AlertWorkerTest, FindAlertByKey)
{
    zmqpp::context context;
    AlertWorker worker(context, LOCALHOST);

    std::list<std::shared_ptr<Alert>> alerts = initAlerts("memory");
    ASSERT_EQ(worker.findAlertByKey(alerts, "memory"), alerts.cbegin());

    alerts = initAlerts("processes");
    ASSERT_EQ(worker.findAlertByKey(alerts, "processes"), alerts.cbegin());

    alerts = initAlerts("cpu");
    ASSERT_EQ(worker.findAlertByKey(alerts, "cpu"), alerts.cbegin());

    alerts = initAlerts("crossover");
    ASSERT_EQ(worker.findAlertByKey(alerts, "crossover"), alerts.cbegin());
}

TEST(AlertWorkerTest, FindNotAlertByKey)
{
    zmqpp::context context;
    AlertWorker worker(context, LOCALHOST);

    std::list<std::shared_ptr<Alert>> alerts = initAlerts("crossover");
    ASSERT_EQ(worker.findAlertByKey(alerts, "memory"), alerts.cend());

    alerts = initAlerts("processes");
    ASSERT_EQ(worker.findAlertByKey(alerts, "memory"), alerts.cend());

    alerts = initAlerts("cpu");
    ASSERT_EQ(worker.findAlertByKey(alerts, "memory"), alerts.cend());

    alerts = initAlerts("other");
    ASSERT_EQ(worker.findAlertByKey(alerts, "memory"), alerts.cend());
}

TEST(AlertWorkerTest, ParseValidClients)
{
    zmqpp::context context;
    AlertWorker worker(context, LOCALHOST);

    std::list<std::shared_ptr<Client>> clients = std::list<std::shared_ptr<Client>>();
    std::string xml = "<clients>" \
                        "<client key=\"key1\" mail=\"user1@email.com\">" \
                            "<alert type=\"memory\" limit=\"50\"/>" \
                        "</client>" \
                      "</clients>";
    worker.parseClients(clients, xml);

    ASSERT_EQ(clients.size(), 1);
    std::shared_ptr<Client> const &client = *clients.begin();
    ASSERT_EQ(client->getKey(), "key1");
    ASSERT_EQ(client->getMail(), "user1@email.com");    
    std::shared_ptr<Alert> const &alert = *client->getAlerts().begin();
    ASSERT_EQ(alert->getType(), "memory");
    ASSERT_EQ(alert->getLimit(), 50);    
}

TEST(AlertWorkerTest, ParseInvalidClients)
{
    zmqpp::context context;
    AlertWorker worker(context, LOCALHOST);

    std::list<std::shared_ptr<Client>> clients = std::list<std::shared_ptr<Client>>();
    std::string xml = "";
    worker.parseClients(clients, xml);
    ASSERT_EQ(clients.size(), 0);

    xml = "<test></test>";
    worker.parseClients(clients, xml);
    ASSERT_EQ(clients.size(), 0);

    xml = "<clients></clients>";
    worker.parseClients(clients, xml);
    ASSERT_EQ(clients.size(), 0);

    xml = "<clients>" \
            "<client></client>" \
          "</clients>";
    worker.parseClients(clients, xml);
    ASSERT_EQ(clients.size(), 1);
    std::shared_ptr<Client> const &client = *clients.begin();
    ASSERT_EQ(client->getKey(), "");
    ASSERT_EQ(client->getMail(), "");
    ASSERT_EQ(client->getAlerts().size(), 0);

    xml = "<clients>" \
            "<client key=\"key1\" mail=\"user1@email.com\">" \
                "<alert/>" \
            "</client>" \
          "</clients>";
    worker.parseClients(clients, xml);
    ASSERT_EQ(clients.size(), 1);
    std::shared_ptr<Client> const &client2 = *clients.begin();
    ASSERT_EQ(client2->getAlerts().size(), 1);
    std::shared_ptr<Alert> const &alert = *client2->getAlerts().begin();
    ASSERT_EQ(alert->getType(), "");
    ASSERT_EQ(alert->getLimit(), 0);
}