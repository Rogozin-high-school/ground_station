#include <FrontEnd.hpp>
#include <FrontEnd/Window.hpp>
#include <FrontEnd/Pages/CLI.hpp>
#include <FrontEnd/Pages/Satellite.hpp>
#include <FrontEnd/Pages/Settings.hpp>
#include <Logger.hpp>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

namespace FrontEnd
{

static Gtk::Box *pLayout;

static void build_layout(Window *pWindow);
static void build_title_bar();
static void build_notebook();

Window::Window()
{
    set_default_icon(Resources::Pixbufs::pIconGroundStation);
    {
        auto pScreen = Gdk::Screen::get_default();
        int nMonitors = pScreen->get_n_monitors();
        fullscreen_on_monitor(pScreen, nMonitors - 1); // Last monitor
    }
    build_layout(this);
    show_all();
}

void build_layout(Window *pWindow)
{
    pLayout = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    build_title_bar();
    build_notebook();
    pWindow->add(*pLayout);
}

void build_title_bar()
{
    auto pTitleBar = Gtk::manage(new Gtk::Box);
    auto pTitleBarInner = Gtk::manage(new Gtk::Box);

    auto pIconPixbuf = SCALE(Resources::Pixbufs::pIconGroundStation, 96);
    auto pIcon = Gtk::manage(new Gtk::Image(pIconPixbuf));
    auto pLabel = Gtk::manage(new Gtk::Label("Rogozin's Ground Station"));

    pTitleBar->set_name("title_bar");
    pTitleBar->add(*pTitleBarInner);

    pTitleBarInner->pack_start(*pIcon, Gtk::PACK_SHRINK);
    pTitleBarInner->pack_start(*pLabel, Gtk::PACK_SHRINK);

    pLayout->pack_start(*pTitleBar, Gtk::PACK_SHRINK);
}

void build_notebook()
{
    pNotebook = Gtk::manage(new Gtk::Notebook);
    pNotebook->set_tab_pos(Gtk::POS_LEFT);

    Pages::CLI::load();
    Pages::Settings::load();

    pLayout->pack_start(*pNotebook);
}

} // namespace FrontEnd