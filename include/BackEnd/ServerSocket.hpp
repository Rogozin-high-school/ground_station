#pragma once
#include <BackEnd/ClientSocket.hpp>
#include <sys/time.h>

namespace BackEnd
{
struct ServerSocket
{
    const int port;

    ServerSocket(int port);

    void server_open_socket() const;
    void server_bind() const;
    void server_listen(int maxClients) const;
    void server_set_timeout(suseconds_t timeoutMicros) const;
    ClientSocket server_accept() const;
    void server_close() const;
};
} // namespace BackEnd