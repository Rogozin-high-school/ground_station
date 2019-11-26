#include <ground_station.hpp>

int main(void) {
    GroundStation groundStation;
    Graphics graphics(groundStation);
    return groundStation.run(graphics);
}