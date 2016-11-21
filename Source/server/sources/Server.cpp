/*
** Created by Gaston Siffert
*/

#include "Server.h"

std::string Server::PULLER_PORT         = "4000";
std::string Server::DATA_PUSHER_PORT    = "4001";
std::string Server::ALERT_PUSHER_PORT   = "4002";

Server::Server() : Server(zmqpp::context())
{
}

Server::Server(zmqpp::context const &context) :
    _puller(context, zmqpp::socket_type::pull),
    _dataPusher(context, zmqpp::socket_type::push),
    _alertPusher(context, zmqpp::socket_type::push)
{
    _puller.bind("tcp://*:" + PULLER_PORT);
    _dataPusher.bind("tcp://*:" + DATA_PUSHER_PORT);
    _alertPusher.bind("tcp://*:" + ALERT_PUSHER_PORT);
}

Server::~Server()
{
    _puller.close();
    _dataPusher.close();
    _alertPusher.close();
}

/*
** IRunnable
*/

void Server::run()
{
    std::string buffer;

    while (true)
    {
        _puller.receive(buffer);
        _dataPusher.send(buffer);
        _alertPusher.send(buffer);
    }
}