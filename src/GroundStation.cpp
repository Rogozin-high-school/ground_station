#include <GroundStation.hpp>
#include <FrontEnd.hpp>
#include <BackEnd.hpp>

int main()
{
    GroundStation::initialize();
    GroundStation::run();

    // Shouldn't call GroundStation::quit(),
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
