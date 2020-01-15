#include <FrontEnd/Pages/Settings.hpp>
#include <FrontEnd.hpp>

#include <gtkmm/box.h>
#include <gtkmm/image.h>

void FrontEnd::Pages::Settings::load(Gtk::Notebook &notebook)
{
    static Gtk::Box page;
    static Gtk::Image icon(Resources::Pixbufs::iconGears->scale_simple(96, 96, Gdk::INTERP_BILINEAR));
    notebook.append_page(page, icon);
}
