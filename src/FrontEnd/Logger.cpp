#include <FrontEnd/Logger.hpp>

#include <ctime>
#include <cstdlib>

std::ofstream Logger::logFile;

void Logger::initialize()
{
    // Get the current time and date (long)
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::string timeStr{ctime(&time)};
    std::replace(begin(timeStr), end(timeStr), ' ', '_');
    std::replace(begin(timeStr), end(timeStr), ':', '-');
    timeStr = timeStr.substr(0, timeStr.length() - 1);

    // Create logs folder is doesn't already exist
    system("mkdir -p logs");

    // Create a log file
    logFile.open("logs/" + timeStr + ".log");
}

void Logger::print(std::string&& text, bool endl)
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

    logFile << text;
    FrontEnd::Pages::CLI::get_text_buffer()->insert_at_cursor(text);
}

void Logger::quit()
{
    logFile.close();
}