#pragma once
#include <BackEnd.hpp>
#include <BackEnd/Client.hpp>

namespace BackEnd
{
struct Server
{
    static void initialize();
    static void run();
    static void quit();

    static bool is_open();
    static void close_connection_with(const Client &client);
};
} // namespace BackEnd