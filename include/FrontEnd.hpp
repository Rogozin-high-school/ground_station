#pragma once

#include <string>
#include <gdkmm/pixbuf.h>
#include <gtkmm/image.h>

namespace FrontEnd
{

namespace Resources::Paths
{
extern const Glib::ustring
    CSSProvider,
    iconGroundStation,
    iconConsole,
    iconGears; 
} // namespace Resources::Paths

namespace Resources::Pixbufs
{

extern Glib::RefPtr<Gdk::Pixbuf>
    pIconGroundStation,
    pIconConsole,
    pIconGears;

#define SCALE(pixbuf, size) pixbuf->scale_simple(size, size, Gdk::INTERP_BILINEAR)

} // namespace Resources::Pixbufs

extern bool isRunning;

void initialize();
void run();
void quit();

}