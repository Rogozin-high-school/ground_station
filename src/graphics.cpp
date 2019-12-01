#include <graphics.hpp>
#include <gtkmm/cssprovider.h>

Graphics::Graphics(GroundStation& groundStation) 
    : groundStation(groundStation)
{
    application = Gtk::Application::create();

    Window window(*this);
    {
        { // CSS
            auto css = Gtk::CssProvider::create();
            css->load_from_resource("/style.css");
            window.get_style_context()->add_provider(css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        }
        window.set_default_icon(Gdk::Pixbuf::create_from_resource("/icon.png"));
        window.fullscreen();
        width = window.get_screen()->get_width();
        height = window.get_screen()->get_height();
        window.add_events(Gdk::KEY_PRESS_MASK);
    }

    DrawingArea drawingArea(*this);
    window.add(drawingArea);
    drawingArea.show();

    application->run(window);
}

void Graphics::quit() {
    // groundStation.quit();
    application->quit();
}

bool Graphics::Window::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape) {
        graphics.quit();
    }
    return true;
}

bool Graphics::DrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // if (!graphics.groundStation.isConnected) {
    //     Pango::FontDescription font;
    //     // font.set_family("Ubuntu");
    //     // font.set_weight(Pango::WEIGHT_BOLD);
    //     // font.set_size(36 * PANGO_SCALE);

    //     auto layout = create_pango_layout("Waiting for connection");
    //     layout->set_font_description(font);

    //     int w, h, x, y;
    //     layout->get_pixel_size(w, h);
    //     x = (graphics.width - w) / 2.0;
    //     y = (graphics.height - h) / 2.0;

    //     // cr->set_source_rgb(1, 1, 1);
    //     cr->move_to(x, y);
    //     layout->show_in_cairo_context(cr);
    // }
    return true;
}