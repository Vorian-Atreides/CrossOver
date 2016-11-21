/*
** Created by Gaston Siffert
*/

#include "Request.h"

Request::Request(zmqpp::context const &context, std::string const &serverHost) :
    _pusher(context, zmqpp::socket_type::push)
{
    _pusher.connect("tcp://" + serverHost + ":4000");
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