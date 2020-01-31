#include <BackEnd/ServerSocket.hpp>
#include <stdexcept>
#include <unistd.h>

static BackEnd::SocketFd socketFd = -1;
static BackEnd::SocketAddress socketAddress;

BackEnd::ServerSocket::ServerSocket(int port)
    : port(port)
{
    socketAddress = {AF_INET, htons(port), {INADDR_ANY}};
}

void BackEnd::ServerSocket::server_open_socket() const
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1) 
    {
        throw std::runtime_error("Unable to open socket!");
    }
}

void BackEnd::ServerSocket::server_bind() const
{
    auto pSocketAddress = reinterpret_cast<const sockaddr *>(&socketAddress);
    auto result = bind(socketFd, pSocketAddress, sizeof(SocketAddress));
    if (result == -1) 
    {
        throw std::runtime_error("Unable to bind socket to address!");
    }
}

void BackEnd::ServerSocket::server_listen(int maxClients) const
{
    if (listen(socketFd, maxClients) == -1)
    {
        throw std::runtime_error("Unable to listen to the socket!");
    }
}

void BackEnd::ServerSocket::server_set_timeout(suseconds_t timeoutMicros) const
{
    timeval timeout = {timeoutMicros / 1000000, timeoutMicros % 1000000};
    if (setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO | SO_SNDTIMEO, &timeout, sizeof(timeval)) == -1)
    {
        throw std::runtime_error("Unable to set socket timeout!");
    }
}

BackEnd::ClientSocket BackEnd::ServerSocket::server_accept() const
{
    SocketAddress clientSocketAddress;
    socklen_t addressSize = sizeof(SocketAddress);
    auto pClientSocketAddress = reinterpret_cast<sockaddr *>(&clientSocketAddress);
    
    SocketFd clientSocketFd = accept(socketFd, pClientSocketAddress, &addressSize);
    if (clientSocketFd == -1) 
    {
        throw std::runtime_error("Can't accept new connection!");
    }

    return ClientSocket(clientSocketFd, clientSocketAddress);
}

void BackEnd::ServerSocket::server_close() const
{
    if (socketFd != -1)
    {
        shutdown(socketFd, SHUT_RDWR);
        close(socketFd);
    }
}
