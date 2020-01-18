#pragma once
#include <gtkmm/entry.h>
#include <gtkmm/notebook.h>
#include <gtkmm/textbuffer.h>

namespace FrontEnd::Pages
{

struct CLI
{
    static void load(Gtk::Notebook *pNotebook);
    static Glib::RefPtr<Gtk::TextBuffer> get_text_buffer();
};

} // namespace FrontEnd