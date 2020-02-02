#pragma once
#include <BackEnd/ClientSocket.hpp>

namespace BackEnd::Clients
{

struct PowerSupplies
{
    static const bool &isConnected;
    
    static void run(const ClientSocket &clientSocket);
    static void die();
};

extern PowerSupplies powerSupplies;

} // namespace BackEnd::Clients