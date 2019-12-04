#pragma once
#include <graphics.hpp>
#include <gtkmm/window.h>
#include <gtkmm/glarea.h>

class Window : public Gtk::Window {
public:
    Window(Graphics *pGraphics);
protected:
    bool on_key_press_event(GdkEventKey *event) override;
private:
    Graphics& graphics;
};

class GLArea : public Gtk::GLArea {
protected:
    bool on_render(const Glib::RefPtr<Gdk::GLContext>& context) override;
};