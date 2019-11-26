#include <graphics.hpp>
#include <ground_station.hpp>
#include <gtkmm/cssprovider.h>

Graphics::Graphics(GroundStation& groundStation) 
    : groundStation(groundStation) 
{
    auto css = Gtk::CssProvider::create();
    css->load_from_resource("/style.css");
    get_style_context()->add_provider(css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    set_default_icon(Gdk::Pixbuf::create_from_resource("/icon.png"));

    fullscreen();
    
    add_events(Gdk::KEY_PRESS_MASK);
}

bool Graphics::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape) {
        groundStation.quit();
    }
    return true;
}