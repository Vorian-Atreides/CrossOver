/*
** Created by Gaston Siffert
*/

#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>

#include "models/metric_update.pb.h"

/*
** The Request is a class abstracting the notification request
** to the remote server.
*/
class Request
{
private:
    zmqpp::socket _pusher;

public:
    Request(zmqpp::context const &context, std::string const &serverHost);
    ~Request();

public:
    void send(MetricUpdate const &message);
};