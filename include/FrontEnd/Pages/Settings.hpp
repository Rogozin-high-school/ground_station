#pragma once
#include <gtkmm/notebook.h>

namespace FrontEnd::Pages
{

struct Settings
{
    static void load(Gtk::Notebook &notebook);
};

} // namespace FrontEnd