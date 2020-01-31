#include <BackEnd/ClientSocket.hpp>
#include <BackEnd/Server.hpp>
#include <Logger.hpp>
#include <thread>

static void communicate(const BackEnd::Client &client);

BackEnd::Client::Client(const ClientSocket &clientSocket)
    : clientSocket(clientSocket)
{
    Logger::verbose("Handshake with " + clientSocket.ip + "!");
    std::thread thread(communicate, *this);
    thread.detach();
}

BackEnd::Client::Client(const Client &client)
    : clientSocket(client.clientSocket)
{
}

bool BackEnd::Client::operator==(const Client &client)
{
    return this->clientSocket.ip == client.clientSocket.ip;
}

BackEnd::Client &BackEnd::Client::operator=(const Client &)
{
    return *this;
}

void communicate(const BackEnd::Client &client)
{
    Logger::verbose(client.clientSocket.ip + " -> Waiting for dummy input...");

    char buffer[1024];
    recv(client.clientSocket.get_socket_fd(), buffer, sizeof(buffer), 0);

    if (BackEnd::Server::is_open())
    {
        Logger::verbose(client.clientSocket.ip + " -> EOF!");
        BackEnd::Server::close_connection_with(client);
    }
}
