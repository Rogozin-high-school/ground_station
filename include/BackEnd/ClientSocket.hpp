#pragma once
#include <BackEnd.hpp>
#include <glibmm/ustring.h>

namespace BackEnd
{
struct ClientSocket
{
    const Glib::ustring ip;

    ClientSocket(SocketFd socketFd, SocketAddress socketAddress);

    void client_set_timeout(suseconds_t timeoutMicros) const;
    void client_close() const;

    SocketFd get_socket_fd() const;
    const SocketAddress &get_socket_address() const;
};
} // namespace BackEnd