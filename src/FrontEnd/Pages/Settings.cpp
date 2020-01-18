#include <FrontEnd/Pages/Settings.hpp>
#include <FrontEnd.hpp>

#include <gtkmm/box.h>
#include <gtkmm/image.h>

void FrontEnd::Pages::Settings::load(Gtk::Notebook *pNotebook)
{
    auto pPage = Gtk::manage(new Gtk::Box);
    auto pIcon = Gtk::manage(new Gtk::Image(Resources::Pixbufs::pIconGears->scale_simple(96, 96, Gdk::INTERP_BILINEAR)));
    pNotebook->append_page(*pPage, *pIcon);
}
