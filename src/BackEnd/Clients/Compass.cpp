#include <BackEnd/Clients/Compass.hpp>
#include <Logger.hpp>

namespace BackEnd::Clients
{

static bool connected = false;
static const ClientSocket *pClientSocket = nullptr;

void Compass::run(const ClientSocket &clientSocket)
{
    if (connected)
    {
        return;
    }
    
    connected = true;
    pClientSocket = &clientSocket;
    Logger::info("Compass has connected!");
    uint8_t buffer[1]; // dummy
    clientSocket.client_recv(buffer, 1);
}

void Compass::die()
{
    if (!connected)
    {
        return;
    }

    connected = false;
    pClientSocket->client_close();
    Logger::info("Compass has disconnected!");
}

bool Compass::is_connected()
{
    return connected;
}

} // namespace BackEnd::Clients