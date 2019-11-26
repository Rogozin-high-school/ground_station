#pragma once
#include <graphics.hpp>
#include <gtkmm/application.h>

class GroundStation {
public:
    GroundStation();

    int run(Graphics& graphics);
    void quit();
private:
    Glib::RefPtr<Gtk::Application> application;
};