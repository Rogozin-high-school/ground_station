#include <FrontEnd/Pages/Settings.hpp>
#include <FrontEnd.hpp>
#include <gtkmm/box.h>
#include <gtkmm/image.h>

namespace FrontEnd::Pages
{

void Settings::load(Gtk::Notebook *pNotebook)
{
    auto pPage = Gtk::manage(new Gtk::Box);
    auto pIcon = Gtk::manage(new Gtk::Image(SCALE(Resources::Pixbufs::pIconGears, 96)));
    pNotebook->append_page(*pPage, *pIcon);
}

} // namespace FrontEnd::Pages