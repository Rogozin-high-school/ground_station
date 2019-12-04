#pragma once
#include <ground_station.hpp>
#include <gtkmm/application.h>

class Graphics {
public:
    Graphics(GroundStation& groundStation);

    void quit();
private:
    int width, height;
    GroundStation& groundStation;

    Glib::RefPtr<Gtk::Application> application;
};