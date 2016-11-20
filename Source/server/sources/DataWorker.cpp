/*
** Created by Gaston Siffert
*/

#include <sstream>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/connection.h>

#include "DataWorker.h"

DataWorker::DataWorker() : DataWorker(zmqpp::context())
{
}

DataWorker::DataWorker(zmqpp::context const &context) :
    AWorker(context, "4001")
{
    try
    {
        auto driver = sql::mysql::get_mysql_driver_instance();
        if (driver)
            _connection = std::shared_ptr<sql::Connection>(
                driver->connect("tcp://mysql:3306", "user", "password"));
    }
    catch (sql::SQLException e)
    {
        //TODO add log
    }
}

DataWorker::~DataWorker()
{
    _connection->close();
}

/*
** AWorker
*/

void DataWorker::task(MetricUpdate const &message)
{
    if (!_connection)
    {
        //TODO add log        
        return;
    }

    int newId = insertMetric(message.key());
    if (newId == -1)
    {
        //TODO add log        
        return;
    }

    if (message.has_memory())
        insertMemory(newId, message.memory());
    if (message.has_cpu())
        insertCpu(newId, message.cpu());
    if (message.has_processes())
        insertProcesses(newId, message.processes());
}

/*
** Private
*/

int DataWorker::insertMetric(std::string const &key)
{
    std::stringstream request;
    std::unique_ptr<sql::Statement> statement(_connection->createStatement());

    request << "INSERT INTO metrics(client_key) VALUES('" << key << "')";
    statement->execute("USE crossover");
    statement->execute(request.str());
    std::unique_ptr<sql::ResultSet> result(statement->executeQuery("SELECT LAST_INSERT_ID()"));

    if (result->next())
        return result->getInt(1);
    //TODO add log    
    return -1;
}

void DataWorker::insertMemory(int metricId, float value)
{
    std::stringstream request;
    std::unique_ptr<sql::Statement> statement(_connection->createStatement());

    request << "INSERT INTO memories(metric_id, value) VALUES('"
        << metricId << "', '" << value << "')";
    statement->execute("USE crossover");
    statement->execute(request.str());
}

void DataWorker::insertCpu(int metricId, float value)
{
    std::stringstream request;
    std::unique_ptr<sql::Statement> statement(_connection->createStatement());

    request << "INSERT INTO cpu(metric_id, value) VALUES('"
        << metricId << "', '" << value << "')";
    statement->execute("USE crossover");
    statement->execute(request.str());
}

void DataWorker::insertProcesses(int metricId, int value)
{
    std::stringstream request;
    std::unique_ptr<sql::Statement> statement(_connection->createStatement());

    request << "INSERT INTO processes(metric_id, value) VALUES('"
        << metricId << "', '" << value << "')";
    statement->execute("USE crossover");
    statement->execute(request.str());
}