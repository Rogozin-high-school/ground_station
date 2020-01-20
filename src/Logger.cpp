#include <Logger.hpp>

#include <FrontEnd.hpp>
#include <FrontEnd/Pages/CLI.hpp>

#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

std::stringstream logStringStream;
std::ofstream logFileStream;

void Logger::initialize()
{
    // Get the current time and date (long)
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::string timeStr{ctime(&time)};
    timeStr.pop_back();

    // Create logs folder if doesn't already exist
    system("mkdir -p logs");

    // Create a log file
    logFileStream.open("logs/" + timeStr);

    verbose("Logger has been initialized!");
}

void Logger::quit()
{
    logFileStream.close();
}

const Glib::ustring Logger::get_last_markup()
{
    return logStringStream.str();
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
    if (endl)
    {
        markup += "\n";
    }

    logFileStream << markup;

    // You probably ask yourself why I made that weird and complicated.
    // Well, the answer is that you can't print to the console before it was created.
    // Therefore I must save all the markup to be printed before the console had been created,
    // and print it in one shot right after it is done.

    logStringStream << markup;

    if (FrontEnd::isRunning)
    {
        FrontEnd::Pages::CLI::append(markup);
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
