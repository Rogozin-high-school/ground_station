#pragma once
#include <glibmm/ustring.h>

struct Logger
{
    static void initialize();
    static void quit();

    static const Glib::ustring get_last_markup();
    static const Glib::ustring get_current_time();

    static void print_raw(Glib::ustring &&markup, bool endl = true);
    static void verbose(Glib::ustring &&markup, bool endl = true);
    static void debug(Glib::ustring &&markup, bool endl = true);
    static void info(Glib::ustring &&markup, bool endl = true);
    static void warn(Glib::ustring &&markup, bool endl = true);
    static void error(Glib::ustring &&markup, bool endl = true);
};
