#pragma once
#include <ground_station.hpp>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/table.h>
#include <gtkmm/box.h>
#include <gtkmm/glarea.h>
#include <gtkmm/expander.h>

class Graphics {
public:
    Graphics(GroundStation& groundStation);

    void quit();
private:
    GroundStation& groundStation;

    Glib::RefPtr<Gtk::Application> pApplication;
};

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

class PanelRevealer : public Gtk::Expander {
public:
    enum class Side : uint8_t {
        Left, Right
    };

    PanelRevealer(Side side, bool expanded) : side(side) {
        set_expanded(expanded);
    }
protected:
    bool on_button_release_event(GdkEventButton* event) override;
private:
    Side side;
};