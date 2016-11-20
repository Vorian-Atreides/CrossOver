/*
** Created by Gaston Siffert
*/

#ifndef DATA_WORKER_H
#define DATA_WORKER_H

#include <mysql_driver.h>

#include "AWorker.h"

/*
** DataWorker is a worker in charge of
** updating the database with the client notification
*/
class DataWorker : public AWorker
{
private:
    std::shared_ptr<sql::Connection> _connection;

public:
    /*
    ** Provide a shared context in the application,
    ** the context is thread safe and multiplex the
    ** socket
    */
    DataWorker(zmqpp::context const &context);
    /*
    ** Create an process independant context
    */    
    DataWorker();
    ~DataWorker();

protected:
    /*
    ** Create a new metric and its relational element
    ** depending if the memory, cpu, processes; were
    ** present in the message.
    */
    void task(MetricUpdate const &message);

private:
    // Insert a new row in the table metrics
    int insertMetric(std::string const &key);
    // Insert a new row in the table memories
    void insertMemory(int metricId, float value);
    // Insert a new row in the table cpu
    void insertCpu(int metricId, float value);
    // Insert a new row in the table processes
    void insertProcesses(int metricId, int value);
};

#endif //DATA_WORKER_H