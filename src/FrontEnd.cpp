#include <FrontEnd.hpp>
#include <FrontEnd/Window.hpp>
#include <gtkmm/application.h>
#include <gtkmm/cssprovider.h>

namespace FrontEnd::Resources::Pixbufs
{
// Link these resources that were declared in <FrontEnd.hpp>
Glib::RefPtr<Gdk::Pixbuf>
    iconGroundStation,
    iconConsole,
    iconGears;
} // namespace FrontEnd::Resources::Pixbufs


Glib::RefPtr<Gtk::Application>
    application;

void load_CSS();
Glib::RefPtr<Gdk::Pixbuf> scale_image();

void FrontEnd::initialize()
{
    application = Gtk::Application::create();

    // Now only after the application is created, can you allocate memory for UI stuff.
    Resources::Pixbufs::load();
    load_CSS();
}

void FrontEnd::run()
{
    Window window;

    // application->run runs on the main thread, hence it pauses the thread;
    // Thus, the window created here will not deallocate as long as the front-end is running,
    // and therefore there is no need for static/dynamic allocation for the window.
    application->run(window);
}

void FrontEnd::quit()
{
    application->quit();
}

inline void load_CSS()
{
    auto screen = Gdk::Screen::get_default();
    auto CSSProvider = Gtk::CssProvider::create();
    Gtk::StyleContext::add_provider_for_screen(screen, CSSProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    CSSProvider->load_from_path(FrontEnd::Resources::Paths::CSSProvider);
}