#include <ground_station.hpp>

GroundStation::GroundStation() {
    application = Gtk::Application::create();
}

int GroundStation::run(Graphics& graphics) {
    return application->run(graphics);
}

void GroundStation::quit() {
    application->quit();
}