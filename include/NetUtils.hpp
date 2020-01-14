#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>

#include <optional>
#include <string>
#include <array>

namespace NetUtils
{
using SocketFd = int;
using SocketAddress = sockaddr_in;

constexpr int socketErrorCode = -1;

auto SocketError = [](const std::string msg) {
    std::string err = strerror(errno);
    return std::runtime_error(msg + " [" + err + "]");
};

class ClientSocket
{
public:
    const std::string &IP = ip;

    explicit ClientSocket(SocketFd socketFd, SocketAddress socketAddress)
        : socketFd(socketFd), socketAddress(socketAddress)
    {
        char buffer[22] = {0};
        inet_ntop(AF_INET, &socketAddress.sin_addr, buffer, sizeof(buffer));
        ip = buffer;
    }

    void SetTimeout(long seconds, long micros) const
    {
        timeval timeout = {seconds, micros};
        if (setsockopt(socketFd, SOL_SOCKET, SO_SNDTIMEO | SO_RCVTIMEO, &timeout, sizeof(timeval)) == socketErrorCode)
        {
            throw SocketError("Unable to set socket timeout!");
        }
    }

    template <size_t N, class Byte = char>
    const std::optional<std::array<Byte, N>> Receive() const
    {
        static_assert(N > 0 && N <= 1024);
        static_assert(std::is_same_v<Byte, char> || std::is_same_v<Byte, unsigned char>);
        std::array<Byte, N> buffer;
        if (recv(socketFd, buffer.begin(), N, 0) > 0)
        {
            return buffer;
        }
        return std::nullopt;
    }

    template <size_t N, class Byte = char>
    bool Send(const std::array<Byte, N> &buffer) const
    {
        static_assert(N > 0 && N <= 1024);
        static_assert(std::is_same_v<Byte, char> || std::is_same_v<Byte, unsigned char>);
        return send(socketFd, buffer.begin(), N, 0) > 0;
    }

    template <class T>
    static void ltob(T begin, T end)
    {
        while ((begin != end) && (begin != --end))
        {
            std::iter_swap(begin++, end);
        }
    }

    void Close() const
    {
        shutdown(socketFd, SHUT_RDWR);
        close(socketFd);
    }

private:
    SocketFd socketFd;
    SocketAddress socketAddress;
    std::string ip;
};

class ServerSocket
{
public:
    const int port;

    explicit ServerSocket(int port) : socketAddress{
                                          AF_INET,     // sin_family
                                          htons(port), // sin_port
                                          {INADDR_ANY} // sin_addr
                                      },
                                      port(port)
    {
    }

    ~ServerSocket()
    {
        if (socketFd != socketErrorCode)
        {
            close(socketFd);
        }
    }

    void Open()
    {
        socketFd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFd == socketErrorCode)
        {
            throw SocketError("Unable to open socket!");
        }
    }

    void Bind() const
    {
        auto pSocketAddress = reinterpret_cast<const sockaddr *>(&socketAddress);
        auto result = bind(socketFd, pSocketAddress, sizeof(SocketAddress));
        if (result == socketErrorCode)
        {
            throw SocketError("Unable to bind socket to address!");
        }
    }

    void Listen(int maxConnections) const
    {
        auto result = listen(socketFd, maxConnections);
        if (result == socketErrorCode)
        {
            throw SocketError("Unable to listen to the socket!");
        }
    }

    template <int seconds = 0, int micros = 0>
    void SetTimeout() const
    {
        static_assert(seconds > 0 && micros > 0);
        timeval timeout = {seconds, micros};
        bool b1 = setsockopt(socketFd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeval)) == socketErrorCode;
        bool b2 = setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeval)) == socketErrorCode;
        if (b1 || b2)
        {
            throw SocketError("Unable to set socket timeout!");
        }
    }

    ClientSocket Accept()
    {
        SocketAddress clientSocketAddress;
        socklen_t addressSize = sizeof(SocketAddress);
        auto pClientSocketAddress = reinterpret_cast<sockaddr *>(&clientSocketAddress);

        SocketFd clientSocketFd = accept(socketFd, pClientSocketAddress, &addressSize);
        if (clientSocketFd == socketErrorCode)
        {
            throw SocketError("Can't accept new connection!");
        }

        return ClientSocket(clientSocketFd, clientSocketAddress);
    }

private:
    SocketFd socketFd = socketErrorCode;
    SocketAddress socketAddress;
};
} // namespace NetUtils
