/*
** Created by Gaston Siffert
*/

#include "Request.h"

std::string Request::HOST = "tcp://localhost:4000";

Request::Request(zmqpp::context const &context) :
    _pusher(context, zmqpp::socket_type::push)
{
    _pusher.connect(HOST);
}

Request::~Request()
{
    _pusher.close();
}

void Request::send(MetricUpdate const &message)
{
    std::string buffer;

    if (message.IsInitialized() && message.SerializeToString(&buffer))
        _pusher.send(buffer);
}