#include <BackEnd/Server.hpp>
#include <BackEnd/ServerSocket.hpp>
#include <Logger.hpp>
#include <vector>
#include <thread>
#include <algorithm>

static constexpr int maxClients = 1;
static constexpr int port = 8888;

static bool isOpen = false;
static BackEnd::ServerSocket serverSocket(port);
static std::vector<BackEnd::Client> clients;

static void host();

void BackEnd::Server::initialize()
{
    Logger::verbose("Server is ready!");
    isOpen = true;
}

void BackEnd::Server::run()
{
    serverSocket.server_open_socket();
    serverSocket.server_bind();
    serverSocket.server_listen(maxClients);
    std::thread thread(host);
    thread.detach();
}

void BackEnd::Server::quit()
{
    isOpen = false;
    for (const Client &client : clients)
    {
        close_connection_with(client);
    }
    Logger::verbose("Server is dead!");
}

bool BackEnd::Server::is_open()
{
    return isOpen;
}

void BackEnd::Server::close_connection_with(const Client &client)
{
    client.clientSocket.client_close();
    Logger::info(client.clientSocket.ip + " -> Closed connection!");
    clients.erase(std::remove(clients.begin(), clients.end(), client));
}

void host()
{
    Logger::info("Server is running on port " + std::to_string(port) + "!");
    while (clients.size() < maxClients)
    {
        try 
        {
            clients.push_back(serverSocket.server_accept());
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