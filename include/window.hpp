#pragma once
#include <graphics.hpp>
#include <gtkmm/window.h>

class Window : public Gtk::Window {
public:
    Window(Graphics *pGraphics);
protected:
    bool on_key_press_event(GdkEventKey *event) override;
private:
    Graphics& graphics;
};