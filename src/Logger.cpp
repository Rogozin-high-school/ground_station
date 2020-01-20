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

const Glib::ustring Logger::get_last_text()
{
    return logStringStream.str();
}

void Logger::print_raw(Glib::ustring &&text, bool endl)
{
    // Get the current time (short)
    {
        char buffer[12];
        time_t t;
        time(&t);
        strftime(buffer, sizeof(buffer), "[%H:%M:%S] ", localtime(&t));
        text = buffer + text;
    }

    if (endl)
    {
        text += "\n";
    }

    logFileStream << text;

    // You probably ask yourself why I made that weird and complicated.
    // Well, the answer is that you can't print to the console before it was created.
    // Therefore I must save all the text to be printed before the console had been created,
    // and print it in one shot right after it is done.

    logStringStream << text;

    if (FrontEnd::isRunning)
    {
        FrontEnd::Pages::CLI::append(text);
    }
}

void Logger::verbose(Glib::ustring &&text, bool endl)
{
    print_raw("[Verbose] " + text, endl);
}

void Logger::debug(Glib::ustring &&text, bool endl)
{
    print_raw("[Debug]   " + text, endl);
}

void Logger::info(Glib::ustring &&text, bool endl)
{
    print_raw("[Info]    " + text, endl);
}

void Logger::warn(Glib::ustring &&text, bool endl)
{
    print_raw("[Warn]    " + text, endl);
}

void Logger::error(Glib::ustring &&text, bool endl)
{
    print_raw("[Error]   " + text, endl);
}
