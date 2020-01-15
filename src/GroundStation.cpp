#include <GroundStation.hpp>
#include <BackEnd.hpp>
#include <FrontEnd.hpp>

int main()
{
    GroundStation::initialize();
    GroundStation::run();

    // No need to call GroundStation::quit(),
    // since the program quits only when the user desires it.
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

void GroundStation::quit()
{
    BackEnd::quit();
    FrontEnd::quit();
}