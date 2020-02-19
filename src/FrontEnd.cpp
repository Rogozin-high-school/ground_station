#include <FrontEnd.hpp>
#include <FrontEnd/Window.hpp>
#include <gtkmm/application.h>
#include <gtkmm/cssprovider.h>

namespace FrontEnd
{

Gtk::Notebook *pNotebook;
bool isRunning;

namespace Resources::Paths
{

const Glib::ustring
    CSSProvider = "res/style.css",
    iconGroundStation = "res/ground_station.png",
    iconConsole = "res/console.png",
    iconSatellite = "res/satellite.png",
    iconGears = "res/gears.png";

} // namespace Resources::Paths

namespace Resources::Pixbufs
{
// Link these resources that were declared in <FrontEnd.hpp>
Glib::RefPtr<Gdk::Pixbuf>
    pIconGroundStation,
    pIconConsole,
    pIconSatellite,
    pIconGears;

static void load()
{
    pIconGroundStation = Gdk::Pixbuf::create_from_file(Paths::iconGroundStation);
    pIconConsole = Gdk::Pixbuf::create_from_file(Paths::iconConsole);
    pIconSatellite = Gdk::Pixbuf::create_from_file(Paths::iconSatellite);
    pIconGears = Gdk::Pixbuf::create_from_file(Paths::iconGears);
}

} // namespace Resources::Pixbufs

static Glib::RefPtr<Gtk::Application> pApplication;

static void load_CSS();

void initialize()
{
    pApplication = Gtk::Application::create();

    // Now only after the application is created, can you allocate memory for UI stuff.
    Resources::Pixbufs::load();
    load_CSS();
}

void run()
{
    Window window;
    isRunning = true;

    // application->run runs on the main thread, hence it pauses the thread;
    // Thus, the window created here will not deallocate as long as the front-end is running,
    // and therefore there is no need for static/dynamic allocation for the window.
    pApplication->run(window);
}

void quit()
{
    pApplication->quit();
}

void load_CSS()
{
    auto pScreen = Gdk::Screen::get_default();
    auto pCSSProvider = Gtk::CssProvider::create();
    Gtk::StyleContext::add_provider_for_screen(pScreen, pCSSProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    pCSSProvider->load_from_path(Resources::Paths::CSSProvider);
}

} // namespace FrontEnd