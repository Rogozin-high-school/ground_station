#pragma once
#include <BackEnd/ClientSocket.hpp>

namespace BackEnd::Clients
{

struct Phone
{
    static const bool &isConnected;
    
    static void run(const ClientSocket &clientSocket);
    static void die();
};

extern Phone phone;

} // namespace BackEnd::Clients