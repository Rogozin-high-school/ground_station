#include <FrontEnd/Pages/CLI.hpp>
#include <FrontEnd.hpp>
#include <BackEnd.hpp>
#include <Logger.hpp>
#include <gtkmm/entry.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <thread>
#include <chrono>

struct Entry : Gtk::Entry
{
protected:
    void on_activate() override;
};

static Entry *pEntry;
static Gtk::TextView *pTextView;

static void load_page(Gtk::Box *pPage);
static void process_command(const Glib::ustring &command);
static void insert_markup();

void FrontEnd::Pages::CLI::load(Gtk::Notebook *pNotebook)
{
    auto pPage = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    auto pIcon = Gtk::manage(new Gtk::Image(SCALE(Resources::Pixbufs::pIconConsole, 96)));
    pNotebook->append_page(*pPage, *pIcon);
    load_page(pPage);
    append();
}

void FrontEnd::Pages::CLI::append()
{
    g_idle_add((GSourceFunc)insert_markup, nullptr);
}

void Entry::on_activate()
{
    auto pBuffer = this->get_buffer();
    auto text = pBuffer->get_text();
    if (text.empty())
    {
        return;
    }

    pBuffer->set_text("");

    Logger::print_raw(Logger::get_current_time() + " <span weight='bold'>> '" + text + "'</span>");
    process_command(text);
}

void load_page(Gtk::Box *pPage)
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

void process_command(const Glib::ustring &command)
{
    if (command == "exit" || command == "quit" || command == "terminate" || command == "close" || command == "stop")
    {
        BackEnd::quit();
        std::thread countdownThread([]() {
            constexpr int delaySeconds = 3;
            for (int i = delaySeconds; i > 0; i--)
            {
                Logger::verbose("Shutting down in " + std::to_string(i) + " seconds...");
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            g_idle_add((GSourceFunc)FrontEnd::quit, nullptr);
        });
        countdownThread.detach();
    }
}

void insert_markup()
{
    auto pBuffer = pTextView->get_buffer();
    pBuffer->insert_markup(pBuffer->end(), Logger::get_last_markup_and_reset());
}