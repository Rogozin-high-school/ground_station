#pragma once
#include <glibmm/ustring.h>

struct Logger
{
    static void initialize();
    static void quit();

    static const Glib::ustring get_last_text();

    static void print_raw(Glib::ustring &&text, bool endl = true);
    static void verbose(Glib::ustring &&text, bool endl = true);
    static void debug(Glib::ustring &&text, bool endl = true);
    static void info(Glib::ustring &&text, bool endl = true);
    static void warn(Glib::ustring &&text, bool endl = true);
    static void error(Glib::ustring &&text, bool endl = true);
};
