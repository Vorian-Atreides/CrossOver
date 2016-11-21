/*
** Created by Gaston Siffert
*/

#include <sstream>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/connection.h>

#include "DataWorker.h"

DataWorker::DataWorker(zmqpp::context const &context,
                       std::string const &serverHost) :
    AWorker(context, serverHost, "4001")
{
    _connection = NULL;
}

DataWorker::~DataWorker()
{
    if (_connection)
        _connection->close();
}

/*
** AWorker
*/

void DataWorker::task(MetricUpdate const &message)
{
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

bool DataWorker::connectToMysql()
{
    try
    {
        auto driver = sql::mysql::get_mysql_driver_instance();
        if (driver)
        {
            _connection = std::shared_ptr<sql::Connection>(
                driver->connect("tcp://localhost:3306", "user", "password"));
            return true;
        }
    }
    catch (sql::SQLException e)
    {
        //TODO add log
    }
    return false;
}

int DataWorker::insertMetric(std::string const &key)
{
    if (!_connection && !connectToMysql())
    {
        //TODO add log
        return -1;
    }

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

bool DataWorker::insertMemory(int metricId, float value)
{
    if (!_connection && !connectToMysql())
    {
        //TODO add log
        return false;
    }

    std::stringstream request;
    std::unique_ptr<sql::Statement> statement(_connection->createStatement());

    request << "INSERT INTO memories(metric_id, value) VALUES('"
        << metricId << "', '" << value << "')";
    statement->execute("USE crossover");
    statement->execute(request.str());
    
    return true;
}

bool DataWorker::insertCpu(int metricId, float value)
{
    if (!_connection && !connectToMysql())
    {
        //TODO add log        
        return false;
    }

    std::stringstream request;
    std::unique_ptr<sql::Statement> statement(_connection->createStatement());

    request << "INSERT INTO cpu(metric_id, value) VALUES('"
        << metricId << "', '" << value << "')";
    statement->execute("USE crossover");
    statement->execute(request.str());
    return true;
}

bool DataWorker::insertProcesses(int metricId, int value)
{
    if (!_connection && !connectToMysql())
    {
        //TODO add log        
        return false;
    }

    std::stringstream request;
    std::unique_ptr<sql::Statement> statement(_connection->createStatement());

    request << "INSERT INTO processes(metric_id, value) VALUES('"
        << metricId << "', '" << value << "')";
    statement->execute("USE crossover");
    statement->execute(request.str());
    return true;
}