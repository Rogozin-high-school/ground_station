#include <BackEnd/Clients/Satellite.hpp>
#include <Logger.hpp>

namespace BackEnd::Clients
{

static bool connected = false;
static const ClientSocket *pClientSocket = nullptr;

const bool &Satellite::isConnected = connected;
    
Satellite satellite;

void Satellite::run(const ClientSocket &clientSocket)
{
    if (connected)
    {
        return;
    }
    
    connected = true;
    pClientSocket = &clientSocket;
    Logger::info("Satellite has connected!");
    uint8_t buffer[1]; // dummy
    clientSocket.client_recv(buffer, 1);
}

void Satellite::die()
{
    if (!connected)
    {
        return;
    }

    connected = false;
    pClientSocket->client_close();
    Logger::info("Satellite has disconnected!");
}

} // namespace BackEnd::Clients