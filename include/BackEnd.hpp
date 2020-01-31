#pragma once
#include <arpa/inet.h>
#include <sys/socket.h>

namespace BackEnd
{
using SocketFd = int;
using SocketAddress = sockaddr_in;

extern bool isConnected;

void initialize();
void run();
void quit();
} // namespace BackEnd