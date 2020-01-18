#pragma once

#include <string>
#include <gdkmm/pixbuf.h>
#include <gtkmm/image.h>

namespace FrontEnd
{

namespace Resources::Paths
{
extern const std::string
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

} // namespace Resources::Pixbufs

void initialize();
void run();
void quit();

} // namespace FrontEnd