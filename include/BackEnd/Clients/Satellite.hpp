#pragma once
#include <BackEnd/ClientSocket.hpp>

namespace BackEnd::Clients
{

struct Satellite
{
    static void run(const ClientSocket &clientSocket);
    static void die();
    static bool is_connected();
};

} // namespace BackEnd::Clients