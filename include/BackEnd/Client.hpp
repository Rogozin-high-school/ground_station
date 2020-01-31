#pragma once
#include <BackEnd/ClientSocket.hpp>

namespace BackEnd
{
struct Client
{
    const ClientSocket clientSocket;

    Client(const ClientSocket &clientSocket);
    Client(const Client& client);

    bool operator==(const Client& client);
    Client& operator=(const Client&);
};
} // namespace BackEnd