#pragma once

#include <gtkmm/window.h>

namespace FrontEnd
{
struct Window : Gtk::Window
{
    Window();
protected:
    bool on_key_press_event(GdkEventKey *event) override;
};
} // namespace FrontEnd