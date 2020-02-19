#include <BackEnd/Clients/Satellite.hpp>
#include <FrontEnd/Pages/Satellite.hpp>
#include <Logger.hpp>

namespace BackEnd::Clients
{

static bool connected = false;
static const ClientSocket *pClientSocket = nullptr;

void Satellite::run(const ClientSocket &clientSocket)
{
    if (connected)
    {
        return;
    }
    
    connected = true;
    pClientSocket = &clientSocket;
    g_idle_add((GSourceFunc)FrontEnd::Pages::Satellite::load, nullptr);
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
    g_idle_add((GSourceFunc)FrontEnd::Pages::Satellite::unload, nullptr);
    Logger::info("Satellite has disconnected!");
}

bool Satellite::is_connected()
{
    return connected;
}

} // namespace BackEnd::Clients