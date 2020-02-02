#include <BackEnd/ClientSocket.hpp>
#include <Logger.hpp>
#include <unistd.h>

namespace BackEnd
{

static SocketFd socketFd;
static SocketAddress socketAddress;

static Glib::ustring load_ip(const SocketAddress &socketAddress);
static int load_port(const SocketAddress &socketAddress);

ClientSocket::ClientSocket(SocketFd _socketFd, SocketAddress _socketAddress)
    : ip(load_ip(_socketAddress)), port(load_port(_socketAddress))
{
    socketFd = _socketFd;
    socketAddress = _socketAddress;
}

ssize_t ClientSocket::client_recv(uint8_t *buffer, size_t size) const
{
    return recv(socketFd, buffer, size, 0);
}

void ClientSocket::client_set_timeout(suseconds_t timeoutMicros) const
{
    timeval timeout = {timeoutMicros / 1000000, timeoutMicros % 1000000};
    if (setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeval)) == -1)
    {
        throw std::runtime_error("Unable to set socket timeout!");
    }
}

void ClientSocket::client_close() const
{
    if (socketFd != -1)
    {
        shutdown(socketFd, SHUT_RDWR);
        close(socketFd);
    }
}

SocketFd ClientSocket::get_socket_fd() const
{
    return socketFd;
}

const SocketAddress &ClientSocket::get_socket_address() const
{
    return socketAddress;
}

Glib::ustring load_ip(const SocketAddress &socketAddress)
{
    char buffer[16];
    inet_ntop(AF_INET, &socketAddress.sin_addr, buffer, sizeof(buffer));
    return buffer;
}

int load_port(const SocketAddress &socketAddress)
{
    return htons(socketAddress.sin_port);
}

} // namespace BackEnd