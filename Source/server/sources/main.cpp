/*
** Created by Gaston Siffert
*/

#include <map>
#include <list>
#include <thread>

#include "Server.h"
#include "DataWorker.h"
#include "AlertWorker.h"

#define HELPER      "./server (standalone|cluster)"
#define STANDALONE  "standalone"
#define CLUSTER     "cluster"
#define LOCALHOST   "localhost"
#define POOL_SIZE   2

typedef void (*option)();

static void cluster()
{
}

/*
** Standalone version, run a main thread with the Server
** and run several thread as Worker
*/

static void runAlertWorker(zmqpp::context const *context)
{
    AlertWorker worker(*context, LOCALHOST);
    worker.run();
}

static void runDataWorker(zmqpp::context const *context)
{
    DataWorker worker(*context, LOCALHOST);
    worker.run();
}

static void standalone()
{
    zmqpp::context context;
    Server server(context);
    std::list<std::thread> pool;

    for (int i = 0; i < POOL_SIZE; ++i)
        pool.push_back(std::thread(runDataWorker, &context));
    for (int i = 0; i < POOL_SIZE; ++i)
        pool.push_back(std::thread(runAlertWorker, &context));    
    
    server.run();
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << HELPER << std::endl;
        return -1;
    }
    std::map<std::string, option> options;
    options[STANDALONE] = &standalone;
    options[CLUSTER] = &cluster;

    if (options.find(argv[1]) != options.end())
        options[argv[1]]();
    else
    {
        std::cout << HELPER << std::endl;
        return -1;
    }
    return 0;
}
