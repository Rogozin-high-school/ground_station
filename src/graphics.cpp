#include <graphics.hpp>
#include <GL/gl.h>

Glib::RefPtr<Gdk::Pixbuf> pIconGroundStation;
Glib::RefPtr<Gdk::Pixbuf> pIconSatellite;
Glib::RefPtr<Gdk::Pixbuf> pIconRogozin;
Glib::RefPtr<Gdk::Pixbuf> pIconPresentation;

int width;
int height;

Graphics::Graphics(GroundStation &groundStation) : groundStation(groundStation)
{
    pApplication = Gtk::Application::create();
    {
        auto pScreen = Gdk::Screen::get_default();
        { // Load CSS from resource
            auto pCSSProvider = Gtk::CssProvider::create();
            Gtk::StyleContext::add_provider_for_screen(pScreen, pCSSProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            pCSSProvider->load_from_resource("/style.css");
        }
        { // Load icons
            pIconGroundStation = Gdk::Pixbuf::create_from_resource("/ground_station.png");
            pIconSatellite = Gdk::Pixbuf::create_from_resource("/satellite.png");
            pIconRogozin = Gdk::Pixbuf::create_from_resource("/rogozin.png");
            pIconPresentation = Gdk::Pixbuf::create_from_resource("/presentation.png");
        }
        width = pScreen->get_width();
        height = pScreen->get_height();
    }
    Window window(this);
    pApplication->run(window);
}

Window::Window(Graphics *pGraphics) : graphics(*pGraphics)
{
    set_default_icon(pIconGroundStation);
    fullscreen();
    add_events(Gdk::KEY_PRESS_MASK);

    static Gtk::Box layout(Gtk::ORIENTATION_VERTICAL);
    {
        static Gtk::Box titleBar;
        titleBar.set_name("title_bar");
        {
            static Gtk::Box titleBarInner;
            titleBarInner.set_name("title_bar_inner");
            {
                static Gtk::Image icon(pIconRogozin->scale_simple(128, 128, Gdk::INTERP_BILINEAR));
                static Gtk::Label label("Rogozin's Ground Station");
                icon.set_name("title_bar_inner");
                label.set_name("title_bar_inner");
                titleBarInner.pack_start(icon, Gtk::PACK_SHRINK);
                titleBarInner.pack_start(label, Gtk::PACK_SHRINK);
            }
            titleBar.add(titleBarInner);
        }
        layout.pack_start(titleBar, Gtk::PACK_SHRINK);
    }
    {
        static Gtk::Notebook notebook;
        notebook.set_tab_pos(Gtk::POS_LEFT);
        {
            { // Presentation Mode
                static Gtk::Image icon(pIconPresentation->scale_simple(128, 128, Gdk::INTERP_BILINEAR));
                static Gtk::Box page;
                notebook.append_page(page, icon);
            }
            { // Ground Station Control
                static Gtk::Image icon(pIconGroundStation->scale_simple(128, 128, Gdk::INTERP_BILINEAR));
                static Gtk::Box page;
                notebook.append_page(page, icon);
            }
            { // Satellite Control
                static Gtk::Image icon(pIconSatellite->scale_simple(128, 128, Gdk::INTERP_BILINEAR));
                static Gtk::Box page;
                notebook.append_page(page, icon);
            }
        }
        layout.pack_start(notebook);
    }
    add(layout);
    show_all();
}

bool Window::on_key_press_event(GdkEventKey *event)
{
    if (event->keyval == GDK_KEY_Escape)
    {
        graphics.quit();
    }
    return true;
}

bool GLArea::on_render(const Glib::RefPtr<Gdk::GLContext> &context)
{
    // OpenGL stuff
    // glClearColor(0.125, 0.125, 0.125, 1);
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

void Graphics::quit()
{
    groundStation.quit();
    pApplication->quit();
}