#pragma once
#include <ground_station.hpp>
#include <gtkmm/application.h>

class Graphics {
public:
    int width, height;
    Graphics(GroundStation& groundStation);

    void quit();
private:
    GroundStation& groundStation;

    Glib::RefPtr<Gtk::Application> application;
};