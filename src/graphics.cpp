#include <graphics.hpp>
#include <windows.hpp>
#include <gdkmm/screen.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>

Graphics::Graphics(GroundStation& groundStation) : groundStation(groundStation)
{
    application = Gtk::Application::create();
    {
        auto screen = Gdk::Screen::get_default();
        {
            auto css = Gtk::CssProvider::create();
            Gtk::StyleContext::add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            css->load_from_resource("/style.css");
        }
        width = screen->get_width();
        height = screen->get_height();
    }
    Window window(this);
    application->run(window);
}

void Graphics::quit() {
    // groundStation.quit();
    application->quit();
}
