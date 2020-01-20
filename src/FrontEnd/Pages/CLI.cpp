#include <FrontEnd/Pages/CLI.hpp>
#include <FrontEnd.hpp>

#include <Logger.hpp>

#include <gtkmm/entry.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>

void load_page(Gtk::Box *pPage);
void process_command(const Glib::ustring &command);

struct Entry : Gtk::Entry
{
protected:
    void on_activate() override
    {
        auto pBuffer = get_buffer();

        auto text = pBuffer->get_text();
        pBuffer->set_text("");
        
        Logger::print_raw("> " + text);
        process_command(text);
    }
} *pEntry;
Gtk::TextView *pTextView;

void FrontEnd::Pages::CLI::load(Gtk::Notebook *pNotebook)
{
    auto pPage = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    auto pIcon = Gtk::manage(new Gtk::Image(SCALE(Resources::Pixbufs::pIconConsole, 96)));
    pNotebook->append_page(*pPage, *pIcon);
    load_page(pPage);

    append(Logger::get_last_text());
}

void FrontEnd::Pages::CLI::append(const Glib::ustring &text)
{
    pTextView->get_buffer()->insert_at_cursor(text);   
}

inline void load_page(Gtk::Box *pPage)
{
    pPage->set_name("page_cli");

    auto pTextView_box = Gtk::manage(new Gtk::Box);
    auto pTextView_scrolledWindow = Gtk::manage(new Gtk::ScrolledWindow);
    pTextView = Gtk::manage(new Gtk::TextView);
    
    pEntry = Gtk::manage(new Entry);

    pTextView_scrolledWindow->add(*pTextView);
    pTextView_box->pack_start(*pTextView_scrolledWindow);
    pTextView->set_cursor_visible(false);
    pTextView->set_editable(false);

    pPage->pack_start(*pTextView_box);
    pPage->pack_start(*pEntry, Gtk::PACK_SHRINK);
}

inline void process_command(const Glib::ustring &command)
{
    if (command == "exit" || command == "quit" || command == "terminate" || command == "close" || command == "stop")
    {
        FrontEnd::quit();
    }
}