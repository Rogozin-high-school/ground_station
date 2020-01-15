#include <FrontEnd.hpp>
#include <FrontEnd/Window.hpp>
#include <FrontEnd/Pages/CLI.hpp>
#include <FrontEnd/Pages/Settings.hpp>

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

void build_layout(FrontEnd::Window &window);
void build_title_bar(Gtk::Box &layout);
void build_notebook(Gtk::Box &layout);

FrontEnd::Window::Window()
{
    set_default_icon(Resources::Pixbufs::iconGroundStation);
    fullscreen();
    add_events(Gdk::KEY_PRESS_MASK);
    build_layout(*this);
    show_all();
}

bool FrontEnd::Window::on_key_press_event(GdkEventKey *event)
{
    if (event->keyval == GDK_KEY_Escape)
    {
        FrontEnd::quit();
    }
    return true;
}

inline void build_layout(FrontEnd::Window &window)
{
    static Gtk::Box layout(Gtk::ORIENTATION_VERTICAL);
    build_title_bar(layout);
    build_notebook(layout);
    window.add(layout);
}

inline void build_title_bar(Gtk::Box &layout)
{
    static Gtk::Box titleBar;
    static Gtk::Box titleBarInner;
    static Gtk::Image icon(FrontEnd::Resources::Pixbufs::iconGroundStation->scale_simple(96, 96, Gdk::INTERP_BILINEAR));
    static Gtk::Label label("Rogozin's Ground Station");

    titleBar.set_name("title_bar");
    titleBar.add(titleBarInner);
    
    titleBarInner.pack_start(icon, Gtk::PACK_SHRINK);
    titleBarInner.pack_start(label, Gtk::PACK_SHRINK);
    
    layout.pack_start(titleBar, Gtk::PACK_SHRINK);
}

inline void build_notebook(Gtk::Box &layout)
{
    static Gtk::Notebook notebook;
    notebook.set_tab_pos(Gtk::POS_LEFT);

    FrontEnd::Pages::CLI::load(notebook);
    FrontEnd::Pages::Settings::load(notebook);

    layout.pack_start(notebook);
}