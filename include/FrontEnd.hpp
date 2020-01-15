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
} // namespace Paths

namespace Resources::Pixbufs
{

extern Glib::RefPtr<Gdk::Pixbuf> 
    iconGroundStation,
    iconConsole,
    iconGears;

static inline void load()
{
    iconGroundStation = Gdk::Pixbuf::create_from_file(Paths::iconGroundStation);
    iconConsole = Gdk::Pixbuf::create_from_file(Paths::iconConsole);
    iconGears = Gdk::Pixbuf::create_from_file(Paths::iconGears);
}

} // namespace Resources::Pixbufs

void initialize();
void run();
void quit();

} // namespace FrontEnd