#pragma once
#include <gtkmm/window.h>

class GroundStation;

class Graphics : public Gtk::Window {
public:
    Graphics(GroundStation& groundStation);
protected:
    bool on_key_press_event(GdkEventKey *event) override;
private:
    GroundStation& groundStation;
};