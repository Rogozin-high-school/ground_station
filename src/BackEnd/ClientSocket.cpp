#include <BackEnd/ClientSocket.hpp>
#include <Logger.hpp>
#include <unistd.h>

static BackEnd::SocketFd socketFd; 
static BackEnd::SocketAddress socketAddress;

static Glib::ustring load_ip(const BackEnd::SocketAddress &socketAddress);

BackEnd::ClientSocket::ClientSocket(SocketFd _socketFd, SocketAddress _socketAddress)
    : ip(load_ip(_socketAddress))
{
    socketFd = _socketFd;
    socketAddress = _socketAddress;
}

ssize_t BackEnd::ClientSocket::client_recv(uint8_t *buffer, size_t size) const
{
    return recv(socketFd, buffer, size, 0);
}

void BackEnd::ClientSocket::client_set_timeout(suseconds_t timeoutMicros) const
{
    timeval timeout = {timeoutMicros / 1000000, timeoutMicros % 1000000};
    if (setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeval)) == -1)
    {
        throw std::runtime_error("Unable to set socket timeout!");
    }
}

void BackEnd::ClientSocket::client_close() const
{
    if (socketFd != -1)
    {
        shutdown(socketFd, SHUT_RDWR);
        close(socketFd);
    }
}

BackEnd::SocketFd BackEnd::ClientSocket::get_socket_fd() const
{
    return socketFd;
}

const BackEnd::SocketAddress &BackEnd::ClientSocket::get_socket_address() const
{
    return socketAddress;
}

Glib::ustring load_ip(const BackEnd::SocketAddress &socketAddress)
{
    char buffer[16];
    inet_ntop(AF_INET, &socketAddress.sin_addr, buffer, sizeof(buffer));
    return buffer;
}