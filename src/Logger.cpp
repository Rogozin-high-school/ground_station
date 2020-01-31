#include <Logger.hpp>
#include <FrontEnd.hpp>
#include <FrontEnd/Pages/CLI.hpp>
#include <ctime>
#include <iostream>

std::stringstream logStringStream; // Non-static!

const Glib::ustring Logger::get_last_markup_and_reset()
{
    auto str = logStringStream.str();
    logStringStream.str("");
    logStringStream.clear();
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
    // You probably ask yourself why I made that weird and complicated.
    // Well, the answer is that you can't print to the console before it was created.
    // Therefore I must save all the markup to be printed before the console had been created,
    // and print it in one shot right after it is done.

    std::cout << markup;
    logStringStream << markup;
    if (endl)
    {
        std::cout << std::endl;
        logStringStream << std::endl;
    }

    // This if is important!
    // Remove it if you want segfaults :)
    // (append() should be called only after the frontend has begun running)
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
