/*
** Created by Gaston Siffert
*/

#ifndef SERVER_H
#define SERVER_H

#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>

#include "IRunnable.h"

/*
** The server is used as proxy between the client
** and the workers. The server will reception a 
** client notification and then load balance
** a request for a DataWorker and an AlertWorker.
*/
class Server: public IRunnable
{
private:
    zmqpp::socket   _puller;
    zmqpp::socket   _dataPusher;
    zmqpp::socket   _alertPusher;    

public:
    /*
    ** Provide a shared context in the application,
    ** the context is thread safe and multiplex the
    ** socket
    */
    Server(zmqpp::context const &context);
    /*
    ** Create an process independant context
    */
    Server();
    ~Server();

public:
    void run();
};

#endif //SERVER_H
