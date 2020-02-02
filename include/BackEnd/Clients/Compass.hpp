#pragma once
#include <BackEnd/ClientSocket.hpp>

namespace BackEnd::Clients
{

struct Compass
{
    static const bool &isConnected;
    
    static void run(const ClientSocket &clientSocket);
    static void die();
};

extern Compass compass;

} // namespace BackEnd::Clients