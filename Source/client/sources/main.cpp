/*
** Created by Gaston Siffert
*/

#include <unistd.h>
#include <iostream>

#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>

#include "Request.h"
#include "SigarWrapper.h"

#define USAGE "./client $KeyName $ServerHost"

/*
** Analyze the machine system's usage
** and produce a MetricUpdate to send to
** the remote server
*/
static MetricUpdate analyze()
{
    MetricUpdate message;

    float cpu = SigarWrapper::getCpu();
    float memory = SigarWrapper::getMemory();
    int processes = SigarWrapper::getProcesses();
    if (cpu >= 0.0)
        message.set_cpu(cpu);
    if (memory >= 0.0)
        message.set_memory(memory);
    if (processes >= 0)
        message.set_processes(processes);

    return message;
}

int main(int argc, char **argv)
{
    zmqpp::context context;

    if (argc != 3)
    {
        std::cout << USAGE << std::endl;
        return -1;
    }

    std::string key = argv[1];
    while (true)
    {
        /*
        ** We use an inner scope to destroy the Request
        ** and close the socket
        */
        {
            Request request(context, argv[2]);
            MetricUpdate message = analyze();
            message.set_key(key);
            request.send(message);
        }
        sleep(5 * 60);
    }
    return 0;
}