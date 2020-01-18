#include <FrontEnd.hpp>
#include <FrontEnd/Logger.hpp>
#include <FrontEnd/Window.hpp>

#include <gtkmm/application.h>
#include <gtkmm/cssprovider.h>

namespace FrontEnd::Resources::Pixbufs
{
// Link these resources that were declared in <FrontEnd.hpp>
Glib::RefPtr<Gdk::Pixbuf>
    pIconGroundStation,
    pIconConsole,
    pIconGears;
} // namespace FrontEnd::Resources::Pixbufs

Glib::RefPtr<Gtk::Application>
    pApplication;

void load_CSS();
Glib::RefPtr<Gdk::Pixbuf> scale_image();

void FrontEnd::initialize()
{
    pApplication = Gtk::Application::create();

    // Initialize the logger
    Logger::initialize();

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
    pApplication->run(window);
}

void FrontEnd::quit()
{
    // Destroy the logger
    Logger::quit();

    pApplication->quit();
}

inline void load_CSS()
{
    auto pScreen = Gdk::Screen::get_default();
    auto pCSSProvider = Gtk::CssProvider::create();
    Gtk::StyleContext::add_provider_for_screen(pScreen, pCSSProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    pCSSProvider->load_from_path(FrontEnd::Resources::Paths::CSSProvider);
}