#pragma once
#include <gtkmm/notebook.h>
#include <gtkmm/textbuffer.h>

namespace FrontEnd::Pages
{

struct CLI
{
    static void load(Gtk::Notebook &notebook);
    static Glib::RefPtr<Gtk::TextBuffer> get_text_buffer();
};

} // namespace FrontEnd