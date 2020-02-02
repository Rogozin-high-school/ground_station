#include <BackEnd/Clients/PowerSupplies.hpp>
#include <Logger.hpp>

namespace BackEnd::Clients
{

static bool connected = false;
static const ClientSocket *pClientSocket = nullptr;

const bool &PowerSupplies::isConnected = connected;

PowerSupplies powerSupplies;

void PowerSupplies::run(const ClientSocket &clientSocket)
{
    if (connected)
    {
        return;
    }
    
    connected = true;
    pClientSocket = &clientSocket;
    Logger::info("PowerSupplies has connected!");
    uint8_t buffer[1]; // dummy
    clientSocket.client_recv(buffer, 1);
}

void PowerSupplies::die()
{
    if (!connected)
    {
        return;
    }

    connected = false;
    pClientSocket->client_close();
    Logger::info("PowerSupplies has disconnected!");
}

} // namespace BackEnd::Clients