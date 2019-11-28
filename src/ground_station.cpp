#include <ground_station.hpp>
#include <server.hpp>

GroundStation::GroundStation() {
    application = Gtk::Application::create();
}

int GroundStation::run(Graphics& graphics) {
    Server server;
    server.run();
    return application->run(graphics);
}

void GroundStation::quit() {
    application->quit();
}