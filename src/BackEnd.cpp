#include <BackEnd/Server.hpp>

namespace BackEnd
{

bool isConnected = false;

void initialize()
{
    Server::initialize();
}

void run()
{
    Server::run();
}

void quit()
{
    Server::quit();
}

} // namespace BackEnd