#pragma once
#include <ground_station.hpp>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

class Graphics {
    class Window : public Gtk::Window {
    public:
        Window(Graphics& graphics) : graphics(graphics)
        {}
    protected:
        bool on_key_press_event(GdkEventKey *event) override;
    private:
        Graphics& graphics;
    };

    class DrawingArea : public Gtk::DrawingArea {
    public:
        DrawingArea(Graphics& graphics) : graphics(graphics)
        {}
    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    private:
        Graphics& graphics;
    };
public:
    int width, height;

    Graphics(GroundStation& groundStation);

    void quit();
private:
    GroundStation& groundStation;

    Glib::RefPtr<Gtk::Application> application;
};