#pragma once
#include <gtkmm/notebook.h>

namespace FrontEnd::Pages
{

struct CLI
{
    static void load(Gtk::Notebook *pNotebook);
    static void append();
};

} // namespace FrontEnd