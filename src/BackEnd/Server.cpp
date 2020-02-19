#include <BackEnd/Server.hpp>
#include <BackEnd/ServerSocket.hpp>
#include <BackEnd/Clients/Satellite.hpp>
#include <BackEnd/Clients/Phone.hpp>
#include <BackEnd/Clients/Compass.hpp>
#include <BackEnd/Clients/PowerSupplies.hpp>
#include <Logger.hpp>
#include <thread>

namespace BackEnd
{

static constexpr int maxClients = 1;
static constexpr int port = 8888;

static bool isOpen = false;
static ServerSocket serverSocket(port);

static void host();
static void create_client(const ClientSocket &clientSocket);

void Server::initialize()
{
    Logger::verbose("Server is ready!");
    isOpen = true;
}

void Server::run()
{
    serverSocket.server_open_socket();
    serverSocket.server_bind();
    serverSocket.server_listen(maxClients);
    std::thread thread(host);
    thread.detach();
}

void Server::quit()
{
    isOpen = false;
    Clients::Satellite::die();
    Clients::Phone::die();
    Clients::Compass::die();
    Clients::PowerSupplies::die();
    serverSocket.server_close();
    Logger::verbose("Server is dead!");
}

bool Server::is_open()
{
    return isOpen;
}

void host()
{
    Logger::info("Server is running on port " + std::to_string(port) + "!");
    while (true)
    {
        try
        {
            std::thread thread(create_client, serverSocket.server_accept());
            thread.detach();
        }
        catch (const std::exception &ex)
        {
            if (isOpen)
            {
                // Relevant only if the server is still open!
                // Should be thrown when the server shuts down...
                Logger::error(ex.what());
            }
        }
    }
}

void create_client(const ClientSocket &clientSocket)
{
    Logger::verbose("Handshake from " + clientSocket.ip + ":" + std::to_string(clientSocket.port));

    constexpr int timeoutMicros = 500000;
    clientSocket.client_set_timeout(timeoutMicros);

    uint8_t buffer[sizeof(ClientType)];
    if (Server::is_open() && clientSocket.client_recv(buffer, sizeof(buffer)) <= 0)
    {
        Logger::verbose("Didn't receive any response from " + clientSocket.ip + ":" +
                        std::to_string(clientSocket.port) + " in " + std::to_string(timeoutMicros) + "μs!");
        clientSocket.client_close();
        return;
    }

    clientSocket.client_set_timeout(0);

    switch (*buffer)
    {
        // run() doesn't open a new thread!
    case uint8_t(ClientType::Satellite):
        Clients::Satellite::run(clientSocket);
        Clients::Satellite::die();
        return;
    case uint8_t(ClientType::Phone):
        Clients::Phone::run(clientSocket);
        Clients::Phone::die();
        return;
    case uint8_t(ClientType::Compass):
        Clients::Compass::run(clientSocket);
        Clients::Compass::die();
        return;
    case uint8_t(ClientType::PowerSupplies):
        Clients::PowerSupplies::run(clientSocket);
        Clients::PowerSupplies::die();
        return;
    }
}

} // namespace BackEnd