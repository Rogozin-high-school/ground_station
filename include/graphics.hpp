#pragma once
#include <ground_station.hpp>
#include <gtkmm.h>

class Graphics
{
public:
    Graphics(GroundStation &groundStation);

    void quit();

private:
    GroundStation &groundStation;

    Glib::RefPtr<Gtk::Application> pApplication;
};

class Window : public Gtk::Window
{
public:
    Window(Graphics *pGraphics);

protected:
    bool on_key_press_event(GdkEventKey *event) override;

private:
    Graphics &graphics;
};

class GLArea : public Gtk::GLArea
{
protected:
    bool on_render(const Glib::RefPtr<Gdk::GLContext> &context) override;
};