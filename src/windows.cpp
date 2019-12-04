#include <windows.hpp>
#include <gtkmm/box.h>
#include <gtkmm/table.h>
#include <GL/gl.h>

Window::Window(Graphics *pGraphics) : graphics(*pGraphics) {
    set_default_icon(Gdk::Pixbuf::create_from_resource("/icon.png"));
    fullscreen();
    add_events(Gdk::KEY_PRESS_MASK);

    static Gtk::Table layout;
    static Gtk::Box leftPanel, rightPanel;
    static GLArea middlePanel;

    int x1 = (graphics.width - graphics.height) / 2.0;
    int x2 = x1 + graphics.height;

    layout.attach(leftPanel, 0, x1, 0, 1);
    layout.attach(middlePanel, x1, x2, 0, 1);
    layout.attach(rightPanel, x2, graphics.width, 0, 1);

    add(layout);
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