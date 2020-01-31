#include <BackEnd.hpp>
#include <BackEnd/Server.hpp>

bool BackEnd::isConnected = false;

void BackEnd::initialize()
{
    Server::initialize();
}

void BackEnd::run()
{
    Server::run();
}

void BackEnd::quit()
{
    Server::quit();
}