#pragma once
#include <BackEnd/ClientSocket.hpp>

namespace BackEnd::Clients
{

struct Satellite
{
    static const bool &isConnected;
    
    static void run(const ClientSocket &clientSocket);
    static void die();
};

extern Satellite satellite;

} // namespace BackEnd::Clients