#include <Logger.hpp>
#include <FrontEnd.hpp>
#include <FrontEnd/Pages/CLI.hpp>
#include <ctime>
#include <iostream>

std::stringstream lastMarkupStringStream; // Non-static!

const Glib::ustring Logger::get_last_markup_and_reset()
{
    auto str = lastMarkupStringStream.str();
    lastMarkupStringStream.str("");
    lastMarkupStringStream.clear();
    return str;
}

const Glib::ustring Logger::get_current_time()
{
    char buffer[12];
    time_t t;
    time(&t);
    strftime(buffer, sizeof(buffer), "[%H:%M:%S]", localtime(&t));
    return "<span foreground='grey'>" + Glib::ustring(buffer) + "</span>";
}

void Logger::print_raw(Glib::ustring &&markup, bool endl)
{
    std::cout << markup;
    lastMarkupStringStream << markup;
    if (endl)
    {
        std::cout << std::endl;
        lastMarkupStringStream << std::endl;
    }

    // append() should be called only after FrontEnd had begun running
    if (FrontEnd::isRunning)
    {
        FrontEnd::Pages::CLI::append();
    }
}

void Logger::verbose(Glib::ustring &&markup, bool endl)
{
    print_raw(get_current_time() + "<span foreground='grey'> " + markup + "</span>", endl);
}

void Logger::debug(Glib::ustring &&markup, bool endl)
{
    print_raw(get_current_time() + "<span foreground='cyan'> " + markup + "</span>", endl);
}

void Logger::info(Glib::ustring &&markup, bool endl)
{
    print_raw(get_current_time() + "<span foreground='white'> " + markup + "</span>", endl);
}

void Logger::warn(Glib::ustring &&markup, bool endl)
{
    print_raw(get_current_time() + "<span foreground='red'> " + markup + "</span>", endl);
}

void Logger::error(Glib::ustring &&markup, bool endl)
{
    print_raw(get_current_time() + "<span foreground='red' weight = 'bold'> " + markup + "</span>", endl);
}
