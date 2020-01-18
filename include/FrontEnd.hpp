#pragma once

#include <string>
#include <gdkmm/pixbuf.h>
#include <gtkmm/image.h>

namespace FrontEnd
{

namespace Resources::Paths
{
static inline const std::string
    CSSProvider = "res/style.css",
    iconGroundStation = "res/ground_station.png",
    iconConsole = "res/console.png",
    iconGears = "res/gears.png";
} // namespace Resources::Paths

namespace Resources::Pixbufs
{

extern Glib::RefPtr<Gdk::Pixbuf>
    pIconGroundStation,
    pIconConsole,
    pIconGears;

static inline void load()
{
    pIconGroundStation = Gdk::Pixbuf::create_from_file(Paths::iconGroundStation);
    pIconConsole = Gdk::Pixbuf::create_from_file(Paths::iconConsole);
    pIconGears = Gdk::Pixbuf::create_from_file(Paths::iconGears);
}

} // namespace Resources::Pixbufs

void initialize();
void run();
void quit();

} // namespace FrontEnd