#include <FrontEnd/Pages/Satellite.hpp>
#include <FrontEnd.hpp>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <iostream>

namespace FrontEnd::Pages
{

static Gtk::Widget *pPage;
static Gtk::Widget *pIcon;

void Satellite::load()
{
    // Don't use Gtk::manage() here, it doesn't work well!
    pPage = new Gtk::Box;
    pIcon = new Gtk::Image(SCALE(Resources::Pixbufs::pIconSatellite, 96));
    pNotebook->append_page(*pPage, *pIcon);
    pNotebook->show_all();
}

void Satellite::unload()
{
    pNotebook->remove_page(*pPage);
    delete pPage;
    delete pIcon;
}

} // namespace FrontEnd::Pages