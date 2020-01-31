#include <GroundStation.hpp>
#include <FrontEnd.hpp>
#include <BackEnd.hpp>

int main()
{
    GroundStation::initialize();
    GroundStation::run();
}

void GroundStation::initialize()
{
    BackEnd::initialize();
    FrontEnd::initialize();
}

void GroundStation::run()
{
    BackEnd::run();
    FrontEnd::run();
}
