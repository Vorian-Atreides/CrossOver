/*
** Created by Gaston Siffert
*/

#include "AWorker.h"

AWorker::AWorker(zmqpp::context const &context, std::string const &serverHost,
                 std::string const &port) :
    _puller(context, zmqpp::socket_type::pull)
{
    _puller.connect("tcp://" + serverHost + ":" + port);
}

AWorker::~AWorker()
{
    _puller.close();
}

/*
** IRunnable
*/

void AWorker::run()
{
    MetricUpdate message;
    std::string buffer;

    while (true)
    {
        _puller.receive(buffer);
        message.ParseFromString(buffer);

        if (message.IsInitialized())
            task(message);
    }
}