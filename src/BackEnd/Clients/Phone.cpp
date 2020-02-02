#include <BackEnd/Clients/Phone.hpp>
#include <Logger.hpp>

namespace BackEnd::Clients
{

static bool connected = false;
static const ClientSocket *pClientSocket = nullptr;

const bool &Phone::isConnected = connected;
    
Phone phone;

void Phone::run(const ClientSocket &clientSocket)
{
    if (connected)
    {
        return;
    }

    connected = true;
    pClientSocket = &clientSocket;
    Logger::info("Phone has connected!");
    uint8_t buffer[1]; // dummy
    clientSocket.client_recv(buffer, 1);
}

void Phone::die()
{
    if (!connected)
    {
        return;
    }

    connected = false;
    pClientSocket->client_close();
    Logger::info("Phone has disconnected!");
}

} // namespace BackEnd::Clients