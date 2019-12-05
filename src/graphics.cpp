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
                static Gtk::Image icon(pIconRogozin->scale_simple(64, 64, Gdk::INTERP_BILINEAR));
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
        int glAreaSize = height - 64 * 2;
        int x1 = (width - glAreaSize) / 2.0;
        int x2 = x1 + glAreaSize;

        static Gtk::Table belowTitleBar;
        {
            static Gtk::Box sideBar(Gtk::ORIENTATION_VERTICAL);
            sideBar.set_name("side_bar");
            {
                static Gtk::ToggleButton presentationModeButton;
                presentationModeButton.set_name("side_bar_node");
                {
                    static Gtk::Box presentationMode;
                    presentationMode.set_name("side_bar_node");
                    {
                        static Gtk::Image icon(pIconPresentation->scale_simple(64, 64, Gdk::INTERP_BILINEAR));
                        static Gtk::Label label("Presentation Mode");
                        icon.set_name("side_bar_node");
                        label.set_name("side_bar_node");
                        presentationMode.pack_start(icon, Gtk::PACK_SHRINK);
                        presentationMode.pack_start(label, Gtk::PACK_SHRINK);
                    }
                    presentationModeButton.add(presentationMode);
                }

                sideBar.pack_start(presentationModeButton, Gtk::PACK_SHRINK);
            }
            belowTitleBar.attach(sideBar, 0, x1, 0, 1);
        }
        {
            static GLArea glArea;
            belowTitleBar.attach(glArea, x1, x2, 0, 1);
        }
        {
            static Gtk::Box rest;
            belowTitleBar.attach(rest, x2, width, 0, 1);
        }
        layout.pack_start(belowTitleBar, Gtk::PACK_EXPAND_WIDGET);
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