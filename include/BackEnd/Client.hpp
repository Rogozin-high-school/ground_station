#pragma once
#include <BackEnd/ClientSocket.hpp>

namespace BackEnd
{
struct Client
{
    enum class Type : uint8_t
    {
        Satellite = 0x01,
        Phone = 0x02,
        Compass = 0x03,
        PowerSupplies = 0x04,
        None = 0x00
    };

    const ClientSocket clientSocket;
    Type type;

    Client(const ClientSocket &clientSocket);
    Client(const Client& client);

    bool operator==(const Client& client);
    Client& operator=(const Client&);
};
} // namespace BackEnd