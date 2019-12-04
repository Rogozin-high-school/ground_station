#include <window.hpp>

Window::Window(Graphics *pGraphics) : graphics(*pGraphics) {
    set_default_icon(Gdk::Pixbuf::create_from_resource("/icon.png"));
    fullscreen();
    add_events(Gdk::KEY_PRESS_MASK);
}

bool Window::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape) {
        graphics.quit();
    }
    return true;
}