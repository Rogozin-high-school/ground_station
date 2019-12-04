#include <graphics.hpp>
#include <gdkmm/screen.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>
#include <gtkmm/label.h>
#include <GL/gl.h>

/*
 * Allocate dynamically to avoid any kind of segmentation faults,
 * and so you could access the widgets from wherever you like.
 */

double         width;
double         height;
Gtk::Table    *pLayout;
Gtk::Box      *pLeftPanel;
GLArea        *pMiddlePanel;
Gtk::Box      *pRightPanel;
PanelRevealer *pLeftPanelRevealer;
PanelRevealer *pRightPanelRevealer;

Graphics::Graphics(GroundStation& groundStation) : groundStation(groundStation)
{
    pApplication = Gtk::Application::create();
    {
        auto pScreen = Gdk::Screen::get_default();
        { // Load CSS from resource
            auto pCSSProvider = Gtk::CssProvider::create();
            Gtk::StyleContext::add_provider_for_screen(pScreen, pCSSProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            pCSSProvider->load_from_resource("/style.css");
        }
        width = pScreen->get_width();
        height = pScreen->get_height();
    }
    Window window(this);
    pApplication->run(window);
}

void Graphics::quit() {
    groundStation.quit();
    pApplication->quit();
}

Window::Window(Graphics *pGraphics) : graphics(*pGraphics) {
    set_default_icon(Gdk::Pixbuf::create_from_resource("/icon.png"));
    fullscreen();
    add_events(Gdk::KEY_PRESS_MASK);

    pLayout             = Gtk::manage(new Gtk::Table);
    pLeftPanel          = Gtk::manage(new Gtk::Box);
    pMiddlePanel        = Gtk::manage(new GLArea);
    pRightPanel         = Gtk::manage(new Gtk::Box);
    pLeftPanelRevealer  = Gtk::manage(new PanelRevealer(PanelRevealer::Side::Left, true));
    pRightPanelRevealer = Gtk::manage(new PanelRevealer(PanelRevealer::Side::Right, true));

    { // Add the panel revealers to the panels
        pLeftPanel->pack_start(*pLeftPanelRevealer, pLeftPanelRevealer->get_expanded() ? Gtk::PACK_EXPAND_WIDGET : Gtk::PACK_SHRINK);
        pRightPanel->pack_start(*pRightPanelRevealer, pRightPanelRevealer->get_expanded() ? Gtk::PACK_EXPAND_WIDGET : Gtk::PACK_SHRINK);
        pRightPanel->set_direction(Gtk::TextDirection::TEXT_DIR_RTL);
    }

    { // Add the panels to the layout
        int middlePanelSize = height; // Middle panel is square and in the middle of the screen
        int x1 = (width - middlePanelSize) / 2.0;
        int x2 = x1 + middlePanelSize;
        pLayout->attach(*pLeftPanel,   0,  x1,    0, 1);
        pLayout->attach(*pMiddlePanel, x1, x2,    0, 1);
        pLayout->attach(*pRightPanel,  x2, width, 0, 1);
    }

    add(*pLayout);
    show_all();
}

bool Window::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape) {
        graphics.quit();
    }
    return true;
}

bool GLArea::on_render(const Glib::RefPtr<Gdk::GLContext>& context) {
    // OpenGL stuff
    glClearColor(0.125, 0.125, 0.125, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    return true;
}

bool PanelRevealer::on_button_release_event(GdkEventButton* event) {
    // TODO: Document this, will not be clear to anyone except Maor :(
    if (get_expanded()) {
        set_expanded(false);
        if (side == Side::Left) {
            pLeftPanel->remove(*this);
            pLeftPanel->pack_start(*this, Gtk::PACK_SHRINK);
        } else {
            pRightPanel->remove(*this);
            pRightPanel->pack_start(*this, Gtk::PACK_SHRINK);
        }
    } else {
        set_expanded(true);
        if (side == Side::Left) {
            pLeftPanel->remove(*this);
            pLeftPanel->pack_start(*this, Gtk::PACK_EXPAND_WIDGET);
        } else {
            pRightPanel->remove(*this);
            pRightPanel->pack_start(*this, Gtk::PACK_EXPAND_WIDGET);
        }
    }
    return true;
}