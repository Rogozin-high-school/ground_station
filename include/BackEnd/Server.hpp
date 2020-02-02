#pragma once
#include <BackEnd.hpp>

namespace BackEnd
{

enum class ClientType : uint8_t
{
    Satellite = 0x01,
    Phone = 0x02,
    Compass = 0x03,
    PowerSupplies = 0x04
};

struct Server
{
    static void initialize();
    static void run();
    static void quit();
    static bool is_open();
};

} // namespace BackEnd