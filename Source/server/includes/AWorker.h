/*
** Created by Gaston Siffert
*/

#ifndef AWORKER_H
#define AWORKER_H

#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>

#include "IRunnable.h"
#include "models/metric_update.pb.h"

/*
** A Worker is an abstract class, listening on a specific port
** to receive a client's notification and run a task.
*/
class AWorker: public IRunnable
{
protected:
    zmqpp::socket _puller;

public:
    /*
    ** Initialize the socket's puller.
    */
    AWorker(zmqpp::context const &context, std::string const &serverHost,
            std::string const &port);
    virtual ~AWorker();

public:
    /*
    ** Inner loop, handling the dataflow and event architecture
    ** for the inherited classes.
    */
    void run();

protected:
    virtual void task(MetricUpdate const &message) = 0;
};

#endif //AWORKER_H