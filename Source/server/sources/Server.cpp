/*
** Created by Gaston Siffert
*/

#include "Server.h"

Server::Server() : Server(zmqpp::context())
{
}

Server::Server(zmqpp::context const &context) :
    _puller(context, zmqpp::socket_type::pull),
    _dataPusher(context, zmqpp::socket_type::push),
    _alertPusher(context, zmqpp::socket_type::push)
{
    _puller.bind("tcp://*:4000");
    _dataPusher.bind("tcp://*:4001");
    _alertPusher.bind("tcp://*:4002");    
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