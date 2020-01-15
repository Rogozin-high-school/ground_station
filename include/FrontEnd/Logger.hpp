#pragma once
#include <FrontEnd/Pages/CLI.hpp>

#include <iostream>
#include <fstream>
#include <string>

class Logger
{
    static std::ofstream logFile;
public:
    static void initialize();
    static void print(std::string&& text, bool endl = true);
    static void quit();
};
