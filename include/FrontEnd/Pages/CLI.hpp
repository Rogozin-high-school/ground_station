#pragma once
#include <gtkmm/entry.h>
#include <gtkmm/notebook.h>
#include <gtkmm/textbuffer.h>

namespace FrontEnd::Pages
{

struct CLI
{
    struct Entry : Gtk::Entry
    {
    protected:
        void on_activate() override;
    };
    
    static void load(Gtk::Notebook *pNotebook);
    static Glib::RefPtr<Gtk::TextBuffer> get_text_buffer();
};

} // namespace FrontEnd