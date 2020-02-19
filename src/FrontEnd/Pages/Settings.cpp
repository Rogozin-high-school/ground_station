#include <FrontEnd/Pages/Settings.hpp>
#include <FrontEnd.hpp>
#include <gtkmm/box.h>
#include <gtkmm/image.h>

namespace FrontEnd::Pages
{

static Gtk::Widget *pPage;
static Gtk::Widget *pIcon;

void Settings::load()
{
    pPage = Gtk::manage(new Gtk::Box);
    pIcon = Gtk::manage(new Gtk::Image(SCALE(Resources::Pixbufs::pIconGears, 96)));
    pNotebook->append_page(*pPage, *pIcon);
    pNotebook->show_all();
}

} // namespace FrontEnd::Pages