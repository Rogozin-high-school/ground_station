#include <FrontEnd/Pages/CLI.hpp>
#include <FrontEnd.hpp>

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/entry.h>

Gtk::TextView *pTextView;

void load_page(Gtk::Box &page);

void FrontEnd::Pages::CLI::load(Gtk::Notebook &notebook)
{
    static Gtk::Box page(Gtk::ORIENTATION_VERTICAL);
    static Gtk::Image icon(Resources::Pixbufs::iconConsole->scale_simple(96, 96, Gdk::INTERP_BILINEAR));
    notebook.append_page(page, icon);
    load_page(page);
}

Glib::RefPtr<Gtk::TextBuffer> FrontEnd::Pages::CLI::get_text_buffer()
{
    return pTextView->get_buffer();
}

inline void load_page(Gtk::Box &page)
{
    page.set_name("page_cli");

    static Gtk::Box textView_box;
    static Gtk::ScrolledWindow textView_scrolledWindow;
    pTextView = Gtk::manage(new Gtk::TextView);
    
    static Gtk::Entry entry;

    textView_scrolledWindow.add(*pTextView);
    textView_box.pack_start(textView_scrolledWindow);
    pTextView->set_cursor_visible(false);
    pTextView->set_editable(false);

    page.pack_start(textView_box);
    page.pack_start(entry, Gtk::PACK_SHRINK);
}